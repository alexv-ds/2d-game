#include <catch2/catch_test_macros.hpp>
#include <compare>
import engine.spatial.xy_iterator;

using namespace engine::spatial;

SCENARIO("xy struct compares correctly") {
  GIVEN("two equal xy structs") {
    xy<int> xy1 = {3, -5};
    xy<int> xy2 = {3, -5};

    REQUIRE(xy1 == xy2);
    REQUIRE(xy1 >= xy2);
    REQUIRE(xy1 <= xy2);
    REQUIRE_FALSE(xy1 > xy2);
    REQUIRE_FALSE(xy1 < xy2);
    REQUIRE_FALSE(xy1 != xy2);
    REQUIRE((xy1 <=> xy2) == std::strong_ordering::equal);
  }

  GIVEN("two non equal xy structs") {
    xy<int> xy1 = {3, -5};
    xy<int> xy2 = {6, -2};

    REQUIRE_FALSE(xy1 == xy2);
    REQUIRE(xy1 != xy2);
    REQUIRE((xy1 <=> xy2) != std::strong_ordering::equal);
  }
}