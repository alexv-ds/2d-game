#pragma once
#include <SFML/Graphics.hpp>
#include <EASTL/shared_ptr.h>

namespace engine::window {

  struct SFML_RenderWindow {
    eastl::shared_ptr<sf::RenderWindow> window;
    float cells_x = 10;
  };

  namespace phases {
    struct SFML_WindowClearPre {};
    struct SFML_WindowClear {};
    struct SFML_WindowDisplayPre {};
    struct SFML_WindowDisplay {};
  } // namespace phases
}