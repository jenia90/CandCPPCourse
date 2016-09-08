CC = g++
CFLAGS = -Wall -Wextra -Wvla -std=c++11

default: ConvexHull PointSetBinaryOperations

PointSet.o: PointSet.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c PointSet.cpp

Point.o: Point.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Point.cpp

ConvexHull: Point.o PointSet.o ConvexHull.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) Point.o PointSet.o ConvexHull.cpp -o ConvexHull

PointSetBinaryOperations: PointSetBinaryOperations.cpp Point.o PointSet.o
	$(CC) $(CFLAGS) $(ADDFLAGS) Point.o PointSet.o PointSetBinaryOperations.cpp -o PointSetBinaryOperations

tar:
	tar cvf ex1.tar README Makefile ConvexHull.cpp PointSetBinaryOperations.cpp Point.h Point.cpp PointSet.h PointSet.cpp

clean:
	rm -f *.o *.a *.tar ConvexHull PointSetBinaryOperations
