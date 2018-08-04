cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)

set(SRC
        configuration.cpp
        image_filter.cpp
)

set(INC
        configuration.hpp
        image_filter.hpp
)
        
add_library(tools STATIC ${INC} ${SRC})

target_include_directories(tools PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/modes
        ${CMAKE_SOURCE_DIR}/ui
        ${CMAKE_SOURCE_DIR}/modules
        ${CMAKE_SOURCE_DIR}/modules/detection
        ${CMAKE_SOURCE_DIR}/modules/image_acquisition
        ${CMAKE_SOURCE_DIR}/modules/planning
        ${CMAKE_SOURCE_DIR}/modules/vehicle_control
)

