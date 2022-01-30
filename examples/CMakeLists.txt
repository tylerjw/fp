# Example usage for documentation

add_executable(no_discard no_discard.cpp)
target_link_libraries(no_discard monad)

add_executable(result result.cpp)
target_link_libraries(result monad)

add_executable(validate_in validate_in.cpp)
target_link_libraries(validate_in monad)

add_executable(validate_range validate_range.cpp)
target_link_libraries(validate_range monad)
