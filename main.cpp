#include <spdlog/spdlog.h>
#include <engine/window.hpp>
#include <engine/window/components-sfml.hpp>
#include <engine/space.hpp>

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

  world.set<engine::window::SFML_RenderWindow>({
    .window = eastl::make_shared<sf::RenderWindow>(
      sf::VideoMode({1100,800}),
      "Window"
    )
  });

  world.entity("test transform")
    .add<engine::space::Size>()
    .add<engine::space::Position>()
    .add<engine::space::Transform>()
    .add<engine::space::Size, engine::space::Global>()
    .add<engine::space::Position, engine::space::Global>()
    .add<engine::space::Transform, engine::space::Global>();

  return world.app()
    .enable_monitor(true)
    .enable_rest()
    .target_fps(60)
    .threads(4)
    .run();
}
