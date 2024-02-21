#pragma once
#include <cstdint>
#include <flecs.h>

namespace engine {

  struct Graphics {
    explicit Graphics(flecs::world&);
  };

  struct Color {
    float r = 1;
    float g = 1;
    float b = 1;
  };
}