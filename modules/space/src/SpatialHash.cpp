#include "SpatialHash.hpp"

namespace engine::space {

  static inline std::uint64_t hash(const std::int32_t x, const std::int32_t y) {
    const auto u64_x = static_cast<std::uint64_t>(std::bit_cast<std::uint32_t>(x));
    const auto u64_y = static_cast<std::uint64_t>(std::bit_cast<std::uint32_t>(y));
    return (u64_x << 32) | u64_y;
  }


  void SpatialHash::update(const flecs::entity_t* entity, const Position* pos, const BBox* bbox) {

  }
} // engine::space