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

#include <fp/all.hpp>

namespace views = ::ranges::views;

fp::Result<double> divide_4_by(double x) {
  if (x == 0.0) {
    return tl::make_unexpected(fp::InvalidArgument(fmt::format("divide by 0")));
  }
  return 4.0 / x;
}

fp::Result<double> f1(double x) { return divide_4_by(x); }
fp::Result<double> f2(double x) { return divide_4_by(x); }
fp::Result<double> f3(double x) { return divide_4_by(x); }
fp::Result<double> f4(double x) { return divide_4_by(x); }

fp::Result<double> do_work() {
  auto const a = fp::make_result(2.4) | f1 | f2;
  auto const b = fp::make_result(0.0) | f3 | f4;

  if (auto const error = fp::maybe_error(a, b); error) {
    return tl::make_unexpected(*error);
  }

  return *a + *b;
}

int main() {
  auto const result = do_work();
  fmt::print("result: {}\n", result);
  // result: [Result<T>: [Error: [InvalidArgument] divide by 0]]

  return 0;
}
