find_package(ament_cmake_gtest REQUIRED)

ament_add_gtest(mbind_tests mbind_tests.cpp)
target_link_libraries(mbind_tests monad)

ament_add_gtest(result_tests result_tests.cpp)
target_link_libraries(result_tests monad)

ament_add_gtest(validate_tests validate_tests.cpp)
target_link_libraries(validate_tests monad)
