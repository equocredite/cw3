cmake_minimum_required(VERSION 3.24)
project(paralgo-hw3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Threads REQUIRED)
include_directories(include)

add_executable(cw3 src/main.cpp src/tree.cpp src/validation.cpp src/node.cpp src/spinlock.cpp include/timer.hpp src/runner.cpp src/timer.cpp)
target_link_libraries(cw3 pthread)
