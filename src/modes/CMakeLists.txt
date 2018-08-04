cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)

set(SRC
        about_mode.cpp
        autonomous_mode.cpp
        calibration_mode.cpp
        closing_mode.cpp
        configuration_mode.cpp
        development_mode.cpp
        error_mode.cpp
        remote_control_mode.cpp
        standby_mode.cpp
        system_state.cpp
)

set(INC
        about_mode.hpp
        autonomous_mode.hpp
        calibration_mode.hpp
        closing_mode.hpp
        configuration_mode.hpp
        development_mode.hpp
        error_mode.hpp
        remote_control_mode.hpp
        standby_mode.hpp
        system_mode.hpp
        system_state.hpp
)
        
add_library(modes STATIC ${INC} ${SRC})

target_include_directories(modes PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/ui
        ${CMAKE_SOURCE_DIR}/modules
        ${CMAKE_SOURCE_DIR}/modules/detection
        ${CMAKE_SOURCE_DIR}/modules/image_acquisition
        ${CMAKE_SOURCE_DIR}/modules/planning
        ${CMAKE_SOURCE_DIR}/modules/vehicle_control
        ${CMAKE_SOURCE_DIR}/tools
)
