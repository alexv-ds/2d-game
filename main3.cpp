#include <spdlog/spdlog.h>
#include <engine/window.hpp>
#include <engine/window/components-sfml.hpp>
#include <engine/space.hpp>
#include <engine/graphics.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include <cmath>
#include <random>
#include <cstring>

using namespace engine;

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


struct Force {
  glm::vec2 force = glm::vec2(0);
};

struct Mass {
  float mass = 1.0f;
};

struct Diameter {
  float d = 1.0f;
};

struct Speed {
  glm::vec2 speed = glm::vec2(0);
};

struct BodyPrefab {};

template<class T>
T random(T from, T to) {
  static auto random_engine = [](){
    std::random_device rd;
    return std::default_random_engine(rd());
  }();

  if constexpr (std::is_floating_point_v<T>) {
    return std::uniform_real_distribution<T>(from, to)(random_engine);
  } else {
    return std::uniform_int_distribution<T>(from, to)(random_engine);
  }
}

void init_components(flecs::world & world) {
  auto _ = world.scope("components");

  world.component<Force>()
    .member<float>("x")
    .member<float>("y");

  world.component<Mass>()
    .member<float>("mass");

  world.component<Diameter>()
    .member<float>("d");

  world.component<Speed>()
    .member<float>("x")
    .member<float>("y");

  world.prefab<BodyPrefab>()
    .is_a<engine::graphics::material::BlendAdd>()

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

    .add<Force>()
    .add<Mass>()
    .add<Diameter>()
    .add<Speed>()

    .override<Force>()
    .override<Mass>()
    .override<Diameter>()
    .override<Speed>();
}

void init_systems(flecs::world & world) {
  auto _ = world.scope("systems");

  auto objects_q = world.query_builder<const Mass, const space::Position>().build();

  world.system<Force>("CleanupForce")
    .iter([](flecs::iter it, Force* force) {
      std::memset(force, 0, sizeof(Force) * it.count());
    });

  world.system<Force, const Mass, const space::Position>("UpdateForce")
    .iter([objects_q](flecs::iter it, Force* force, const Mass* mass, const space::Position* position) {
      for (auto i: it) {
        objects_q.iter(
          [
            self = (flecs::entity_t) it.entity(i),
            p_self_force = force + i, self_mass = mass[i],
            self_position = position[i]
          ]
          (flecs::iter it, const Mass* mass, const space::Position* position) {
            for (auto i: it) {
              if (it.entity(i) == self) {
                continue;
              }

              const float r2 =
                std::pow(position[i].x - self_position.x, 2.0f) + std::pow(position[i].y - self_position.y, 2.0f);

              constexpr float G = 6.67408e-11;

              const glm::vec2 direction = glm::normalize(
                glm::vec2(position[i].x - self_position.x, position[i].y - self_position.y)
              );

              p_self_force->force += direction * (G * (self_mass.mass * mass[i].mass)) / r2;
            }
          }
        );
      }

    });

  world.system<const Force, const Mass, Speed>("UpdateSpeed")
    .iter([](flecs::iter it, const Force* force, const Mass* mass, Speed* speed) {
      const float dt = it.delta_time();
      for (auto i: it) {
        speed[i].speed += (force[i].force / mass[i].mass) * dt;
      }
    });

  world.system<const Speed, space::Position>("UpdatePosition")
    .iter([](flecs::iter it, const Speed* speed, space::Position* pos) {
      const float dt = it.delta_time();
      for (auto i: it) {
        glm::vec2 delta_pos = speed[i].speed * dt;
        pos[i].x += delta_pos.x;
        pos[i].y += delta_pos.y;
      }
    });

  auto merge_q = world.query_builder<
    const Mass,
    const space::Position,
    const Speed,
    const graphics::Color,
    const Diameter
  >().build();

  world.system<Mass, Speed, Diameter, graphics::Color, space::Position>("MergeObjects")
    .iter([merge_q](
      flecs::iter it,
      Mass* mass,
      Speed* speed,
      Diameter* diameter,
      graphics::Color* color,
      space::Position* position
    ) {
      for (auto i: it) {
        merge_q.iter(
          [
            self = (flecs::entity_t) it.entity(i),
            p_self_mass = mass + i,
            p_self_speed = speed + i,
            p_self_color = color + i,
            self_diameter = diameter[i],
            self_position = position[i]
          ]
            (flecs::iter it,
             const Mass* mass,
             const space::Position* position,
             const Speed* speed,
             const graphics::Color* color,
             const Diameter* diameter) {
            for (auto i: it) {
              flecs::entity e = it.entity(i);
              if (e == self) {
                continue;
              }

              if (p_self_mass->mass < mass[i].mass) {
                continue;
              }

              const float distance = std::sqrt(
                std::pow(position[i].x - self_position.x, 2.0f) + std::pow(position[i].y - self_position.y, 2.0f)
              );

              if ((distance - self_diameter.d - diameter[i].d) <= 0.0f) {
                e.destruct();
                SPDLOG_ERROR("DESTRUCTED: {}", (flecs::entity_t)e);
              }
            }
          }
        );
      }
    });

  world.system<const space::Position>("Delete")
    .each([](flecs::entity e, const space::Position& pos){
      if (pos.x > 100.0f || pos.y > 100.0f) {
        e.destruct();
      }
    })
    .add(flecs::Disabled);
//  world.system<const Mass, space::Position,

  world.system<Diameter, space::Scale>("UpdateScale")
    .each([](flecs::entity, Diameter& diameter, space::Scale& scale) {
      scale.x = diameter.d;
      scale.y = diameter.d;
    });
}

int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  flecs::world world;
  //flecs::log::set_level(0);

  world.import<engine::Window>();
  world.import<engine::Space>();
  world.import<engine::Graphics>();

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

  init_components(world);
  init_systems(world);

  world.entity()
    .is_a<BodyPrefab>()
    .set<space::Position>({0,0})
    .set<Diameter>({1.0f})
    .set<Mass>({1000e9});

  for (int i = 0; i < 10; ++i) {
    world.entity()
      .is_a<BodyPrefab>()
      .set<space::Position>({random(-4.0f, 4.0f), random(-4.0f, 4.0f)})
      .set<Diameter>({0.1f})
      .set<Mass>({5e9});
  }

//  world.entity("FIRST")
//    .is_a<BodyPrefab>()
//    .set<Diameter>({0.1})
//    .set<Mass>({10e9});
//
//  world.entity("SECOND")
//    .is_a<BodyPrefab>()
//    .set<space::Position>({2,2})
//    .set<Diameter>({0.1})
//    .set<Mass>({5e9});


  window->setVerticalSyncEnabled(true);
  return world.app()
    .enable_monitor(true)
    .enable_rest()
    .target_fps(0)
    .threads(4)
    .run();
}
