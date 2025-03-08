#pragma once

#include "./validator.hpp"
namespace refined::validator {
template <ValidatorConcept LHS, ValidatorConcept RHS> struct Or {
  using is_validator = void;

  [[no_unique_address]] LHS lhs;
  [[no_unique_address]] RHS rhs;
  constexpr explicit Or(LHS lhs, RHS rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}

  constexpr auto operator()(auto const &value) const -> bool { return lhs(value) or rhs(value); }
};

template <ValidatorConcept LHS, ValidatorConcept RHS>
[[nodiscard]] constexpr auto operator or(LHS const &lhs, RHS const &rhs) -> Or<LHS, RHS> {
  return Or<LHS, RHS>(lhs, rhs);
}
} // namespace refined::validator
