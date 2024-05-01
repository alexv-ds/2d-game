module;
#include <flecs.h>

export module engine.window;
export import :components;

import :components_impl;
import :systems_impl;

namespace engine {
  export struct Window {
    explicit Window(flecs::world& world) {
      world.module<Window>("window");

      window::init_window_components(world);
      window::init_window_phases(world);
      window::init_window_systems(world);
    }
  };
}

//instantiate import template
template flecs::entity flecs::world::import<engine::Window>();
