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

#include "gtest/gtest.h"
#include "monad/all.hpp"

TEST(ResultTests, OkErrorTrue) {
  // GIVEN Ok error
  const auto error = Ok();

  // WHEN we cast to bool
  // THEN we expect it to be true
  EXPECT_TRUE(error);
}

TEST(ResultTests, CanceledErrorFalse) {
  // GIVEN Canceled error
  const auto error = Canceled();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, UnknownErrorFalse) {
  // GIVEN Unknown error
  const auto error = Unknown();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, InvalidArgumentErrorFalse) {
  // GIVEN InvalidArgument error
  const auto error = InvalidArgument();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, TimeoutErrorFalse) {
  // GIVEN Timeout error
  const auto error = Timeout();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, NotFoundErrorFalse) {
  // GIVEN NotFound error
  const auto error = NotFound();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, AlreadyExistsErrorFalse) {
  // GIVEN AlreadyExists error
  const auto error = AlreadyExists();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, PermissionDeniedErrorFalse) {
  // GIVEN PermissionDenied error
  const auto error = PermissionDenied();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, ResourceExhaustedErrorFalse) {
  // GIVEN ResourceExhausted error
  const auto error = ResourceExhausted();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, FailedPreconditionErrorFalse) {
  // GIVEN FailedPrecondition error
  const auto error = FailedPrecondition();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, AbortedErrorFalse) {
  // GIVEN Aborted error
  const auto error = Aborted();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, OutOfRangeErrorFalse) {
  // GIVEN OutOfRange error
  const auto error = OutOfRange();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, UnimplementedErrorFalse) {
  // GIVEN Unimplemented error
  const auto error = Unimplemented();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, InternalErrorFalse) {
  // GIVEN Internal error
  const auto error = Internal();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, UnavailableErrorFalse) {
  // GIVEN Unavailable error
  const auto error = Unavailable();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, DataLossErrorFalse) {
  // GIVEN DataLoss error
  const auto error = DataLoss();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, UnauthenticatedErrorFalse) {
  // GIVEN Unauthenticated error
  const auto error = Unauthenticated();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, ExceptionErrorFalse) {
  // GIVEN Exception error
  const auto error = Exception();

  // WHEN we cast to bool
  // THEN we expect it to be false
  EXPECT_FALSE(error);
}

TEST(ResultTests, ErrorEqualityTrue) {
  // Given two different Ok Errors
  const auto first_error = Ok();
  const auto second_error = Ok();

  // WHEN we test their equality
  // THEN we expect it to be true
  EXPECT_EQ(first_error, second_error)
      << fmt::format("{} == {}", first_error, second_error);
}

TEST(ResultTests, ErrorEqualityCodeFalse) {
  // Given two different errors with different codes
  const auto first_error = Ok();
  const auto second_error = Unknown();

  // WHEN we test their equality
  // THEN we expect it to be false
  EXPECT_NE(first_error, second_error)
      << fmt::format("{} != {}", first_error, second_error);
}

TEST(ResultTests, ErrorEqualityWhatFalse) {
  // Given two different errors with different strings
  const auto first_error = Timeout("foo");
  const auto second_error = Timeout("bar");

  // WHEN we test their equality
  // THEN we expect it to be false
  EXPECT_NE(first_error, second_error)
      << fmt::format("{} != {}", first_error, second_error);
}

TEST(ResultTests, FormatErrorNoThrow) {
  // GIVEN a Error
  const auto error = Exception();

  // WHEN we call fmt::format on it
  // THEN we expect it not to throw
  EXPECT_NO_THROW(fmt::format("{}", error));
}

TEST(ResultTests, FormatResultValueNoThrow) {
  // GIVEN a Result<int> with a value
  const auto result = Result<int>{4};

  // WHEN we call fmt::format on it
  // THEN we expect it not to throw
  EXPECT_NO_THROW(fmt::format("{}", result));
}

TEST(ResultTests, FormatResultErrorNoThrow) {
  // GIVEN a Result<int> with an error
  const auto result = Result<int>{make_unexpected(DataLoss())};

  // WHEN we call fmt::format on it
  // THEN we expect it not to throw
  EXPECT_NO_THROW(fmt::format("{}", result));
}

TEST(ResultTests, StringToViewNoThrow) {
  // GIVEN each type of error
  const auto each_type_of_error =
      ranges::views::iota(static_cast<int>(ErrorCode::OK),
                          static_cast<int>(ErrorCode::__END)) |
      ranges::views::transform(
          [](int i) { return static_cast<ErrorCode>(i); }) |
      ranges::to<std::vector>();

  // WHEN we call toStringView with each type of Error
  // THEN we expect it doesn't throw
  for (const auto& error : each_type_of_error) {
    EXPECT_NO_THROW(const auto _ = toStringView(error));
  }
}

TEST(ResultTests, MaybeError) {
  // GIVEN two Result<T> values
  const Result<double> a = 6.5;
  const Result<int> b = make_unexpected(Unknown());

  // WHEN we call maybe_error on those results
  const auto error = maybe_error(a, b);

  // THEN we expect it to have the Unknown error
  EXPECT_TRUE(error);
  EXPECT_EQ(error.value().code, ErrorCode::UNKNOWN);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
