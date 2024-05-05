module;
#include <concepts>
#include <iterator>
export module engine.spatial.xy_iterator;

export namespace engine::spatial {

  template<std::signed_integral T>
  struct xy {
    T x;
    T y;

    inline bool operator==(const xy&) const noexcept = default;
    inline bool operator!=(const xy&) const noexcept = default;
  };

  template<std::signed_integral T>
  class xy_iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = xy<T>;
    using pointer = const value_type*;
    using reference = const value_type&;

    inline xy_iterator() noexcept = default;

    inline xy_iterator(xy<T> from, xy<T> to)
        : xy_current(from), xy_end({.x = to.x + 1, .y = to.y}), y_begin(from.y) {}

    inline reference operator*() const noexcept {
      return this->xy_current;
    }

    inline pointer operator->() const noexcept {
      return &this->xy_current;
    }

    inline xy_iterator& operator++() noexcept {
      move_next();
      return *this;
    }

    inline xy_iterator operator++(int) noexcept {
      xy_iterator<T> tmp = *this;
      move_next();
      return tmp;
    }

    inline xy_iterator& operator--() noexcept {
      move_prev();
      return *this;
    }

    inline xy_iterator operator--(int) noexcept {
      xy_iterator<T> tmp = *this;
      move_prev();
      return tmp;
    }

    inline bool operator==(const xy_iterator<T> other) const noexcept {
      return this->xy_current == other.xy_current;
    }

    inline bool operator!=(const xy_iterator<T> other) const noexcept {
      return this->xy_current != other.xy_current;
    }

    inline xy_iterator<T>& begin() noexcept {// NOLINT(*-use-nodiscard)
      return *this;
    }

    inline xy_iterator<T> end() const noexcept {// NOLINT(*-use-nodiscard)
      xy_iterator<T> end = *this;
      end.xy_current = end.xy_end;
      return end;
    }

  private:
    xy<T> xy_current = {0, 0};
    xy<T> xy_end = {0, 0};
    xy<T> xy_increment = {1,1};
    T y_begin = 0;


    void move_next() noexcept {
      this->xy_current.y += this->xy_increment.y;
//      if (this->xy_current.y > this->xy_end.y) {
//        ++this->xy_current.x;
//
//      }
    }
    void move_prev() noexcept {}
  };

  static_assert(std::bidirectional_iterator<xy_iterator<int>>);
}// namespace engine::spatial
