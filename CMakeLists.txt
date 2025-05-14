cmake_minimum_required(VERSION 3.10)

project(BitwiseOperations)

set(CMAKE_CXX_STANDARD 23)
add_library(bit_op INTERFACE)
target_include_directories(bit_op INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add the test
enable_testing()

add_executable(main main.cpp)
target_link_libraries(main PRIVATE bit_op)

add_test(NAME MainTest COMMAND main)
