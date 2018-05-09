cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)

set(SRC
        camera_image_acquisitor.cpp
        image_data.cpp
)

set(INC
        camera_image_acquisitor.hpp
        image_acquisitor.hpp
        image_data.hpp
)
        
add_library(image_acquisition STATIC ${INC} ${SRC})

target_include_directories(image_acquisition PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/modes
        ${CMAKE_SOURCE_DIR}/modules/detection
        ${CMAKE_SOURCE_DIR}/modules/ui
        ${CMAKE_SOURCE_DIR}/tools
)
