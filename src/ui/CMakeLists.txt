cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)

set(SRC
        ui_about_mode.cpp
        ui_autonomous_mode.cpp
        ui_calibration_mode.cpp
        ui_configuration_mode.cpp
        ui_development_mode.cpp
        ui_error_mode.cpp
        ui_remote_control_mode.cpp
        ui_standby_mode.cpp
        user_interface.cpp
        user_interface_state.cpp
)

set(INC
        ui_about_mode.hpp
        ui_autonomous_mode.hpp
        ui_calibration_mode.hpp
        ui_configuration_mode.hpp
        ui_development_mode.hpp
        ui_error_mode.hpp
        ui_remote_control_mode.hpp
        ui_standby_mode.hpp
        user_interface.hpp
        user_interface_mode.hpp
        user_interface_state.hpp
)
        
add_library(ui STATIC ${INC} ${SRC})

target_include_directories(ui PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/modules/detection
        ${CMAKE_SOURCE_DIR}/modules/image_acquisition
        ${CMAKE_SOURCE_DIR}/modules/path_planning
        ${CMAKE_SOURCE_DIR}/modules/vehicle_control
        ${CMAKE_SOURCE_DIR}/tools
)
