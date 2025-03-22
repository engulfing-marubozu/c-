cmake_minimum_required(VERSION 3.20.0)

project(NG)

find_package(CURL REQUIRED)

add_executable(callback_model callback_model.cpp ng_sdk.cpp algo.cpp algo2.cpp)
target_link_libraries(callback_model CURL::libcurl)