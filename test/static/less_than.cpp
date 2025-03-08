
#include "refined.hpp"
#include "catch2/catch_test_macros.hpp"
#include <Catch2/catch_all.hpp>
#include <optional>
#include <type_traits>

// NOLINTBEGIN

TEST_CASE("static assertion for less_than", "[static] [less_than]") {
    constexpr auto negative = refined::Refined(-1, refined::validator::ct_less_than<int, 0>);
    STATIC_CHECK(negative.has_value());
    STATIC_CHECK(negative.value() == -1);

    constexpr auto invalid_negative = refined::Refined(1, refined::validator::ct_less_than<int, 0>);
    STATIC_CHECK_FALSE(invalid_negative.has_value());
    STATIC_CHECK(invalid_negative.value() == std::nullopt);

    constexpr auto negative2 = refined::Refined(-2, refined::validator::ct_less_than<int, 0>);
    constexpr auto invalid_positive = refined::Refined(-1, refined::validator::ct_greater_than<int, 0>);
    STATIC_CHECK_FALSE(invalid_positive.has_value());
    STATIC_CHECK(invalid_positive.value() == std::nullopt);

    constexpr auto negative3 = refined::Refined(-1, refined::validator::ct_less_than<int, -1>);
    STATIC_CHECK_FALSE(std::is_same_v<decltype(negative), decltype(negative3)>);
}



// NOLINTEND