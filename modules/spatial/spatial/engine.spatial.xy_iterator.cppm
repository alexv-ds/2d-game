module;
#include <cstdint>
#include <iterator>
export module engine.spatial.xy_iterator;

namespace engine::spatial {

  export struct xy {
    std::int32_t x;
    std::int32_t y;
  };

  export class xy_iterator {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::int32_t;
    using pointer = value_type*;
    using reference = value_type&;

    inline xy_iterator(const value_type x_begin,
                       const value_type y_begin,
                       const value_type x_end,
                       const value_type y_end) noexcept
        : x(x_begin), y(y_begin),
          x_end(x_end), y_end(y_end) {}

//    inline const reference operator* () const noexcept {
//      return
//    }

  private:
    const value_type x_end;
    const value_type y_end;
    value_type x;
    value_type y;
  };
}// namespace engine::spatial