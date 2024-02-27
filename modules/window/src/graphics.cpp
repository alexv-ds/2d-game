#include <algorithm>
#include <SFML/Graphics.hpp>
#include <EASTL/array.h>
#include <EASTL/vector.h>
#include <EASTL/algorithm.h>
#include <EASTL/sort.h>
#include <engine/space.hpp>
#include <engine/window.hpp>
#include <engine/window/components-sfml.hpp>
#include <engine/graphics.hpp>

#include <spdlog/spdlog.h>

namespace engine::graphics {
  void init_graphics_components(flecs::world&);
  void init_graphics_systems(flecs::world& world);
}

engine::Graphics::Graphics(flecs::world& world) {
  world.import<Space>();
  world.import<Window>();
  world.module<Graphics>("graphics");

  graphics::init_graphics_components(world);
  graphics::init_graphics_systems(world);
}