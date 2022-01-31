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

#include <cmath>
#include <functional>
#include <optional>
#include <stdexcept>

#include "gtest/gtest.h"
#include "monad/all.hpp"

using namespace monad;

std::optional<int> maybe_non_zero(int in) {
  return (in == 0) ? std::nullopt : make_opt(in);
}

std::optional<int> maybe_lt_3_round(double in) {
  return (in < 3) ? make_opt(round(in)) : std::nullopt;
}

Result<double> divide_4_by(double val) {
  if (val == 0) {
    return make_unexpected(InvalidArgument());
  }
  return 4.0 / val;
}

double unsafe_divide_4_by(double val) {
  if (val == 0.0) {
    throw std::runtime_error("divide by zero");
  }
  return 4.0 / val;
}

TEST(MBindTests, MBindOptValueTest) {
  // GIVEN optional value 4
  const auto opt = make_opt(4);

  // WHEN we mbind it with the function maybe_non_zero
  // THEN we expect it true
  EXPECT_TRUE(mbind(opt, maybe_non_zero));
}

TEST(MBindTests, OverloadedOrOptValueTest) {
  // GIVEN optional value -4.0
  const auto opt = make_opt(-4.0);

  // WHEN we mbind it with two functions chained with operator| overload
  // THEN we expect it true
  EXPECT_TRUE((opt | maybe_lt_3_round | maybe_non_zero));
}

TEST(MBindTests, MBindOptNoValueTest) {
  // GIVEN optional non value
  const auto opt = std::optional<int>{std::nullopt};

  // WHEN we mbind it with the function maybe_non_zero
  // THEN we expect it false
  EXPECT_FALSE(mbind(opt, maybe_non_zero));
}

TEST(MBindTests, MBindOptNoValueOutputTest) {
  // GIVEN optional value with 0.0
  const auto opt = std::optional<int>{0.0};

  // WHEN we mbind it with the function maybe_non_zero
  // THEN we expect it false
  EXPECT_FALSE(mbind(opt, maybe_non_zero));
}

TEST(MBindTests, MBindResultValueTest) {
  // GIVEN input with value 4.9
  const auto input = 4.9;

  // WHEN we mbind it with the function divide_4_by
  // THEN we expect it true
  EXPECT_TRUE(mbind(make_result(input), divide_4_by));
}

TEST(MBindTests, MBindResultOutputErrorTest) {
  // GIVEN input with value 0.0
  const auto input = Result<double>{make_unexpected(InvalidArgument())};

  EXPECT_FALSE(input);

  // WHEN we mbind it with the function divide_4_by
  // THEN we expect it false
  EXPECT_FALSE(mbind(input, divide_4_by));
}

TEST(MBindTests, MBindInputErrorTest) {
  // GIVEN input with value error
  const auto input = 0.0;

  // WHEN we mbind it with the function divide_4_by
  // THEN we expect it false
  EXPECT_FALSE(mbind(make_result(input), divide_4_by));
}

TEST(MBindTests, MBindResultValueOperatorChainTest) {
  // GIVEN input with value 4.9
  const auto input = 4.9;

  // WHEN we mbind it with the function divide_4_by twice
  // THEN we expect it true
  EXPECT_TRUE((make_result(input) | divide_4_by | divide_4_by));
}

TEST(MBindTests, MTryTest) {
  // GIVEN input value of 0.0
  const auto input = 0.0;

  // WHEN we pass unsafe_divide_4_by to mtry with out input
  // THEN we expect it to not throw
  EXPECT_NO_THROW(mtry(std::bind(&unsafe_divide_4_by, input)));
}

TEST(MBindTests, MTryOkTest) {
  // GIVEN input value of 4.3
  const auto input = 4.3;

  // WHEN we pass unsafe_divide_4_by to mtry with out input
  // THEN we expect it to not throw
  EXPECT_NO_THROW(mtry(std::bind(&unsafe_divide_4_by, input)));
}

TEST(MBindTests, MComposeTwo) {
  // GIVEN the functions maybe_non_zero and maybe_lt_3_round and an input opt
  const auto opt = make_opt(-4.0);

  // WHEN we compose them together and then bind them with an input
  const auto compose_result = opt | mcompose(maybe_lt_3_round, maybe_non_zero);

  // THEN we expect the result to be the same as if we chained the calls
  // together
  const auto chain_result = opt | maybe_lt_3_round | maybe_non_zero;

  EXPECT_EQ(compose_result, chain_result);
}

TEST(MBindTests, MComposeThree) {
  // GIVEN the functions maybe_non_zero and maybe_lt_3_round and an input opt
  const auto opt = make_opt(-4.0);

  // WHEN we compose them together multiple times and then bind them with an
  // input
  const auto compose_result =
      opt | mcompose(maybe_lt_3_round, maybe_non_zero, maybe_non_zero);

  // THEN we expect the result to be the same as if we chained the calls
  // together
  const auto chain_result =
      opt | maybe_lt_3_round | maybe_non_zero | maybe_non_zero;

  EXPECT_EQ(compose_result, chain_result);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
