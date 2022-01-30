// Copyright 2022 PickNik Inc
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
//    * Neither the name of the PickNik Inc nor the names of its
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

// #include <fmt/ranges.h>
#include <monad/all.hpp>

namespace views = ::ranges::views;

Result<double> divide_4_by(double x) {
  if (x == 0.0) {
    return make_unexpected(InvalidArgument(fmt::format("divide by 0")));
  }
  return 4.0 / x;
}

Result<double> safe_sqrt(double x) {
  if (x < 0) {
    return make_unexpected(InvalidArgument(
        fmt::format("sqrt of value < 0.0 is undefined: {}", x)));
  }

  return sqrt(x);
}

Result<double> do_math(double x) {
  return make_result(x).and_then(divide_4_by).and_then(safe_sqrt);
}

void print_errors(Result<double> result) {
  if (!result.has_value()) {
    fmt::print("{}\n", result.error());
  }
}

int main() {
  const auto x = views::iota(-5, 10) |
                 views::transform([](const int& x) { return x * 0.2; }) |
                 ranges::to<std::vector>();
  const auto y =
      x | views::transform(do_math) | views::filter([](const auto& result) {
        print_errors(result);
        return result.has_value();
      }) |
      views::transform([](const auto& result) { return result.value(); }) |
      ranges::to<std::vector>();

  fmt::print("y = sqrt(4.0 / x)\nx = {}\ny = {}\n", x, y);

  // Output:
  // [Error: [InvalidArgument] sqrt of value < 0.0 is undefined: -4.0]
  // [Error: [InvalidArgument] sqrt of value < 0.0 is undefined: -5.0]
  // [Error: [InvalidArgument] sqrt of value < 0.0 is undefined:
  //   -6.666666666666666]
  // [Error: [InvalidArgument] sqrt of value < 0.0 is
  //   undefined: -10.0]
  // [Error: [InvalidArgument] sqrt of value < 0.0 is
  //   undefined: -20.0]
  // [Error: [InvalidArgument] divide by 0]
  // y = sqrt(4.0 / x)
  // x = {-1.0, -0.8, -0.6000000000000001, -0.4, -0.2, 0.0, 0.2, 0.4,
  //   0.6000000000000001, 0.8, 1.0, 1.2000000000000002, 1.4000000000000001,
  //   1.6, 1.8}
  // y = {4.47213595499958, 3.1622776601683795, 2.581988897471611,
  //   2.23606797749979, 2.0, 1.8257418583505536, 1.6903085094570331,
  //   1.5811388300841898, 1.4907119849998598}

  return 0;
}
