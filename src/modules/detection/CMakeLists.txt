cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)

set(SRC
        lane_data.cpp
        lane_detection.cpp
        obstacle_data.cpp
        obstacle_detection.cpp
        traffic_sign_data.cpp
        traffic_sign_detection.cpp
)

set(INC
        detector.hpp
        lane_data.hpp
        lane_detection.hpp
        obstacle_data.hpp
        obstacle_detection.hpp
        traffic_sign_data.hpp
        traffic_sign_detection.hpp
)
        
add_library(detection STATIC ${INC} ${SRC})

target_include_directories(detection PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/modes
        ${CMAKE_SOURCE_DIR}/modules/image_acquisition
        ${CMAKE_SOURCE_DIR}/modules/ui
        ${CMAKE_SOURCE_DIR}/tools
)
