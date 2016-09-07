CC = g++
CFLAGS = -Wall -Wextra -Wvla -std=c++11

PointSet.o: PointSet.cpp
	$(CC) $(CFLAGS) -c PointSet.cpp

Point.o: Point.cpp
	$(CC) $(CFLAGS) -c Point.cpp

LinkedList.o: LinkedList.cpp
	$(CC) $(CFLAGS) -c LinkedList.cpp

ConvexHull: Point.o PointSet.o LinkedList.o
	$(CC) $(CFLAGS) Point.o PointSet.o LinkedList.o ConvexHull.cpp -o ConvexHull