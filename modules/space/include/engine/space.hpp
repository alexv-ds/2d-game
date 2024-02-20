#pragma once
#include <flecs.h>

namespace engine {

  struct Space {
    explicit Space(flecs::world&);
  };

  namespace space {
    struct Size {
      float x = 1;
      float y = 1;
    };

    struct Position {
      float x = 0;
      float y = 0;
    };

    struct Rotation {
      float rad = 0;
    };

    struct Scale {
      float x = 1;
      float y = 1;
    };

    struct Transform {
      // GLM compatible matrix
      float matrix[9] = {
        1,0,0,
        0,1,0,
        0,0,1
      };
    };

    struct Static {};
    struct Update {};
  }

}