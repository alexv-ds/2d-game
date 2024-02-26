#include <spdlog/spdlog.h>
#include <engine/window.hpp>
#include <engine/window/components-sfml.hpp>
#include <engine/space.hpp>
#include <engine/graphics.hpp>

#include <glm/vec2.hpp>
#include <glm/trigonometric.hpp>
#include <glm/common.hpp>

//region eastl
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
//endregion

using namespace engine;

//Описывает неповернутый прямоугольник вокруг повернутого прямоугольника
inline glm::vec2 describe_rectangle(glm::vec2 size, float angle) {
  float abs_sin_angle = glm::abs(glm::sin(angle));
  float abs_cos_angle = glm::abs(glm::cos(angle));
  return {
    size.x * abs_cos_angle + size.y * abs_sin_angle,
    size.x * abs_sin_angle + size.y * abs_cos_angle
  };
}

int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif

  flecs::world world;

  world.import<Window>();
  world.import<Space>();
  world.import<Graphics>();

  eastl::shared_ptr window = eastl::make_shared<sf::RenderWindow>(
    sf::VideoMode::getDesktopMode(),
    "Window",
    sf::Style::Default
  );
  world.set<engine::window::SFML_RenderWindow>(
    {
      .window = window
    }
  );

  auto prefab = world.prefab()
    .is_a<engine::graphics::material::BlendAlpha>()
    .add<engine::space::Size>()

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
    .override<engine::space::Scale, engine::space::Global>();

  struct RotateMe {};
  world.component<RotateMe>();

  world.system<const RotateMe, space::Rotation>()
    .each([](flecs::entity e, const RotateMe&, space::Rotation& rotation) {
      rotation.rad -= 0.01;
    });

  world.system<const RotateMe, space::Size>()
    .arg(2).self()
    .each([](flecs::entity e, const RotateMe&, space::Size& scale) {
      const float now = std::chrono::duration_cast<std::chrono::duration<float>>(
        std::chrono::high_resolution_clock::now().time_since_epoch()
      ).count();
      const float factor = glm::max(0.001f, glm::abs(glm::sin(now)));
      scale.x = factor;
      scale.y = factor;
    });

  auto e = world.entity("TARGET")
    .add<RotateMe>()
    .set<graphics::Layer>({-1})
    .add<space::Size>()
    .is_a(prefab);

  struct SyncWith {};
  world.component<SyncWith>()
    .add(flecs::Traversable);

  world.entity("BBOX")
    .set<graphics::Color>({graphics::color::red})
    .set<graphics::Alpha>({0.3})
    .add<space::Size>()
    .add<SyncWith>(e)
    .is_a(prefab);

  world.system<space::Size, space::Rotation, space::Size>()
    .arg(1).self()
    .arg(2).up<SyncWith>()
    .arg(3).up<SyncWith>()
    .each([](flecs::entity e, space::Size& size, space::Rotation& up_rotation, space::Size& up_size){
      const glm::vec2 newsize = describe_rectangle({up_size.x, up_size.y}, up_rotation.rad);
      size.x = newsize.x;
      size.y = newsize.y;
    });







//  for (float x = -4.0f; x <= 4.0f; ++x) {
//    for (float y = -4.0f; y <= 4.0f; ++y) {
//      auto hash = ((std::int64_t)(x / 1.0f) * 73856093) ^ ((std::int64_t) (y / 1.0f) * 19349663);
//      SPDLOG_INFO("{},{} - {}", x, y, hash);
//    }
//  }

  window->setVerticalSyncEnabled(true);
  return world.app()
    .enable_monitor(true)
    .enable_rest()
    .target_fps(0)
    .threads(4)
    .run();
}
