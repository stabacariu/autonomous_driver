cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)

set(SRC
        path_planning.cpp
        remote_control.cpp
        trajectory_data.cpp
)

set(INC
        path_planning.hpp
        remote_control.hpp
        trajectory_data.hpp
)
        
add_library(path_planning STATIC ${INC} ${SRC})

target_include_directories(path_planning PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/ui
        ${CMAKE_SOURCE_DIR}/modules
        ${CMAKE_SOURCE_DIR}/modules/detection
        ${CMAKE_SOURCE_DIR}/modules/image_acquisition
        ${CMAKE_SOURCE_DIR}/modules/vehicle_control
        ${CMAKE_SOURCE_DIR}/tools
)
