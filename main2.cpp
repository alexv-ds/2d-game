#include <spdlog/spdlog.h>
#include <cmath>
#include <random>

#include <glm/mat3x3.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <SFML/Graphics.hpp>
#include <EASTL/shared_ptr.h>
#include <flecs.h>

import engine.graphics;
import engine.graphics.colors;
import engine.window;
import engine.window.sfml;
import engine.space;

void* operator new[](size_t size, const char* name, int, unsigned, const char* name2, int) {
  return new std::byte[size];
}

void* operator new[](size_t size,
                     size_t alignment,
                     size_t alignmentOffset,
                     const char* pName,
                     int flags,
                     unsigned debugFlags,
                     const char* file,
                     int line) {
  return new std::byte[size];
}

using namespace engine;

struct BBoxer {};

int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  flecs::world world;





  world.import<engine::Window>();
  world.import<engine::Space>();
//  import_graphics(world);
  world.import<engine::Graphics>();

  auto window = std::make_shared<sf::RenderWindow>(
    sf::VideoMode::getDesktopMode(),
    "Window",
    sf::Style::Default
  );
  world.set<engine::window::SFML_RenderWindow>(
    {
      .window = window
    }
  );


  {
    auto _ = world.scope("entities");

    struct Orbit {
      float angular_speed = 2;
      float angle = 0;
      float radius = 1;
    };

    world.component<Orbit>()
      .member<float>("angular_speed")
      .member<float>("angle")
      .member<float>("radius");

    using namespace engine::space;

    auto prefab = world.prefab("prefab")
      .is_a<engine::graphics::material::BlendAlpha>()
      .add<engine::space::Position>()
      .add<engine::space::Rotation>()
      .add<engine::space::Scale>()
      .override<engine::space::Position>()
      .override<engine::space::Rotation>()
      .override<engine::space::Scale>()
      .add<engine::space::Position, engine::space::Global>()
      .add<engine::space::Rotation, engine::space::Global>()
      .add<engine::space::Scale, engine::space::Global>()
      .override<engine::space::Position, engine::space::Global>()
      .override<engine::space::Rotation, engine::space::Global>()
      .override<engine::space::Scale, engine::space::Global>()
      .set<space::Transform>(space::Transform{1.0f})
      .override<space::Transform>();

    std::default_random_engine re = [](){
      std::random_device rd;
      return std::default_random_engine(rd());
    }();

    const float global_speed = 1.0f;
    std::uniform_real_distribution<float> color_dist(0.83,0.83);
    std::uniform_real_distribution<float> radius_dist(0.0001,5);
    std::uniform_real_distribution<float> speed_dist(1,1.3);
    std::uniform_real_distribution<float> scale_dist(0.1,0.3);
    std::uniform_real_distribution<float> initial_angle_dist(0, 3.1415 * 2);
    std::uniform_int_distribution<int> negative_speed(0,0);

    for (int i = 0; i < 1000; ++i) {
      const float scale = scale_dist(re);
      auto e = world.entity()
        .set_doc_name("entity")
        .is_a(prefab)
        .set<engine::graphics::Color>({color_dist(re), color_dist(re), color_dist(re)})
        .set<engine::space::Scale>({scale, scale})
        .set<Orbit>(
          {
            .angular_speed = speed_dist(re) * (negative_speed(re) ? -1.0f : 1.0f),
            .angle = initial_angle_dist(re),
            .radius = radius_dist(re)
          }
        )
        .add<space::BBox>();
      world.entity()
        .set_doc_name("bbox")
        .child_of(e)
        .is_a<graphics::material::BlendAlpha>()
        .add<engine::space::Position>()
        .set<engine::space::Scale>(space::Scale{1})
        .add<engine::space::Position, engine::space::Global>()
        .add<engine::space::Scale, engine::space::Global>()
        .add<BBoxer>()
        .add<space::IgnoreParentScale>()
        .set<graphics::Layer>(10)
        .set<graphics::Alpha>(0.3f)
        .set<engine::graphics::Color>(graphics::color::red);
    }

    world.system<space::Scale, const space::BBox, const space::Scale>("SyncBbox")
      .instanced()
      .arg(1).self()
      .arg(2).self().parent()
      .arg(3).self().second<space::Global>().parent()
      .with<BBoxer>().self()
      .iter([](flecs::iter it, space::Scale* scale, const space::BBox* parent_bbox, const space::Scale* parent_scale) {
        for (auto i: it) {
          scale[i] = parent_bbox[i];
        }
      });

    world.system<Position, Rotation, Orbit>("Orbit")
      .iter([global_speed](flecs::iter it, Position* position, Rotation* rotation, Orbit* orbit) {
        const float dt = it.delta_system_time() * global_speed;
        for (auto i : it) {
          orbit[i].angle += dt * orbit[i].angular_speed / std::pow(orbit[i].radius, 1.5f);

          rotation[i].rad = orbit[i].angle + 3.1415f/2.0f;

          position[i].x = orbit[i].radius * std::cos(orbit[i].angle);
          position[i].y = orbit[i].radius * std::sin(orbit[i].angle);
        }
      });
  }

  window->setVerticalSyncEnabled(true);
  return world.app()
    .enable_monitor(true)
    .enable_rest()
    .target_fps(0)
    .threads(4)
    .run();
}
