#include <spdlog/spdlog.h>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include <cmath>
#include <random>
#include <cstring>
#include <bit>

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
