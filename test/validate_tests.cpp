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

#include "gtest/gtest.h"
#include "monad/all.hpp"

TEST(ValidateTests, ValidateRangeFromIntTrue) {
  // GIVEN validation of the range [-10, inf, -]
  const auto test = validate::range<int>{.from = -10};

  // WHEN we we validate the value 14
  const auto result = test(14);

  // THEN we expect it be true
  EXPECT_TRUE(result);
}

TEST(ValidateTests, ValidateRangeFromIntFalse) {
  // GIVEN validation of the range [-10, inf, -]
  const auto test = validate::range<int>{.from = -10};

  // WHEN we we validate the value -100
  const auto result = test(-100);

  // THEN we expect it be false
  EXPECT_FALSE(result);
}

TEST(ValidateTests, ValidateRangeFalseIsOutOfRange) {
  // GIVEN validation of the range [-10, inf, -]
  const auto test = validate::range<int>{.from = -10};

  // WHEN we we validate the value -100
  const auto result = test(-100);

  // THEN we expect the error code to be OutOfRange
  EXPECT_EQ(result.error().code, ErrorCode::OUT_OF_RANGE);
}

TEST(ValidateTests, ValidateRangeToIntFalse) {
  // GIVEN validation of the range [-inf, 4, -]
  const auto test = validate::range<int>{.to = 4};

  // WHEN we we validate the value 5
  const auto result = test(5);

  // THEN we expect it be false
  EXPECT_FALSE(result);
}

TEST(ValidateTests, ValidateRangeStepInt) {
  // GIVEN validation of the range [0, inf, 3]
  const auto test = validate::range<int>{.from = 0, .step = 3};

  // WHEN we we validate the value 14
  const auto result = test(14);

  // THEN we expect it be false
  EXPECT_FALSE(result);
}

TEST(ValidateTests, ValidateRangeToDoubleTrue) {
  // GIVEN validation of the range [-inf, inf, 2]
  const auto test = validate::range<double>{.step = 2};

  // WHEN we we validate the value 4
  const auto result = test(4);

  // THEN we expect it be true
  EXPECT_TRUE(result) << fmt::format("{}", result);
}

TEST(ValidateTests, ValidateRangeToDoubleFalse) {
  // GIVEN validation of the range [-inf, inf, 2]
  const auto test = validate::range<double>{.step = 2};

  // WHEN we we validate the value 5
  const auto result = test(5);

  // THEN we expect it be false
  EXPECT_FALSE(result) << fmt::format("{}", result);
}

TEST(ValidateTests, ValidateInTrue) {
  // GIVEN string "a" and the set {"a", "b", "c"}
  const auto value = "a";
  const auto valid_values = std::set<std::string>{"a", "b", "c"};

  // WHEN we we validate with in
  const auto result = validate::in(valid_values, value);

  // THEN we expect it be true
  EXPECT_TRUE(result) << fmt::format("{}", result);
}

TEST(ValidateTests, ValidateInFalse) {
  // GIVEN string "z" and the set {"a", "b", "c"}
  const auto value = "z";
  const auto valid_values = std::set<std::string>{"a", "b", "c"};

  // WHEN we we validate with in
  const auto result = validate::in(valid_values, value);

  // THEN we expect it be false
  EXPECT_FALSE(result) << fmt::format("{}", result);
}

TEST(ValidateTests, PrependNameNoThrow) {
  // GIVEN a error value
  const auto error = DataLoss("something went wrong");

  // WHEN we call make_named
  // THEN we expect it to not throw
  EXPECT_NO_THROW(const auto _ = validate::make_named(error, "foo"))
      << fmt::format("{}", error);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
