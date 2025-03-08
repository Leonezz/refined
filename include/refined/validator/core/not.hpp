#pragma once

#include "./validator.hpp"
namespace refined::validator {
template <ValidatorConcept Validator> struct Not {
  using is_validator = void;

  [[no_unique_address]] Validator validator{};
  constexpr explicit Not(Validator validator) : validator(std::move(validator)) {}

  [[nodiscard]] constexpr auto operator()(auto const &value) const -> bool { return not validator(value); }
};

template <ValidatorConcept Validator>
[[nodiscard]] constexpr auto operator not(Validator const &validator) -> Not<Validator> {
  return Not<Validator>(validator);
}
} // namespace refined::validator