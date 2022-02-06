# fp

FP (Functional Programming) extensions for C++

[![CI](https://github.com/tylerjw/fp/actions/workflows/ci.yaml/badge.svg?branch=main)](https://github.com/tylerjw/fp/actions/workflows/ci.yaml?query=branch%3Amain)
[![Doxygen](https://github.com/tylerjw/fp/actions/workflows/doxygen.yaml/badge.svg?branch=main)](https://github.com/tylerjw/fp/actions/workflows/doxygen.yaml?query=branch%3Amain)
[![Space Metric](https://tylerjw.testspace.com/spaces/162241/badge?token=942f36be0e57d277368e06dd911d23098a89be84)](https://tylerjw.testspace.com/spaces/162241?utm_campaign=badge&utm_medium=referral&utm_source=test "Test Cases")
[![Code Coverage](https://codecov.io/gh/tylerjw/fp/branch/main/graph/badge.svg?token=W7uHKcY0ly)](https://codecov.io/gh/tylerjw/fp)

[![license](https://img.shields.io/github/license/tylerjw/fp)](https://github.com/tylerjw/fp/blob/main/LICENSE)
[![cpp](https://img.shields.io/badge/C%2B%2B-17-blue)](#)
[![ROS](https://img.shields.io/badge/ROS-rolling-blue)](#)
[![Dependencies](https://img.shields.io/badge/Dependencies-fmt%2C%20range--v3-blue)](#)
[![Released](https://img.shields.io/badge/Released-no!-red)](#)

## Getting started

**upstream.repos**
```yaml
  fp:
    type: git
    url: https://github.com/tylerjw/fp
    version: main
```

**package.xml**
```xml
<depend>fp</depend>
```

**CMakeLists.txt**
```cmake
find_package(fp REQUIRED)

target_link_libraries(your_library
  fp::fp
)
```

**include in source**
```cpp
#include <fp/all.hpp>
```

## Tutorials

1. [Functions that can fail](doc/1_functions_that_can_fail.md)
2. [Combining Result<T>s](doc/2_combining_results.md)
3. [Chaining functions that return Result<T>](doc/3_chaining_functions.md)
4. [Validating values](doc/4_validate.md)

[API Documentation](https://tylerjw.github.io/fp/)

## Vendored libraries

- [tl::expected library](https://tl.tartanllama.xyz/en/latest/api/expected.html#tl-expected)

## Interface Dependencies

These dependencies are added to the cmake INTERFACE library `fp`.

- [fmtlib: A modern formatting library](https://fmt.dev/latest/index.html)
- [range-v3: Range library, basis for C++20's std::ranges](https://ericniebler.github.io/range-v3/)

## Achnologements

- ['Functional Programming in C++' by Ivan Čukić](https://www.manning.com/books/functional-programming-in-c-plus-plus)
- [ABSL `StatusOr`](https://github.com/abseil/abseil-cpp/blob/master/absl/status/statusor.h)
