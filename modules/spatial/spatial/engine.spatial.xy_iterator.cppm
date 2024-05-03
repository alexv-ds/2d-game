module;
#include <concepts>
#include <cstdint>
#include <iterator>
export module engine.spatial.xy_iterator;

namespace engine::spatial {

  export template<std::signed_integral T>
  struct xy {
    T x;
    T y;

    inline auto operator<=>(const xy&) const noexcept = default;
  };

  export template<std::signed_integral T>
  class xy_iterator {
  public:
//    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
  };

  //  static_assert(std::bidirectional_iterator<xy_iterator>);
}// namespace engine::spatial
