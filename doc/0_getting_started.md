# Getting started

To get started using the `fp` library in your project you need to add the repo to your workspace, add the dependency to your package.xml, add the dependency in your CMakeLists.txt, and lastly you need to include it in your project.

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

## Next tutorial

[Functions that can fail](doc/1_returning_results.md)
