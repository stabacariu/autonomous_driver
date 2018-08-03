cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)

set(SRC
        motor_driver.cpp
        vehicle_control.cpp
        vehicle_data.cpp
)

set(INC
        motor_driver.hpp
        vehicle_control.hpp
        vehicle_data.hpp
)
        
add_library(vehicle_control STATIC ${INC} ${SRC})

target_include_directories(vehicle_control PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/ui
        ${CMAKE_SOURCE_DIR}/modules
        ${CMAKE_SOURCE_DIR}/modules/detection
        ${CMAKE_SOURCE_DIR}/modules/image_acquisition
        ${CMAKE_SOURCE_DIR}/modules/path_planning
        ${CMAKE_SOURCE_DIR}/tools
)
