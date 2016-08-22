cmake_minimum_required(VERSION 3.5)
project(CandCPPCourse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -std=c99")

add_library(MyLinkedList ex2/MyLinkedList.c)
add_executable(ListExample ex2/ListExample.c)
target_link_libraries(ListExample MyLinkedList)

add_executable(CheckDependency ex2/CheckDependency.c)

add_executable(ReadDependency ex2/ReadDependency.c)