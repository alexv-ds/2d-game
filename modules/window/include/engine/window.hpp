#pragma once
#include <flecs.h>
#include "window/event.hpp"
#include "window/components.hpp"

namespace engine {

  class Window {
  public:
    explicit Window(flecs::world&);
  };

} // namespace engine
