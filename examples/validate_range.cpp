// Copyright 2022 Tyler Weaver
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
//    * Neither the name of the Tyler Weaver nor the names of its
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

#include <fp/all.hpp>

void validate_int_step() {
  const auto value = 14;
  const auto result =
      fp::validate_range<int>{.from = 0, .step = 3}(value, "foo");
  if (!result) {
    fmt::print("{} failed fp::validate_range with result: {}\n", value, result);
  } else {
    fmt::print("{} passed fp::validate_range with result: {}\n", value, result);
  }
}

void validate_double() {
  const auto value = -2.1;
  const auto result =
      fp::validate_range<double>{.from = -15, .to = 23}(value, "foo");
  if (!result) {
    fmt::print("{} failed fp::validate_range with result: {}\n", value, result);
  } else {
    fmt::print("{} passed fp::validate_range with result: {}\n", value, result);
  }
}

int main() {
  validate_int_step();
  // 14 failed fp::validate_range with result: [Result<T>: [Error:
  //   [OutOfRange] foo: 14 is 0.33333333333333304 away from the nearest valid
  //   step]]

  validate_double();
  // -2.1 passed fp::validate_range with result: [Result<T>: value=-2.1]
}
