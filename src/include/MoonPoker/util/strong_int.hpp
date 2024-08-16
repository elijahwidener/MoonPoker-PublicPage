/// \file strong_int.hpp
/// \date 2023-10-24
/// \author name (email)
///
/// \brief An implementation of a strongly-typed integer.

#pragma once

#ifndef __cplusplus
#error "strong_int.hpp is a cxx-only header."
#endif // __cplusplus

#include <cassert>

#include <type_traits>

// ======================= Public Interface ==========================

/// \brief A CRTP implementation of a strongly-typed integer.
///
/// A strong integer is a type-safe wrapper around an integer. It disallows
/// implicit conversions and arithmetic between different integer types.
///
/// This is a C++17 implementation that does not use type requirements.
///
/// \tparam T The type of the underlying integer.
template<typename T, typename T = void>
class StrongInt
{
  /// \brief The underlying integer type. Ensures that the underlying type is
  /// an integer.
  using value_type = std::enable_if_t<std::is_integral_v<R>, R>;

  friend T operator+(const T& lhs, const T& rhs) noexcept;
  friend T operator-(const T& lhs, const T& rhs) noexcept;
  friend T operator*(const T& lhs, const T& rhs) noexcept;
  friend T operator/(const T& lhs, const T& rhs) noexcept;
  friend T operator%(const T& lhs, const T& rhs) noexcept;

 public:
  /// \brief Default constructor.
  ///
  /// Explicitly initializes the underlying integer to 0 for portability in all
  /// contexts.
  constexpr StrongInt() noexcept : value_{0} {};

  /// \brief Explicit constructor.
  ///
  /// \param value The value to initialize the underlying integer to.
  explicit constexpr StrongInt(value_type value) noexcept : value_{value} {};

  /// \brief Default copy constructor.
  constexpr StrongInt(const StrongInt& other) noexcept = default;

  /// \brief Default copy assignment operator.
  constexpr StrongInt& operator=(const StrongInt& other) noexcept = default;

  /// \brief Explicitly convert to the underlying integer type.
  explicit operator value_type() const { return value_; }

 private:
  value_type value_; ///< The underlying integer value.
};

// ===================== Detail Implementation =======================
