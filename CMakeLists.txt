cmake_minimum_required(VERSION 3.10)
project(ng_sdk)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(ng_sdk
    src/ng_sdk.cpp
    src/KillSwitch.cpp
    // ...other source files...
)

target_link_libraries(ng_sdk
    // ...libraries...
)
