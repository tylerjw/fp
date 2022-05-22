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

#include "fp/all.hpp"
#include "gtest/gtest.h"

TEST(ResultTests, CancelledErrorFalse) {
  // GIVEN Cancelled error
  const auto error = fp::Cancelled();

  // WHEN we read the code
  // THEN we expect it to be Canceled
  EXPECT_EQ(error.code, fp::ErrorCode::CANCELLED);
}

TEST(ResultTests, UnknownErrorFalse) {
  // GIVEN Unknown error
  const auto error = fp::Unknown();

  // WHEN we read the code
  // THEN we expect it to be Unknown
  EXPECT_EQ(error.code, fp::ErrorCode::UNKNOWN);
}

TEST(ResultTests, InvalidArgumentErrorFalse) {
  // GIVEN InvalidArgument error
  const auto error = fp::InvalidArgument();

  // WHEN we read the code
  // THEN we expect it to be InvalidArgument
  EXPECT_EQ(error.code, fp::ErrorCode::INVALID_ARGUMENT);
}

TEST(ResultTests, TimeoutErrorFalse) {
  // GIVEN Timeout error
  const auto error = fp::Timeout();

  // WHEN we read the code
  // THEN we expect it to be Timeout
  EXPECT_EQ(error.code, fp::ErrorCode::TIMEOUT);
}

TEST(ResultTests, NotFoundErrorFalse) {
  // GIVEN NotFound error
  const auto error = fp::NotFound();

  // WHEN we read the code
  // THEN we expect it to be NotFound
  EXPECT_EQ(error.code, fp::ErrorCode::NOT_FOUND);
}

TEST(ResultTests, AlreadyExistsErrorFalse) {
  // GIVEN AlreadyExists error
  const auto error = fp::AlreadyExists();

  // WHEN we read the code
  // THEN we expect it to be AlreadyExists
  EXPECT_EQ(error.code, fp::ErrorCode::ALREADY_EXISTS);
}

TEST(ResultTests, PermissionDeniedErrorFalse) {
  // GIVEN PermissionDenied error
  const auto error = fp::PermissionDenied();

  // WHEN we read the code
  // THEN we expect it to be PermissionDenied
  EXPECT_EQ(error.code, fp::ErrorCode::PERMISSION_DENIED);
}

TEST(ResultTests, ResourceExhaustedErrorFalse) {
  // GIVEN ResourceExhausted error
  const auto error = fp::ResourceExhausted();

  // WHEN we read the code
  // THEN we expect it to be ResourceExhausted
  EXPECT_EQ(error.code, fp::ErrorCode::RESOURCE_EXHAUSTED);
}

TEST(ResultTests, FailedPreconditionErrorFalse) {
  // GIVEN FailedPrecondition error
  const auto error = fp::FailedPrecondition();

  // WHEN we read the code
  // THEN we expect it to be FailedPrecondition
  EXPECT_EQ(error.code, fp::ErrorCode::FAILED_PRECONDITION);
}

TEST(ResultTests, AbortedErrorFalse) {
  // GIVEN Aborted error
  const auto error = fp::Aborted();

  // WHEN we read the code
  // THEN we expect it to be Aborted
  EXPECT_EQ(error.code, fp::ErrorCode::ABORTED);
}

TEST(ResultTests, OutOfRangeErrorFalse) {
  // GIVEN OutOfRange error
  const auto error = fp::OutOfRange();

  // WHEN we read the code
  // THEN we expect it to be OutOfRange
  EXPECT_EQ(error.code, fp::ErrorCode::OUT_OF_RANGE);
}

TEST(ResultTests, UnimplementedErrorFalse) {
  // GIVEN Unimplemented error
  const auto error = fp::Unimplemented();

  // WHEN we read the code
  // THEN we expect it to be Unimplemented
  EXPECT_EQ(error.code, fp::ErrorCode::UNIMPLEMENTED);
}

TEST(ResultTests, InternalErrorFalse) {
  // GIVEN Internal error
  const auto error = fp::Internal();

  // WHEN we read the code
  // THEN we expect it to be Internal
  EXPECT_EQ(error.code, fp::ErrorCode::INTERNAL);
}

TEST(ResultTests, UnavailableErrorFalse) {
  // GIVEN Unavailable error
  const auto error = fp::Unavailable();

  // WHEN we read the code
  // THEN we expect it to be Unavailable
  EXPECT_EQ(error.code, fp::ErrorCode::UNAVAILABLE);
}

TEST(ResultTests, DataLossErrorFalse) {
  // GIVEN DataLoss error
  const auto error = fp::DataLoss();

  // WHEN we read the code
  // THEN we expect it to be DataLoss
  EXPECT_EQ(error.code, fp::ErrorCode::DATA_LOSS);
}

