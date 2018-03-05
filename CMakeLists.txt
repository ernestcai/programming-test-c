cmake_minimum_required(VERSION 2.8)
project(programming-test-c)

set(CMAKE_CXX_FLAGS "-std=c++11")

# include all files under src/
file(GLOB SRC_FILES src/*(.cpp|.h))
message("SRC_FILES: ${SRC_FILES}")

add_executable(programming-test-c ${SRC_FILES})