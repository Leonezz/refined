#include "catch2/catch_test_macros.hpp"
#include "refined.hpp"

// NOLINTBEGIN
TEST_CASE("dynamic check for equal_to", "[dynamic] [equal_to]") {
  SECTION("int") {
    auto equal_to_1 = refined::Refined(1, refined::validator::equal_to<int>(1));
    REQUIRE(equal_to_1.has_value());
    REQUIRE(equal_to_1.value() == 1);

    auto another_equal_to_1 = refined::Refined(1, refined::validator::equal_to<int>(1));
    REQUIRE(equal_to_1 == another_equal_to_1);

    const auto mutate_res = equal_to_1.mutate([](int &value) { value = 2; });
    REQUIRE_FALSE(mutate_res);
    REQUIRE(!equal_to_1.has_value());

    auto not_equal_to_1 = refined::Refined(2, refined::validator::equal_to<int>(1));
    REQUIRE_FALSE(not_equal_to_1.has_value());
    REQUIRE(not_equal_to_1.value() == std::nullopt);

    auto equal_to_2 = refined::Refined(2, refined::validator::equal_to<int>(2));
    REQUIRE(equal_to_2.has_value());
    REQUIRE(equal_to_2.value() == 2);
    REQUIRE_FALSE(equal_to_2 == another_equal_to_1);

    auto another_equal_to_2 = refined::Refined(2, refined::validator::equal_to<int>(2));
    REQUIRE(equal_to_2 == another_equal_to_2);
  }

  SECTION("string") {
    auto equal_to_hello = refined::Refined(std::string("hello"), refined::validator::equal_to<std::string>("hello"));
    REQUIRE(equal_to_hello.has_value());
    REQUIRE(equal_to_hello.value() == "hello");

    equal_to_hello = "world";
    REQUIRE_FALSE(equal_to_hello.has_value());
    REQUIRE(equal_to_hello.value() == std::nullopt);

    auto not_equal_to_hello =
        refined::Refined(std::string("world"), refined::validator::equal_to<std::string>("hello"));
    REQUIRE_FALSE(not_equal_to_hello.has_value());
    REQUIRE(not_equal_to_hello.value() == std::nullopt);

    auto equal_to_world = refined::Refined(std::string("world"), refined::validator::equal_to<std::string>("world"));
    REQUIRE(equal_to_world.has_value());
    REQUIRE(equal_to_world.value() == "world");
    REQUIRE_FALSE(equal_to_world == equal_to_hello);

    auto another_equal_to_world =
        refined::Refined(std::string("world"), refined::validator::equal_to<std::string>("world"));
    REQUIRE(equal_to_world == another_equal_to_world);
  }

  SECTION("string_view") {
    auto equal_to_hello =
        refined::Refined(std::string_view("hello"), refined::validator::equal_to<std::string_view>("hello"));
    REQUIRE(equal_to_hello.has_value());
    REQUIRE(equal_to_hello.value() == "hello");

    equal_to_hello = "world";
    REQUIRE_FALSE(equal_to_hello.has_value());
    REQUIRE(equal_to_hello.value() == std::nullopt);

    auto not_equal_to_hello =
        refined::Refined(std::string_view("world"), refined::validator::equal_to<std::string_view>("hello"));
    REQUIRE_FALSE(not_equal_to_hello.has_value());
    REQUIRE(not_equal_to_hello.value() == std::nullopt);

    auto equal_to_world =
        refined::Refined(std::string_view("world"), refined::validator::equal_to<std::string_view>("world"));
    REQUIRE(equal_to_world.has_value());
    REQUIRE(equal_to_world.value() == "world");
    REQUIRE_FALSE(equal_to_world == equal_to_hello);

    auto another_equal_to_world =
        refined::Refined(std::string_view("world"), refined::validator::equal_to<std::string_view>("world"));
    REQUIRE(equal_to_world == another_equal_to_world);
  }
}

// NOLINTEND