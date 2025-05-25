cmake_minimum_required(VERSION 3.14)
project(ParallelRiscV)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SRC_FILES "src/*.cpp")
add_executable(parallel_riscv ${SRC_FILES} main.cpp)
add_executable(test_decoder test_decoder.cpp src/Decoder.cpp)
target_include_directories(test_decoder PRIVATE include)

