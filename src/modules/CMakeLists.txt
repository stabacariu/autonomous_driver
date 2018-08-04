cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(detection)
add_subdirectory(image_acquisition)
add_subdirectory(planning)
add_subdirectory(vehicle_control)
