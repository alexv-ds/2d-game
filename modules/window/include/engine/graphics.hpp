#pragma once

#include <cstdint>
#include <flecs.h>
#include "graphics/components.hpp"
#include "graphics/predefined-colors.hpp"

namespace engine {

  struct Graphics {
    explicit Graphics(flecs::world&);
  };

}