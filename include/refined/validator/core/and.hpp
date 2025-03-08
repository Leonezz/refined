#pragma once
#include "./validator.hpp"
namespace refined::validator {
template <ValidatorConcept LHS, ValidatorConcept RHS> struct And {
  using is_validator = void;

  [[no_unique_address]] LHS lhs;
  [[no_unique_address]] RHS rhs;
  constexpr explicit And(LHS lhs, RHS rhs) : lhs(std::move(lhs)), rhs(std::move(rhs)) {}

  constexpr auto operator()(auto const &value) const -> bool { return lhs(value) and rhs(value); }
};

template <ValidatorConcept LHS, ValidatorConcept RHS>
[[nodiscard]] constexpr auto operator and(LHS const &lhs, RHS const &rhs) -> And<LHS, RHS> {
  return And<LHS, RHS>(lhs, rhs);
}

} // namespace refined::validator