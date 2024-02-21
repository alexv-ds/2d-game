#include <type_traits>
#include <engine/space.hpp>

namespace engine::space {
  void init_space_components(flecs::world& world) {
    world.component<Size>()
      .member<decltype(Size::x)>("x")
      .member<decltype(Size::y)>("y");

    world.component<Position>()
      .member<decltype(Position::x)>("x")
      .member<decltype(Position::y)>("y");

    world.component<Rotation>()
      .member<decltype(Rotation::rad)>("rad");

    world.component<Scale>()
      .member<decltype(Scale::x)>("x")
      .member<decltype(Scale::y)>("y");

    world.component<Static>();

    world.component<Recalculate>();

    world.component<Global>();
  }
}