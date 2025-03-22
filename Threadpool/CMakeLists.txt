cmake_minimum_required(VERSION 3.20)
project(Threadpool)

set(CMAKE_CXX_STANDARD 17)

find_package(spdlog REQUIRED)

add_executable(threadpool main.cpp)
target_link_libraries(threadpool PRIVATE spdlog::spdlog)
