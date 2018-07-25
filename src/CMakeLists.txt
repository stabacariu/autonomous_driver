cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenCV REQUIRED)
find_library(WiringPi REQUIRED)

add_subdirectory(modes)
add_subdirectory(ui)
add_subdirectory(modules)
add_subdirectory(tools)

set(SRC
    autonomous_driver.cpp
    main.cpp
)

set(INC
    autonomous_driver.hpp
)

set(LIB
    lib/libSonar.cpp
    lib/libSonar.h
    lib/PCA9685.cpp
    lib/PCA9685.h
)

add_executable(autonomous_driver ${SRC} ${INC} ${LIB})
target_link_libraries(autonomous_driver pthread wiringPi ${OpenCV_LIBS} ${WiringPi_LIBS} modes detection image_acquisition path_planning ui vehicle_control tools)
