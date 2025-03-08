#pragma once
#include "core/validator.hpp"

namespace refined::validator {
template <typename T>
constexpr inline auto equal_to = [] [[nodiscard]] (T const &expected) constexpr {
  return Validator{[expected] [[nodiscard]] (T const &value) constexpr -> bool { return value == expected; }};
};

// we have to wrap the equal_to validator into a lambda to make the static type check work,
//    i.e. ct_equal_to<int, 0> and ct_equal_to<int, 1> are different types
// also we have to wrap it back to a Validator to make the validator composition work,
//    i.e. const auto com_validator = ct_equal_to<int, 0> or ct_equal_to<int, 1> is valid
template <typename T, T expected>
constexpr inline auto ct_equal_to =
    Validator{[] [[nodiscard]] (T const &value) { return equal_to<T>(expected)(value); }};

template <typename T>
constexpr inline auto greater_than = [] [[nodiscard]] (T const &min) constexpr {
  return Validator{[min] [[nodiscard]] (T const &value) constexpr -> bool { return value > min; }};
};

template <typename T, T min>
constexpr inline auto ct_greater_than =
    Validator{[] [[nodiscard]] (T const &value) { return greater_than<T>(min)(value); }};

template <typename T>
constexpr inline auto greater_or_equal_than = [] [[nodiscard]] (T const &min) constexpr {
  const auto equal_pred = equal_to<T>(min);
  const auto greater_pred = greater_than<T>(min);
  return Validator{equal_pred} or Validator{greater_pred};
};

template <typename T, T min>
constexpr inline auto ct_greater_or_equal_than =
    Validator{[] [[nodiscard]] (T const &value) { return greater_or_equal_than<T>(min)(value); }};

template <typename T>
constexpr inline auto less_than = [] [[nodiscard]] (T const &max) constexpr {
  const auto pred = [max](T const &value) constexpr -> bool { return value < max; };
  return Validator{pred};
};

template <typename T, T max>
constexpr inline auto ct_less_than = Validator{[] [[nodiscard]] (T const &value) { return less_than<T>(max)(value); }};

template <typename T>
constexpr inline auto less_or_euqal_than = [] [[nodiscard]] (T const &max) constexpr {
  const auto equal_pred = equal_to<T>(max);
  const auto less_pred = less_than<T>(max);
  return Validator{equal_pred} or Validator{less_pred};
};

template <typename T, T max>
constexpr inline auto ct_less_or_euqal_than =
    Validator{[] [[nodiscard]] (T const &value) { return less_or_euqal_than<T>(max)(value); }};

template <typename T>
constexpr inline auto in_range = [] [[nodiscard]] (T const &min, T const &max) constexpr {
  const auto greater_pred = greater_or_equal_than<T>(min);
  const auto less_pred = less_than<T>(max);
  return Validator{greater_pred} and Validator{less_pred};
};

template <typename T, T min, T max>
constexpr inline auto ct_in_range =
    Validator{[] [[nodiscard]] (T const &value) { return in_range<T>(min, max)(value); }};

}; // namespace refined::validator