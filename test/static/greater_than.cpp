#include "refined.hpp"
#include "catch2/catch_test_macros.hpp"
#include <Catch2/catch_all.hpp>
#include <optional>
#include <type_traits>

// NOLINTBEGIN

TEST_CASE("static assertion for greater_than", "[static] [greater_than]") {
    constexpr auto positive = refined::Refined(1, refined::validator::ct_greater_than<int, 0>);
    STATIC_CHECK(positive.has_value());
    STATIC_CHECK(positive.value() == 1);

    constexpr auto invalid_positive = refined::Refined(-1, refined::validator::ct_greater_than<int, 0>);
    STATIC_CHECK_FALSE(invalid_positive.has_value());
    STATIC_CHECK(invalid_positive.value() == std::nullopt);

    constexpr auto positive2 = refined::Refined(2, refined::validator::ct_greater_than<int, 0>);
    STATIC_CHECK(std::is_same_v<decltype(positive), decltype(positive2)>);

    constexpr auto positive3 = refined::Refined(1, refined::validator::ct_greater_than<int, 1>);
    STATIC_CHECK_FALSE(std::is_same_v<decltype(positive), decltype(positive3)>);

    constexpr auto positive4 = refined::Refined(5, refined::validator::ct_greater_than<int, 3>);
    STATIC_CHECK(positive4.has_value());
    STATIC_CHECK(positive4.value() == 5);

    constexpr auto invalid_positive2 = refined::Refined(2, refined::validator::ct_greater_than<int, 3>);
    STATIC_CHECK_FALSE(invalid_positive2.has_value());
    STATIC_CHECK(invalid_positive2.value() == std::nullopt);
}



// NOLINTEND