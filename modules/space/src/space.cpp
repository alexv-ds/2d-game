#include <engine/space.hpp>

namespace engine::space {
  void init_space_components(flecs::world&);
}

engine::Space::Space(flecs::world& world) {
  world.module<Space>("space");

  space::init_space_components(world);
}