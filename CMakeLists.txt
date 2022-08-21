cmake_minimum_required(VERSION 3.5)

project(intel_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(intel_task shared_ptr.h main.cpp)
