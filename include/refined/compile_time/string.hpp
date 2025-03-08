#include <array>
#include <cstddef>
#include <string_view>
namespace refined::util {
template <size_t N> struct CompileTimeString {
  std::array<char, N> data{};

  constexpr CompileTimeString() noexcept = default;

  // NOLINTNEXTLINE(*-avoid-c-arrays, google-explicit-constructor)
  constexpr explicit CompileTimeString(const char (&str)[N]) noexcept {
    for (size_t i = 0; i < N; ++i) {
      data[i] = str[i];
    }
  }

  constexpr explicit CompileTimeString(const char *str, size_t size) noexcept {
    static_assert(size <= N, "CompileTimeString: size is larger than N");
    for (size_t i = 0; i < size; ++i) {
      // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
      data[i] = str[i];
    }
  }

  constexpr explicit CompileTimeString(std::string_view str) : CompileTimeString(str.data(), str.size()) {}

  [[nodiscard]] constexpr auto c_str() const noexcept -> const char * { return data.data(); }

  constexpr static std::integral_constant<std::size_t, N> capacity{};
  constexpr static std::integral_constant<std::size_t, N - 1U> size{};
  constexpr static std::integral_constant<bool, N == 1U> empty{};

  [[nodiscard]] constexpr auto begin() noexcept { return data.begin(); }
  [[nodiscard]] constexpr auto end() noexcept { return data.end() - 1; }
  [[nodiscard]] constexpr auto begin() const noexcept { return data.begin(); }
  [[nodiscard]] constexpr auto end() const noexcept { return data.end() - 1; }
  [[nodiscard]] constexpr auto rbegin() const noexcept { return ++data.rbegin(); }
  [[nodiscard]] constexpr auto rend() const noexcept { return data.rend(); }

  constexpr explicit operator std::string_view() const { return std::string_view{data.data(), size()}; }
};

template <std::size_t N, std::size_t M>
[[nodiscard]] constexpr auto operator==(CompileTimeString<N> const &lhs, CompileTimeString<M> const &rhs) -> bool {
  return static_cast<std::string_view>(lhs) == static_cast<std::string_view>(rhs);
}
} // namespace refined::util