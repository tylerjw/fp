cmake_minimum_required(VERSION 3.15)
project(fp LANGUAGES CXX)

set(fp_MAJOR_VERSION 0)
set(fp_MINOR_VERSION 1)
set(fp_PATCH_VERSION 0)
set(fp_VERSION
  ${fp_MAJOR_VERSION}.${fp_MINOR_VERSION}.${fp_PATCH_VERSION})

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# find dependencies
find_package(fmt REQUIRED)
find_package(range-v3 REQUIRED)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
target_link_libraries(${PROJECT_NAME}
  INTERFACE
    fmt
    range-v3
)

add_subdirectory(examples)

install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS ${PROJECT_NAME}
  EXPORT export_fp
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# export targets
set(export_targets ${export_targets};${PROJECT_NAME})
export(EXPORT export_fp
  FILE "${PROJECT_BINARY_DIR}/export_fp.cmake")

# Create the fpConfig.cmake
set(CONF_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
configure_file(fpConfig.cmake.in
  "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/fpConfig.cmake" @ONLY)

# Create the fpConfigVersion.cmake
configure_file(fpConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/fpConfigVersion.cmake" @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}/${CMAKE_FILES_DIRECTORY}/fpConfig.cmake"
  "${PROJECT_BINARY_DIR}/fpConfigVersion.cmake"
  DESTINATION "share/${PROJECT_NAME}/cmake" COMPONENT dev)
install(EXPORT export_${PROJECT_NAME}
  DESTINATION "share/${PROJECT_NAME}/cmake"
  FILE export_${PROJECT_NAME}.cmake
  COMPONENT dev)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following lines skip linters
  set(ament_cmake_cpplint_FOUND TRUE) # Conflicts with clang-foramt
  set(ament_cmake_flake8_FOUND TRUE) # Conflicts with black
  set(ament_cmake_uncrustify_FOUND TRUE) # Conflicts with clang-format
  ament_lint_auto_find_test_dependencies()

  add_subdirectory(test)
endif()
