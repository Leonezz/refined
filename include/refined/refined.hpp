#pragma once
#include <functional>
#include <optional>
#include <type_traits>
#include <utility>
namespace refined {
template <typename T, typename Validator>
  requires std::invocable<Validator, T> && std::same_as<std::invoke_result_t<Validator, T const &>, bool>
class Refined {
  T origin_value;
  Validator validator;
  std::optional<T> valid_value;

  static constexpr inline bool is_nothrow_validatable = std::is_nothrow_invocable_r_v<bool, Validator, T const &>;
  static constexpr inline bool is_nothrow_copy_constructible =
      std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_copy_constructible_v<Validator>;
  static constexpr inline bool is_nothrow_copy_assignable =
      std::is_nothrow_copy_assignable_v<T> && std::is_nothrow_copy_assignable_v<Validator>;
  template <typename... Args>
  static constexpr inline bool is_nothrow_constructible_from =
      std::is_nothrow_constructible_v<T, Args...> && is_nothrow_validatable;

public:
  constexpr inline explicit Refined(T const &value, Validator validator = {}) noexcept(
      std::is_nothrow_copy_constructible_v<T> && std::is_nothrow_move_constructible_v<Validator> &&
      is_nothrow_validatable)
      : origin_value(value), validator(std::move(validator)),
        valid_value(this->validator(origin_value) ? std::optional{value} : std::nullopt) {}

  inline ~Refined() noexcept = default;

  constexpr inline Refined(const Refined &other) noexcept(is_nothrow_copy_constructible) = default;

  constexpr inline Refined(Refined &&other) noexcept { *this = std::move(other); }

  [[nodiscard]] constexpr inline auto operator=(const Refined &) noexcept(is_nothrow_copy_assignable)
      -> Refined & = default;

  [[nodiscard]] constexpr inline auto operator=(Refined &&other) noexcept -> Refined & {
    validator = std::move(other.validator);
    origin_value = std::move(other.origin_value);
    valid_value = std::move(other.valid_value);
    return *this;
  }

  [[nodiscard]] constexpr inline auto operator=(T const &other) noexcept(std::is_nothrow_copy_assignable_v<T> &&
                                                                         is_nothrow_validatable) -> Refined & {
    origin_value = other;
    valid_value = validator(other) ? valid_value : std::nullopt;
    return *this;
  }

  [[nodiscard]] constexpr inline auto operator=(T &&other) noexcept(std::is_nothrow_move_assignable_v<T> &&
                                                                    std::is_nothrow_copy_assignable_v<T> &&
                                                                    is_nothrow_validatable) -> Refined & {
    origin_value = std::move(other);
    valid_value = validator(origin_value) ? std::optional{origin_value} : std::nullopt;
    return *this;
  }

  template <typename Mutate>
    requires std::invocable<Mutate, T &>
  [[nodiscard]] constexpr inline auto mutate(Mutate &&mutate) -> bool {
    std::invoke(std::forward<Mutate>(mutate), this->origin_value);
    const auto valid = this->validator(this->origin_value);
    this->valid_value = valid ? std::optional{this->origin_value} : std::nullopt;
    return valid;
  }

  template <typename... Args>
  [[nodiscard]] constexpr inline auto operator=(Args &&...args) noexcept(is_nothrow_constructible_from<Args...>)
      -> Refined & {
    origin_value = T(std::forward<Args>(args)...);
    valid_value = validator(origin_value) ? std::optional{origin_value} : std::nullopt;
    return *this;
  }

  [[nodiscard]] constexpr inline auto operator==(Refined const &other) const -> bool {
    return valid_value == other.valid_value;
  }

  [[nodiscard]] constexpr inline auto operator!=(Refined const &other) const -> bool { return !(*this) == other; }

  template <typename U, typename UValidator>
  [[nodiscard]] constexpr inline auto operator==(Refined<U, UValidator> const &other) const -> bool {
    return valid_value == other.value();
  }

  template <typename U, typename UValidator>
  [[nodiscard]] constexpr inline auto operator!=(Refined<U, UValidator> const &other) const -> bool {
    return !(*this) == other;
  }

  [[nodiscard]] constexpr inline auto has_value() const noexcept -> bool { return valid_value.has_value(); }

  [[nodiscard]] constexpr inline auto value() const -> std::optional<T> {
    if (!valid_value.has_value()) {
      return {};
    }
    return valid_value.value();
  }
};

template <typename T, typename Validator>
  requires std::invocable<Validator, T> && std::same_as<std::invoke_result_t<Validator, T const &>, bool>
Refined(T const &, Validator) -> Refined<T, Validator>;

} // namespace refined