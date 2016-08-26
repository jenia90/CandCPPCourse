cmake_minimum_required(VERSION 3.5)
project(CandCPPCourse)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall -Wvla -std=c99")

#add_library(MyLinkedList ex2/MyLinkedList.c)
#add_executable(ListExample ex2/ListExample.c)
#target_link_libraries(ListExample MyLinkedList)

#add_executable(CheckDependency ex2/CheckDependency.c)

#add_executable(ReadDependency ex2/ReadDependency.c)

add_library(GenericHashTable ex3/GenericHashTable.c)
add_library(MyStringFunction ex3/MyStringFunction.c)
add_library(MyIntFunction ex3/MyIntFunction.c)
target_link_libraries(MyStringFunction GenericHashTable)
target_link_libraries(MyIntFunction GenericHashTable)
add_executable(HashIntSearch ex3/HashIntSearch.c)
add_executable(HashStringSearch ex3/HashStringSearch.c)
target_link_libraries(HashIntSearch MyIntFunction)
target_link_libraries(HashStringSearch MyStringFunction)