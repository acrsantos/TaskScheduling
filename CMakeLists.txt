cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 17)
project(TaskScheduling VERSION 0.1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(TaskScheduling ${SRC_FILES})
