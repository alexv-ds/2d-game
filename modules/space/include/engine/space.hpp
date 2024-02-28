#pragma once

#include <flecs.h>
#include <glm/mat3x3.hpp>
#include <glm/vec2.hpp>

namespace engine {

  struct Space {
    explicit Space(flecs::world&);
  };

  namespace space {
    struct Position : glm::vec2 {
      using glm::vec2::vec2;
      using glm::vec2::operator=;
    };

    struct Rotation {
      float rad = 0;

      inline operator float() const { return this->rad; } // NOLINT(google-explicit-constructor)
      static constexpr Rotation radians(float rad) { return {rad}; };

      static constexpr Rotation degrees(float deg) {
        return {deg * (3.1415926535f / 180.0f)};
      }
    };

    struct Scale : glm::vec2 {
      using glm::vec2::vec2;
      using glm::vec2::operator=;
    };

    struct Global {
    };

    struct Static {
    };
    struct Recalculate {
    };

    struct Transform : glm::mat3 {
      using glm::mat3::mat3;
      using glm::mat3::operator=;
    };

    struct BBox : glm::vec2 {
      using glm::vec2::vec2;
      using glm::vec2::operator=;
    };

    struct IgnoreParentScale {};
  }

}