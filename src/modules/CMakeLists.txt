cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

add_subdirectory(detection)
add_subdirectory(image_acquisition)
add_subdirectory(path_planning)
add_subdirectory(vehicle_control)
