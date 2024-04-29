#pragma once

#include <flecs.h>
#include <EASTL/unordered_map.h>
#include <EASTL/vector.h>
#include <engine/space.hpp>

namespace engine::space {




  class SpatialHash {
  public:
    void update(const flecs::entity_t* entity, const Position* pos, const BBox* bbox);
  private:
    struct SpatialObject {
      Position position = {};
      BBox bbox = {};
      flecs::entity_t entity = 0;
    };

  };

} // engine::space

