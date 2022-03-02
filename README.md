# fp

Functional Programming extensions to C++ for ROS projects.

[Tutorials and API Documentation](https://www.fplib.dev/)

[![CI](https://github.com/tylerjw/fp/actions/workflows/ci.yaml/badge.svg?branch=main)](https://github.com/tylerjw/fp/actions/workflows/ci.yaml?query=branch%3Amain)
[![Doxygen](https://github.com/tylerjw/fp/actions/workflows/doxygen.yaml/badge.svg?branch=main)](https://github.com/tylerjw/fp/actions/workflows/doxygen.yaml?query=branch%3Amain)
[![Space Metric](https://tylerjw.testspace.com/spaces/162241/badge?token=942f36be0e57d277368e06dd911d23098a89be84)](https://tylerjw.testspace.com/spaces/162241?utm_campaign=badge&utm_medium=referral&utm_source=test "Test Cases")
[![Code Coverage](https://codecov.io/gh/tylerjw/fp/branch/main/graph/badge.svg?token=W7uHKcY0ly)](https://codecov.io/gh/tylerjw/fp)
[![license](https://img.shields.io/github/license/tylerjw/fp)](https://github.com/tylerjw/fp/blob/main/LICENSE)
[![cpp](https://img.shields.io/badge/C%2B%2B-17-blue)](#)
[![ROS](https://img.shields.io/badge/ROS-rolling-blue)](#)
[![Dependencies](https://img.shields.io/badge/Dependencies-fmt%2C%20range--v3-blue)](#)
[![Vendored](https://img.shields.io/badge/Vendored-tl%3A%3Aexpected-blue)](https://tl.tartanllama.xyz/en/latest/api/expected.html#tl-expected)
[![Released](https://img.shields.io/badge/Released-bloomed-yellow)](#)

## Features

* `Error` type with enum and string
* `Result<T>` type is `tl::expected<T, Error>`
* format `Result<T>` and `Error` with fmt
* monadic bind overloaded `operator|`
* compose monadic functions
* lift functions that throw exceptions to returning `Result<T>`
* add `[[nodiscard]]` attribute to lambdas
* validation helper callables

### Acknowledgements

- [ABSL `StatusOr`](https://github.com/abseil/abseil-cpp/blob/master/absl/status/statusor.h)
- [Rust `Result`](https://doc.rust-lang.org/std/result/)
- ['Functional Programming in C++' by Ivan Čukić](https://www.manning.com/books/functional-programming-in-c-plus-plus)
