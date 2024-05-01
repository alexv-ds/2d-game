module;
#include <flecs.h>
export module engine.space;
export import :components;
import :components_impl;
import :systems;

export namespace engine {
  struct Space {
    explicit Space(flecs::world& world) {
      world.module<Space>("space");

      space::init_space_components(world);
      space::init_space_systems(world);
    }
  };
}

//instantiate import template
//template flecs::entity flecs::world::import<engine::Space>();