cmake_minimum_required(VERSION 2.8)
project(autonomous_driver)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
file(GLOB autonomous_driver_SRC ../src/*.cpp)
add_executable(autonomous_driver ${autonomous_driver_SRC})
target_link_libraries(autonomous_driver pthread ${OpenCV_LIBS} ${Threads_LIBS})

