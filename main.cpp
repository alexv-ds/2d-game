#include <engine/window.hpp>
#include <engine/window/components-sfml.hpp>

void* __cdecl operator new[](size_t size, const char*, int, unsigned, const char*, int) {
  return new uint8_t[size];
}

int main() {
  flecs::world world;

  world.import<engine::Window>();

  world.set<engine::window::SFML_RenderWindow>({
    .window = eastl::make_shared<sf::RenderWindow>(
      sf::VideoMode({1100,800}),
      "Window"
    )
  });

  return world.app()
    .enable_monitor(true)
    .enable_rest()
    .target_fps(60)
    .threads(4)
    .run();
}
