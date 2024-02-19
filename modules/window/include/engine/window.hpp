#pragma once

#include <flecs.h>
#include <fpimpl.hpp>

namespace engine {

  class Window {
  public:
    Window(flecs::world&);

  };

  struct Opened {};

  struct Focused {};

}
