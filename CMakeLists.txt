cmake_minimum_required(VERSION 3.15)
project(fp)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(fmt REQUIRED)
find_package(range-v3 REQUIRED)

add_library(fp INTERFACE)
target_include_directories(fp
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_features(fp INTERFACE cxx_std_17)
target_link_libraries(fp
  INTERFACE
    fmt::fmt
    range-v3::range-v3
)

add_subdirectory(examples)

install(DIRECTORY include/ DESTINATION include/)

install(
  TARGETS fp
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

ament_export_include_directories(include)
ament_export_targets(${PROJECT_NAME}Targets)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following lines skip linters
  set(ament_cmake_cpplint_FOUND TRUE) # Conflicts with clang-foramt
  set(ament_cmake_flake8_FOUND TRUE) # Conflicts with black
  set(ament_cmake_uncrustify_FOUND TRUE) # Conflicts with clang-format
  ament_lint_auto_find_test_dependencies()

  add_subdirectory(test)
endif()

ament_package()
