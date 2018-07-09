cmake_minimum_required(VERSION 2.8.12)

project(ocv)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

## path *cpp
set(SOURCE_LIB src/cvstamp.cpp)		

## path main.cpp
set(SOURCE_EXE src/main.cpp)

## compile libs 
add_library(cvstamp SHARED ${SOURCE_LIB})

## compile
add_executable(ocv ${SOURCE_EXE})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

## link libs
target_link_libraries(ocv ${OpenCV_LIBS} cvstamp)



