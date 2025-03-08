#pragma once

#include "refined/validator/comparable.hpp"
#include <cstddef>
#include <refined/validator/core/validator.hpp>
namespace refined::validator {
template <typename T>
concept HasSize = requires(T value) {
  { value.size() } -> std::convertible_to<size_t>;
};

template <HasSize Container>
constexpr inline auto empty =
    Validator{[] [[nodiscard]] (Container const &value) { return ct_equal_to<size_t, 0>(value.size()); }};
} // namespace refined::validator