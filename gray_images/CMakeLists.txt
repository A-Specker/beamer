cmake_minimum_required(VERSION 3.15)
project(graycode)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED ) # locate OpenCV in system
include_directories( ${OpenCV_INCLUDE_DIRS} ) # provide library headers
add_executable(graycode main.cpp)
target_link_libraries( graycode ${OpenCV_LIBS} /usr/lib/x86_64-linux-gnu/libopencv_highgui.so) # link OpenCV libraries , hightgui.so not found by cmake so this hack
MESSAGE("OpenCV_LIBS: " ${OpenCV_LIBS} )  #display opencv libs found
