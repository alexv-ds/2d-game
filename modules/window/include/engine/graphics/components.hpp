#pragma once

namespace engine::graphics {

  struct Color {
    float r = 1; // range [0, +inf]
    float g = 1;
    float b = 1;
  };

  struct Alpha {
    float a = 1; // range [0,1]
  };

  struct Layer {
    float z = 0; // range [-inf, +inf]
  };

  struct OnDraw {};

  struct FixEqualLayerBlinking {};

  // prefabs
  namespace material {
    struct BlendAlpha {};
    struct BlendAdd {};
    struct BlendMultiply {};
  };
}