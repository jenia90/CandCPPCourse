CC = g++
CFLAGS = -Wall -Wextra -Wvla -pthread -std=c++11

default: ConvexHull PointSetBinaryOperations
	./PointSetBinaryOperations

ConvexHull: Point.o PointSet.o ConvexHull.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) Point.o PointSet.o ConvexHull.cpp -o ConvexHull

PointSetBinaryOperations: PointSetBinaryOperations.cpp Point.o PointSet.o
	$(CC) $(CFLAGS) $(ADDFLAGS) Point.o PointSet.o PointSetBinaryOperations.cpp -o PointSetBinaryOperations

PointSet.o: PointSet.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c PointSet.cpp

Point.o: Point.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Point.cpp

tar:
	tar cvf ex1.tar README Makefile ConvexHull.cpp PointSetBinaryOperations.cpp Point.h Point.cpp PointSet.h PointSet.cpp

clean:
	rm -f *.o *.tar ConvexHull PointSetBinaryOperations
