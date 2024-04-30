module;
#include <EASTL/array.h>
#include <SFML/Graphics.hpp>
export module engine.graphics:components.internal;

export namespace engine::graphics {
  struct SFML_Quad {
    eastl::array<sf::Vertex, 6> vertexes = {};
  };

  struct SFML_RenderStates {
    sf::RenderStates states;
  };
}