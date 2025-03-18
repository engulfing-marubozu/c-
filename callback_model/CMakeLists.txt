cmake_minimum_required(VERSION 3.20.0)

project(NG)

find_package(CURL REQUIRED)

add_executable(main main.cpp ng_sdk.cpp algo.cpp algo2.cpp)
target_link_libraries(main CURL::libcurl)