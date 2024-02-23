#include <spdlog/spdlog.h>
#include <engine/window.hpp>
#include <engine/window/components-sfml.hpp>
#include <engine/space.hpp>
#include <engine/graphics.hpp>


#include <random>

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
    sf::VideoMode({1100, 800}),
    "Window"
  );
  world.set<engine::window::SFML_RenderWindow>({
                                                 .window = window
                                               });


  {
    auto _ = world.scope("entities");
    std::random_device rd;
    std::shared_ptr re = std::make_shared<std::default_random_engine>(rd());
    std::shared_ptr dist = std::make_shared<std::uniform_real_distribution<float>>(0.1f, 1.0f);
    std::uniform_real_distribution<float> rotation_dist(0.0f, 2.0f * 3.1415f);
    std::uniform_int_distribution<std::size_t> material_dist(0, 2);
    std::shared_ptr layer_dist = std::make_shared<std::uniform_real_distribution<float>>(-1000000, 1000000);


    world.entity("green")
      .is_a<engine::graphics::material::BlendAdd>()
      .set<engine::space::Position>({.x = 0, .y = 0})
      .add<engine::space::Position, engine::space::Global>()
      .add<engine::space::Size>()
      .set<engine::graphics::Layer>({-1})
      .add<engine::space::Scale>()
      .add<engine::space::Scale, engine::space::Global>()
      .set<engine::graphics::Color>({0, 1, 0});

    world.entity("pink")
      .is_a<engine::graphics::material::BlendAdd>()
      .set<engine::space::Position>({.x = 0.5, .y = 0})
      .add<engine::space::Position, engine::space::Global>()
      .add<engine::space::Size>()
      .set<engine::graphics::Layer>({1})
      .set<engine::graphics::Color>({1, 0, 1});//.set<engine::graphics::Alpha>({0.5});


    world.system<engine::space::Rotation>("EPILEPTIC_ROTATION")
      .iter([](flecs::iter it, engine::space::Rotation* rotation) {
        for (auto i: it) {
          rotation[i].rad += it.delta_system_time();
        }
      });

    world.system<engine::graphics::Layer>("EPILEPTIC_LAYER")
      .iter([re, layer_dist](flecs::iter it, engine::graphics::Layer* layer) {
//        for (auto i : it) {
//          auto z = (*layer_dist)(*re);
//          layer[i].z = 1;
//        }
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
