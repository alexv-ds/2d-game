#pragma once

#include <SFML/Graphics.hpp>
#include <EASTL/array.h>

namespace engine::graphics {

  struct SFML_Quad {
    eastl::array<sf::Vertex, 6> vertexes = {};
  };

  struct SFML_RenderStates {
    sf::RenderStates states;
  };

  struct SFML_Transform {
    sf::Transform matrix;
  };
}