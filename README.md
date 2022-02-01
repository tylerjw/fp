# fp

FP (Functional Programming) extensions for C++

[![CI](https://github.com/tylerjw/fp/actions/workflows/ci.yaml/badge.svg?branch=main)](https://github.com/tylerjw/fp/actions/workflows/ci.yaml?query=branch%3Amain)
[![Doxygen](https://github.com/tylerjw/fp/actions/workflows/doxygen.yaml/badge.svg?branch=main)](https://github.com/tylerjw/fp/actions/workflows/doxygen.yaml?query=branch%3Amain)
[![Space Metric](https://tylerjw.testspace.com/spaces/162241/badge?token=942f36be0e57d277368e06dd911d23098a89be84)](https://tylerjw.testspace.com/spaces/162241?utm_campaign=badge&utm_medium=referral&utm_source=test "Test Cases")
[![Code Coverage](https://codecov.io/gh/tylerjw/fp/branch/main/graph/badge.svg?token=W7uHKcY0ly)](https://codecov.io/gh/tylerjw/fp)
[![license](https://img.shields.io/github/license/tylerjw/fp)](https://github.com/tylerjw/fp/blob/main/LICENSE)

## Getting started

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

For more info see the [:memo: Detailed Documentation](https://tylerjw.github.io/fp/)

## Vendored libraries

- [tl::expected library](https://github.com/TartanLlama/expected)

## Interface Dependencies

These dependencies are added to the cmake INTERFACE library `fp`.

- [fmtlib: A modern formatting library](https://fmt.dev/latest/index.html)
- [range-v3: Range library, basis for C++20's std::ranges](https://ericniebler.github.io/range-v3/)

## Achnologements

- ['Functional Programming in C++' by Ivan Čukić](https://www.manning.com/books/functional-programming-in-c-plus-plus)
- [ABSL `StatusOr`](https://github.com/abseil/abseil-cpp/blob/master/absl/status/statusor.h)
