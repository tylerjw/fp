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

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <cmath>
#include <limits>
#include <optional>
#include <range/v3/all.hpp>

#include "fp/result.hpp"

namespace fp {

/**
 * @brief      Validate a range
 *
 * @tparam     T     The type of value
 *
 * @example    validate_range.cpp
 *             This is an example of how to use range
 */
template <typename T>
struct validate_range {
  T from = std::numeric_limits<T>::min();
  T to = std::numeric_limits<T>::max();
  std::optional<T> step = std::nullopt;
  double step_threshold = 1e-3;

  constexpr Result<T> operator()(T value) const {
    if (value < from || value > to) {
      return tl::make_unexpected(OutOfRange(
          fmt::format("{} is outside of the range [{}, {}]", value, from, to)));
    }

    if (step) {
      const double step_value = static_cast<double>(step.value());
      const double ratio = static_cast<double>(value - from) / step_value;
      const double distance = fabs(ratio - round(ratio));

      if (distance > step_threshold) {
        return tl::make_unexpected(OutOfRange(fmt::format(
            "{} is {} away from the nearest valid step", value, distance)));
      }
    }

    return value;
  }
};

/**
 * @brief      Validate that the value is contained on the set of valid_values
 *
 * @param[in]  valid_values  The valid values
 * @param[in]  value         The value
 *
 * @tparam     Rng           The type of valid_values, deduced
 * @tparam     T             The type of the value, deduced
 *
 * @return     OutOfRange error if value is not in valid_values
 *
 * @example    validate_in.cpp
 *             This is an example of how to use in
 */
template <typename Rng, typename T>
constexpr Result<T> validate_in(const Rng& valid_values, const T& value) {
  if (ranges::contains(valid_values, value)) {
    return value;
  }
  return tl::make_unexpected(
      OutOfRange(fmt::format("{} is not in {}", value, valid_values)));
  ;
}

/**
 * @brief      Makes a named error.  Useful when validating parameters.
 *
 * @param[in]  error  The error
 * @param[in]  name   The name
 *
 * @return     Prepends "{name}: " to the Error what string
 */
const auto make_named = [](const Error& error, const std::string& name) {
  return Error{.code = error.code,
               .what = fmt::format("{}: {}", name, error.what)};
};

}  // namespace fp
