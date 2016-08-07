cmake_minimum_required(VERSION 3.5)
project(CandCPPCourse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -std=c99")

set(SOURCE_FILES ex1/ChangeBase.c)
add_executable(ChangeBase ${SOURCE_FILES})