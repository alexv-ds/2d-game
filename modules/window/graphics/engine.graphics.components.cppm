module;
#include "engine/space.hpp"
#include <SFML/Graphics.hpp>
#include <flecs.h>
export module engine.graphics:components;
import :components_internal;

export namespace engine::graphics {

  struct Color {
    float r = 1;// range [0, +inf]
    float g = 1;
    float b = 1;
  };

  struct Alpha {
    float a = 1;// range [0,1]

    inline Alpha() = default;
    inline Alpha(float a) : a(a) {}// NOLINT(google-explicit-constructor)
  };

  struct Layer {
    float z = 0;// range [-inf, +inf]

    inline Layer() = default;
    inline Layer(float z) : z(z) {}// NOLINT(google-explicit-constructor)
  };

  struct OnDraw {};

  struct FixEqualLayerBlinking {};

  // prefabs
  namespace material {
    struct BlendAlpha {};
    struct BlendAdd {};
    struct BlendMultiply {};
  };// namespace material
}// namespace engine::graphics

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