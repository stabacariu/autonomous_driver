cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
find_library(WiringPi REQUIRED)

file(GLOB SRC "src/*.cpp"
	INC "src/*.hpp"
	LIB lib/*.cpp)

add_executable(autonomous_driver ${SRC} ${INC} ${LIB})
target_link_libraries(autonomous_driver pthread wiringPi ${OpenCV_LIBS} ${WiringPi_LIBS})
