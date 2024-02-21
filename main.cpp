#include <spdlog/spdlog.h>
#include <engine/window.hpp>
#include <engine/window/components-sfml.hpp>
#include <engine/space.hpp>

#include <random>

void* __cdecl operator new[](size_t size, const char* name, int, unsigned, const char* name2, int) {
  return new std::byte[size];
}

int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif
  flecs::world world;

  //world.import<engine::Window>();
  world.import<engine::Space>();

//  world.set<engine::window::SFML_RenderWindow>({
//    .window = eastl::make_shared<sf::RenderWindow>(
//      sf::VideoMode({1100,800}),
//      "Window"
//    )
//  });


//  {
//    auto _ = world.scope("test_entities");
//    std::random_device rd;
//    std::default_random_engine re(rd());
//    std::uniform_real_distribution<float> dist(0.0f, 10000.0f);
//
//    for (std::size_t i = 0; i < 100; ++i) {
//      world.entity()
//        .set<engine::space::Position>({
//          .x = dist(re),
//          .y = dist(re)
//        })
//        .add<engine::space::Position, engine::space::Global>()
//        .add<engine::space::Static>();
//    }
//
//      SPDLOG_INFO("Test entities initialised");
//    }

    {
      auto e1 = world.entity()
        .add<engine::space::Position>()
        .add<engine::space::Position, engine::space::Global>();

      auto sttc = world.entity()
        .add<engine::space::Position>()
        .add<engine::space::Position, engine::space::Global>()
        .add<engine::space::Static>()
        .add<engine::space::Recalculate>()
        .child_of(e1);

      auto e2 = world.entity()
        .add<engine::space::Position>()
        .add<engine::space::Position, engine::space::Global>()
        .child_of(sttc);
    }




  return world.app()
    .enable_monitor(true)
    .enable_rest()
    .target_fps(60)
    .threads(4)
    .run();
}
