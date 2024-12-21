cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")



set(CMAKE_MAKE_PROGRAM "C:\\Program Files\\CMake\\bin\\cmake.exe")

project(PointersProject)

# Add executable
add_executable(pointers pointers.cpp  linkingCode.cpp  pointers.h)

# Clean target
add_custom_target(clean
    COMMAND ${CMAKE_COMMAND} -E remove pointers
    COMMAND ${CMAKE_COMMAND} -E remove *.o
)

