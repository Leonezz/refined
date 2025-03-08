#pragma once
#include <algorithm>
namespace refined::validator {
template <typename Pred> struct Validator {
  using is_validator = void;

  Pred validator{};
  constexpr explicit Validator(Pred validator = {}) : validator(std::move(validator)) {}

  constexpr auto operator()(auto const &value) const -> bool { return validator(value); }
};

template <typename T>
concept ValidatorConcept = requires { std::same_as<typename T::is_validator, void>; };
} // namespace refined::validator