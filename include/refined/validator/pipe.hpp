
#pragma once
#include <utility>
namespace refined::util {
template <typename T, typename... Pred>
  requires requires(T const &value, Pred &&...pred) {
    { ((std::forward<Pred>(pred)(value)) && ...) } -> std::same_as<bool>;
  }
constexpr auto inline pipe = [] [[nodiscard]] (Pred &&...pred) -> auto {
  return [... predicates = std::forward<Pred>(pred)] [[nodiscard]] (T const &value) {
    return ((std::forward<Pred>(predicates)(value)) && ...);
  };
};
} // namespace refined::util