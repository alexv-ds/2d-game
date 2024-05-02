#include <spdlog/spdlog.h>

#include <cmath>
#include <bit>
#include <flecs.h>
#include <memory>
#include <unordered_map>
#include <vector>

import engine.space;

using namespace engine;

void* operator new[](size_t size, const char* name, int, unsigned, const char* name2, int) {
  return new std::byte[size];
}

void* operator new[](size_t size,
                     size_t alignment,
                     size_t alignmentOffset,
                     const char* pName,
                     int flags,
                     unsigned debugFlags,
                     const char* file,
                     int line) {
  return new std::byte[size];
}

inline std::uint64_t hash(const std::int32_t x, const std::int32_t y) {
  const auto u64_x = static_cast<std::uint64_t>(std::bit_cast<std::uint32_t>(x));
  const auto u64_y = static_cast<std::uint64_t>(std::bit_cast<std::uint32_t>(y));
  return (u64_x << 32) | u64_y;
}

class SpatialHash;

class SpatialSharedData {
  friend class SpatialHash;

  space::BBox bbox_cache = {};
  space::Position position_cache = {};
  flecs::entity_t entity = 0;
};

class SpatialHash : std::enable_shared_from_this<SpatialHash> {
public:
  std::shared_ptr<SpatialSharedData> create_shared_data(const space::BBox& bbox,
                                                        const space::Position& position,
                                                        const flecs::entity_t entity) {

  }

private:
//  using CellT = std::vector




};

int main() {
#ifdef SPDLOG_ACTIVE_LEVEL
  spdlog::set_level(static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));
#endif

  for (std::int32_t x = -5; x <= 5; ++x) {
    for (std::int32_t y = -5; y <= 5; ++y) {
      SPDLOG_INFO("x: {}, y: {}, hash - {}", x,y, hash(x,y));
    }
  }
}
