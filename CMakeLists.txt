project(multithread CXX)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
aux_source_directory(. SRC_LIST)

SET(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(${PROJECT_NAME} ${SRC_LIST})

