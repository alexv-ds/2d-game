module;
#include <flecs.h>
#include <EASTL/array.h>
#include <SFML/Graphics.hpp>
#include <engine/window.hpp>
#include <engine/space.hpp>
//#include <engine/window/components-sfml.hpp>


export module engine.graphics;
export import :components;
import :systems;


export namespace engine {
  struct Graphics {
    explicit Graphics(flecs::world& world) {
      world.import<Space>();
      world.import<Window>();
      world.module<Graphics>("graphics");

      graphics::init_graphics_components(world);
      graphics::init_graphics_systems(world);

    }
  };
}// namespace engine

export void import_graphics(flecs::world& world) {
  world.import<engine::Graphics>();
}