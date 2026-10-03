cmake_minimum_required(VERSION 3.20)
project(metrics-agent CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(agent main.cpp metrics.cpp)
target_compile_options(agent PRIVATE -Wall -Wextra)