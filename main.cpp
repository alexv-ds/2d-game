#include <spdlog/spdlog.h>
#include <engine/window.hpp>
#include <engine/window/components-sfml.hpp>
#include <engine/space.hpp>
#include <engine/graphics.hpp>

#include <random>

void* __cdecl operator new[](size_t size, const char* name, int, unsigned, const char* name2, int) {
  return new std::byte[size];
}

int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  flecs::world world;

  world.import<engine::Window>();
  world.import<engine::Space>();
  world.import<engine::Graphics>();

  world.set<engine::window::SFML_RenderWindow>({
    .window = eastl::make_shared<sf::RenderWindow>(
      sf::VideoMode({1100,800}),
      "Window"
    )
  });


  {
    std::random_device rd;
    std::shared_ptr re = std::make_shared<std::default_random_engine>(rd());
    std::shared_ptr dist = std::make_shared<std::uniform_real_distribution<float>>(0.1f, 1.0f);

    std::uniform_real_distribution<float> rotation_dist(0.0f, 2.0f * 3.1415f);
    for (int i = 0; i < 100; ++i) {
      for (int x = -4; x <= 4; ++x) {
        for (int y = -4; y <= 4; ++y) {
          world.entity()
            .set<engine::space::Position>({.x = float(x), .y = float(y)})
            .add<engine::space::Position, engine::space::Global>()
            .set<engine::space::Rotation>({.rad = rotation_dist(*re)})
            .add<engine::space::Rotation, engine::space::Global>()
            .set<engine::space::Size>({.x = 0.95, .y = 0.95})
            .set<engine::graphics::Color>({.r = (*dist)(*re), .g = (*dist)(*re), .b = (*dist)(*re)});
        }
      }
    }

    world.system<engine::space::Rotation>("EPILEPTIC_ROTATION")
      .iter([](flecs::iter it, engine::space::Rotation* rotation){
        for (auto i : it) {
          rotation[i].rad += it.delta_system_time();
        }
      });
  }





  return world.app()
    .enable_monitor(true)
    .enable_rest()
    .target_fps(60)
    .threads(4)
    .run();
}
