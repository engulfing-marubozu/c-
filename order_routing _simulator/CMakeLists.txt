cmake_minimum_required(VERSION 3.5)

project(order_routing_simulator)

add_executable(order_routing_simulator
    main.cpp
    orsEngine.cpp
    ICEOrderProcessor.cpp
    config.cpp
    CMEOrderProcessor.cpp
    )
