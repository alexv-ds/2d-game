module;
#include <flecs.h>
#include <SFML/Graphics.hpp>
export module engine.graphics:components_impl;
import :components;
import :components_internal;
import engine.space;

namespace engine::graphics {
  template<class T>
  static flecs::entity create_material(flecs::world& world, sf::BlendMode blend_mode) {
    return world.prefab<T>()
      .set_doc_color("#ffffff")
      .template add<Color>()
      .template add<Alpha>()
      .template add<Layer>()
      .template add<SFML_Quad>()
      .template override<SFML_Quad>()

      .template set<space::Transform>(space::Transform{1.0f})
      .template override<space::Transform>()

      .template set<SFML_RenderStates>({sf::RenderStates(blend_mode)})
      .template add<FixEqualLayerBlinking>()
      .template override<FixEqualLayerBlinking>();
  }

  export void init_graphics_components(flecs::world& world) {
    world.component<Color>()
      .member<decltype(Color::r)>("r")
      .member<decltype(Color::g)>("g")
      .member<decltype(Color::b)>("b");

    world.component<Alpha>()
      .member<decltype(Alpha::a)>("a");

    world.component<Layer>()
      .member<decltype(Layer::z)>("z");

    world.component<FixEqualLayerBlinking>();

    world.component<OnDraw>();

    // private components
    {
      [[maybe_unused]] auto _ = world.scope("private");

      world.component<SFML_Quad>();
      world.component<SFML_RenderStates>();
    }

    // materials
    {
      [[maybe_unused]] auto _ = world.scope("material");

      create_material<material::BlendAlpha>(world, sf::BlendAlpha);
      create_material<material::BlendAdd>(world, sf::BlendAdd);
      create_material<material::BlendMultiply>(world, sf::BlendMultiply);
    }
  }
}

