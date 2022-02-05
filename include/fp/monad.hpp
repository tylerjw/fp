// Copyright (c) 2022, Tyler Weaver
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the Universität Hamburg nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <optional>

#include "fp/_external/expected.hpp"

namespace fp {

/**
 * @brief      Makes an optional<T> from a T value.
 *
 * @param[in]  value  The value
 *
 * @tparam     T      The type of value
 *
 * @return     A optional<T> containing the value
 */
template <typename T>
constexpr std::optional<T> make_opt(T value) {
  return std::optional<T>{value};
}

/**
 * @brief      Monad optional bind
 *
 * @param[in]  opt   The input optional
 * @param[in]  f     The function
 *
 * @tparam     T     The input type
 * @tparam     F     The function
 *
 * @return     Return type of f
 */
template <typename T, typename F>
constexpr auto mbind(const std::optional<T>& opt, F f)
    -> decltype(f(opt.value())) {
  if (opt) {
    return f(opt.value());
  } else {
    return {};
  }
}

/**
 * @brief      Monad tl::expected<T,E>
 *
 * @param[in]  exp   The tl::expected<T,E> input
 * @param[in]  f     The function to apply
 *
 * @tparam     T     The type for the input expected
 * @tparam     E     The error type
 * @tparam     F     The function
 * @tparam     Ret   The return type of the function
 *
 * @return     The return type of the function
 */
template <typename T, typename E, typename F,
          typename Ret = typename std::result_of<F(T)>::type>
constexpr Ret mbind(const tl::expected<T, E>& exp, F f) {
  if (exp) {
    return f(exp.value());
  }
  return tl::make_unexpected(exp.error());
}

/**
 * @brief      Monadic try, used to lift a function that throws an
 * exception one that returns an tl::expected<T, std::exception_ptr>
 *
 * @param[in]  f     The function to call
 *
 * @tparam     F     The function type
 * @tparam     Ret   The return value of the function
 * @tparam     Exp   The expected type
 *
 * @return     The return value of the function
 */
template <typename F, typename Ret = typename std::result_of<F()>::type,
          typename Exp = tl::expected<Ret, std::exception_ptr>>
Exp mtry(F f) {
  try {
    return Exp{f()};
  } catch (...) {
    return tl::make_unexpected(std::current_exception());
  }
}

/**
 * @brief      Monadic compose two monad functions
 *
 * @param[in]  f     The first function
 * @param[in]  g     The second function
 *
 * @tparam     F     The type of the first function
 * @tparam     G     The type of the second function
 *
 * @return     A functional composition of two monad functions
 */
template <typename F, typename G>
constexpr auto mcompose(F f, G g) {
  return [=](auto value) { return mbind(f(value), g); };
}

/**
 * @brief      Variadic mcompose
 *
 * @param[in]  t      The first function
 * @param[in]  g      The second function
 * @param[in]  vars   The rest of the functions
 *
 * @tparam     T      The type of the first function
 * @tparam     G      The type of the second function
 * @tparam     Types  The types of the rest of the functions
 *
 * @return     A functional composition of variadic monad functions
 */
template <typename T, typename G, typename... Types>
constexpr auto mcompose(T t, G g, Types... vars) {
  auto exp = mcompose(t, g);
  return mcompose(exp, vars...);
}

}  // namespace fp

/**
 * @brief      Overload of the | operator as bind
 *
 * @param[in]  opt   The input optional
 * @param[in]  f     The function
 *
 * @tparam     T     The input type
 * @tparam     F     The function
 *
 * @return     Return type of f
 */
template <typename T, typename F>
constexpr auto operator|(const std::optional<T>& opt, F f) {
  return fp::mbind(opt, f);
}

/**
 * @brief      Overload of the | operator as bind
 *
 * @param[in]  exp   The input tl::expected<T,E> value
 * @param[in]  f     The function to apply
 *
 * @tparam     T     The type for the input expected
 * @tparam     E     The error type
 * @tparam     F     The function
 * @tparam     Ret   The return type of the function
 *
 * @return     The return type of the function
 */
template <typename T, typename E, typename F,
          typename Ret = typename std::result_of<F(T)>::type>
constexpr Ret operator|(const tl::expected<T, E>& exp, F f) {
  return fp::mbind(exp, f);
}
