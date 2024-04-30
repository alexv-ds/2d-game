#pragma once

#include <memory>
#include <flecs.h>
#include <EASTL/unordered_map.h>
#include <EASTL/vector.h>
#include "engine/space.hpp"

namespace engine::space {

  class SpatialHash;

  class SpatialSharedHandle {
  public:
    SpatialSharedHandle(const SpatialSharedHandle&) = delete;

    SpatialSharedHandle& operator=(const SpatialSharedHandle&) = delete;

    inline ~SpatialSharedHandle();

  private:
    friend class SpatialHash;

    std::weak_ptr<SpatialHash> spatial_hash;
    Position position_cache = {};
    BBox bbox_cache = {};
  };


  class SpatialHash {
  public:
    SpatialHash(const SpatialHash&) = delete;
    SpatialHash& operator=(const SpatialHash&) = delete;

    void update(const flecs::entity_t* entity, const Position* pos, const BBox* bbox);
    void create(const Position& pos, const BBox& bbox);

  private:

    void on_delete(SpatialSharedHandle& handle);

    friend class SpatialSharedHandle;

    struct SpatialObject {
      Position position = {};
      BBox bbox = {};
      flecs::entity_t entity = 0;
    };

    using CellT = eastl::vector<std::shared_ptr<SpatialSharedHandle>>;



  };


  ///////////////////////////////////
  ///////////// IMPL ////////////////
  ///////////////////////////////////

  inline SpatialSharedHandle::~SpatialSharedHandle() = default;


} // engine::space

