cmake_minimum_required(VERSION 3.3.2)
project(CandCPPCourse)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall -Wvla -std=c99")

#C_EX2
#add_library(MyLinkedList ex2/MyLinkedList.c)
#add_executable(ListExample ex2/ListExample.c)
#target_link_libraries(ListExample MyLinkedList)
#add_executable(CheckDependency ex2/CheckDependency.c)
#add_executable(ReadDependency ex2/ReadDependency.c)

#C_EX3
#add_library(GenericHashTable C_Course/ex3/GenericHashTable.c)
#add_library(MyStringFunctions C_Course/ex3/MyStringFunctions.c)
#add_library(MyIntFunctions C_Course/ex3/MyIntFunctions.c)
#add_library(TableErrorHandle C_Course/ex3/TableErrorHandle.c)
#add_executable(HashIntSearch C_Course/ex3/HashIntSearch.c)
#add_executable(HashStrSearch C_Course/ex3/HashStrSearch.c)
#target_link_libraries(HashIntSearch GenericHashTable MyIntFunctions TableErrorHandle)
#target_link_libraries(HashStrSearch GenericHashTable MyStringFunctions TableErrorHandle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -Wvla -std=gnu++11")

#CPP_EX1
#add_library(PointSet CPP_Course/ex1/PointSet.cpp)
#add_library(Point CPP_Course/ex1/Point.cpp)
#add_executable(ConvexHull CPP_Course/ex1/ConvexHull.cpp )
#add_executable(PointSetBinaryOperations CPP_Course/ex1/PointSetBinaryOperations.cpp)
#target_link_libraries(ConvexHull PointSet Point)
#target_link_libraries(PointSetBinaryOperations PointSet Point)

#CPP_EX2
#add_library(PrintOuts CPP_Course/ex2/PrintOuts.cpp)
#add_library(Triangle CPP_Course/ex2/Triangle.cpp)
#add_library(Trapezoid CPP_Course/ex2/Trapezoid.cpp)
#add_library(Point CPP_Course/ex2/Point.cpp)
#add_library(Line CPP_Course/ex2/Line.cpp)
#add_library(Shape CPP_Course/ex2/Shape.cpp)
#add_library(ShapeUtils CPP_Course/ex2/ShapeUtils.cpp)
#add_executable(Shapes CPP_Course/ex2/Shapes.cpp)
#target_link_libraries(Shapes Shape ShapeUtils Triangle Trapezoid Point Line PrintOuts)

add_library(Complex CPP_Course/ex3/Complex.cpp)
add_executable(BonusParallelChecker CPP_Course/ex3/BonusParallelChecker.cpp)
add_executable(GenericMatrixDriver CPP_Course/ex3/GenericMatrixDriver.cpp)
add_library(Matrix CPP_Course/ex3/Matrix.hpp)
target_link_libraries(Matrix Complex)
target_link_libraries(GenericMatrixDriver Matrix)
target_link_libraries(BonusParallelChecker Matrix)