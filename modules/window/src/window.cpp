#include <engine/window.hpp>

namespace engine::window {
  void init_window_components(flecs::world&);
  void init_window_phases(flecs::world&);
  void init_window_systems(flecs::world&);
}

engine::Window::Window(flecs::world& world) {
  world.module<Window>("window");

  window::init_window_components(world);
  window::init_window_phases(world);
  window::init_window_systems(world);
}

