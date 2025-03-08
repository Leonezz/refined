#include "catch2/catch_test_macros.hpp"
#include "refined.hpp"
// NOLINTBEGIN
TEST_CASE("static assertion for equal_to", "[static] [equal_to]") {
  constexpr auto equal_to_1 = refined::Refined(1, refined::validator::ct_equal_to<int, 1>);
  STATIC_CHECK(equal_to_1.has_value());
  STATIC_CHECK(equal_to_1.value() == 1);

  constexpr auto another_equal_to_1 = refined::Refined(1, refined::validator::ct_equal_to<int, 1>);
  STATIC_CHECK(std::is_same_v<decltype(equal_to_1), decltype(another_equal_to_1)>);
  STATIC_CHECK(equal_to_1 == another_equal_to_1);

  constexpr auto not_equal_to_1 = refined::Refined(2, refined::validator::ct_equal_to<int, 1>);
  STATIC_CHECK_FALSE(not_equal_to_1.has_value());
  STATIC_CHECK(not_equal_to_1.value() == std::nullopt);
  
  constexpr auto equal_to_2 = refined::Refined(2, refined::validator::ct_equal_to<int, 2>);
  STATIC_CHECK(equal_to_2.has_value());
  STATIC_CHECK(equal_to_2.value() == 2);
  STATIC_CHECK_FALSE(equal_to_2 == another_equal_to_1);

  constexpr auto another_equal_to_2 = refined::Refined(2, refined::validator::ct_equal_to<int, 2>);
  STATIC_CHECK(std::is_same_v<decltype(equal_to_2), decltype(another_equal_to_2)>);
  STATIC_CHECK_FALSE(std::is_same_v<decltype(equal_to_1), decltype(another_equal_to_2)>);
}

// NOLINTEND