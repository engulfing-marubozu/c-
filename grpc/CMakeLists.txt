cmake_minimum_required(VERSION 3.15)

project(GrpcQuickstart VERSION 1.0.0)

# Include CTest for testing (optional)
include(CTest)
enable_testing()

# Set the C++ standard (optional)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fpic -g")

# Find dependencies
find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(Threads REQUIRED)

# Include directories (if necessary)
include_directories(${Protobuf_INCLUDE_DIRS} ${gRPC_INCLUDE_DIRS})

# Create a common library target for generated code
add_library(helloworld_proto
    helloworld.grpc.pb.cc
    helloworld.pb.cc
)
target_link_libraries(helloworld_proto
    gRPC::grpc++
    protobuf::libprotobuf
)
target_include_directories(helloworld_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# Add the greeter server executable
add_executable(greeter_server greeter_server.cc)
target_link_libraries(greeter_server helloworld_proto Threads::Threads)

# Add the greeter client executable
add_executable(greeter_client greeter_client.cc)
target_link_libraries(greeter_client helloworld_proto Threads::Threads)

# Optionally print status messages
message(STATUS "gRPC_DIR: ${gRPC_DIR}")
message(STATUS "Protobuf_DIR: ${Protobuf_DIR}")
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
