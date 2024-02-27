#include <type_traits>
#include <engine/space.hpp>

namespace engine::space {
  void init_space_components(flecs::world& world) {

    static_assert(sizeof(Position) == sizeof(glm::vec2));
    world.component<Position>()
      .member<decltype(Position::x)>("x")
      .member<decltype(Position::y)>("y");

    world.component<Rotation>()
      .member<decltype(Rotation::rad)>("rad");

    static_assert(sizeof(Scale) == sizeof(glm::vec2));
    world.component<Scale>()
      .member<decltype(Scale::x)>("x")
      .member<decltype(Scale::y)>("y");

    world.component<Static>();

    world.component<Recalculate>();

    world.component<Global>();

    world.component<Transform>();
  }
}