#pragma once

namespace engine::graphics {

  struct Color {
    float r = 1; // range [0, +inf]
    float g = 1;
    float b = 1;
  };

  struct Alpha {
    float a = 1; // range [0,1]

    inline Alpha() = default;
    inline Alpha(float a): a(a) {} // NOLINT(google-explicit-constructor)
  };

  struct Layer {
    float z = 0; // range [-inf, +inf]

    inline Layer() = default;
    inline Layer(float z): z(z) {} // NOLINT(google-explicit-constructor)
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