TEST(ResultTests, UnauthenticatedErrorFalse) {
  // GIVEN Unauthenticated error
  const auto error = fp::Unauthenticated();

  // WHEN we read the code
  // THEN we expect it to be Unauthenticated
  EXPECT_EQ(error.code, fp::ErrorCode::UNAUTHENTICATED);
}

TEST(ResultTests, ExceptionErrorFalse) {
  // GIVEN Exception error
  const auto error = fp::Exception();

  // WHEN we read the code
  // THEN we expect it to be Exception
  EXPECT_EQ(error.code, fp::ErrorCode::EXCEPTION);
}

TEST(ResultTests, ErrorEqualityTrue) {
  // Given two different Unknown Errors
  const auto first_error = fp::Unknown();
  const auto second_error = fp::Unknown();

  // WHEN we test their equality
  // THEN we expect it to be true
  EXPECT_EQ(first_error, second_error)
      << fmt::format("{} == {}", first_error, second_error);
}

TEST(ResultTests, ErrorEqualityCodeFalse) {
  // Given two different errors with different codes
  const auto first_error = fp::Timeout();
  const auto second_error = fp::Unknown();

  // WHEN we test their equality
  // THEN we expect it to be false
  EXPECT_NE(first_error, second_error)
      << fmt::format("{} != {}", first_error, second_error);
}

TEST(ResultTests, ErrorEqualityWhatFalse) {
  // Given two different errors with different strings
  const auto first_error = fp::Timeout("foo");
  const auto second_error = fp::Timeout("bar");

  // WHEN we test their equality
  // THEN we expect it to be false
  EXPECT_NE(first_error, second_error)
      << fmt::format("{} != {}", first_error, second_error);
}

TEST(ResultTests, FormatErrorNoThrow) {
  // GIVEN a Error
  const auto error = fp::Exception();

  // WHEN we call fmt::format on it
  // THEN we expect it not to throw
  EXPECT_NO_THROW(auto const _ = fmt::format("{}", error));
}

TEST(ResultTests, FormatResultValueNoThrow) {
  // GIVEN a Result<int> with a value
  const auto result = fp::Result<int>{4};

  // WHEN we call fmt::format on it
  // THEN we expect it not to throw
  EXPECT_NO_THROW(auto const _ = fmt::format("{}", result));
}

TEST(ResultTests, FormatResultErrorNoThrow) {
  // GIVEN a Result<int> with an error
  const auto result = fp::Result<int>{tl::make_unexpected(fp::DataLoss())};

  // WHEN we call fmt::format on it
  // THEN we expect it not to throw
  EXPECT_NO_THROW(auto const _ = fmt::format("{}", result));
}

TEST(ResultTests, StringToViewNoThrow) {
  // GIVEN each type of error
  const auto each_type_of_error =
      ranges::views::iota(static_cast<int>(fp::ErrorCode::UNKNOWN),
                          static_cast<int>(fp::ErrorCode::EXCEPTION) + 1) |
      ranges::views::transform(
          [](int i) { return static_cast<fp::ErrorCode>(i); }) |
      ranges::to<std::vector>();

  // WHEN we call toStringView with each type of Error
  // THEN we expect it doesn't throw
  for (const auto& error : each_type_of_error) {
    EXPECT_NO_THROW(const auto _ = fp::toStringView(error));
  }
}

TEST(ResultTests, MaybeError) {
  // GIVEN two Result<T> values
  const fp::Result<double> a = 6.5;
  const fp::Result<int> b = tl::make_unexpected(fp::Unknown());

  // WHEN we call maybe_error on those results
  const auto error = fp::maybe_error(a, b);

  // THEN we expect it to have the Unknown error
  EXPECT_TRUE(error);
  EXPECT_EQ(error.value().code, fp::ErrorCode::UNKNOWN);
}

TEST(ResultTests, TryToResultError) {
  // GIVEN function that throws an exception
  const auto f = [] {
    throw std::runtime_error("");
    return 0;
  };

  // WHEN I lift it with try_to_result
  const auto result = fp::try_to_result(f);

  // THEN I get a result with an error that has the code EXCEPTION
  ASSERT_FALSE(result) << fmt::format("{}", result);
  EXPECT_EQ(result.error().code, fp::ErrorCode::EXCEPTION)
      << fmt::format("{}", result);
}

TEST(ResultTests, TryToResultValue) {
  // GIVEN a function that returns a value
  const auto f = [] { return 0; };

  // WHEN I lift it with try_to_result
  const auto result = fp::try_to_result(f);

  // THEN I get the same value in the result as if I'd called the function
  ASSERT_TRUE(result) << fmt::format("{}", result);
  EXPECT_EQ(result.value(), f()) << fmt::format("{}", result);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
