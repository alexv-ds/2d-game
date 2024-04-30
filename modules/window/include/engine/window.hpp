#pragma once
#include <flecs.h>
#include "window/event.hpp"
#include "window/components.hpp"

import engine.window;

namespace engine {

  class Window {
  public:
    explicit Window(flecs::world&);
  };

} // namespace engine
