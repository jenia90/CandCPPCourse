CC = g++
CFLAGS = -Wall -Wextra -Wvla -std=c++11

PointSet.o: PointSet.cpp
	$(CC) $(CFLAGS) -c PointSet.cpp

Point.o: Point.cpp
	$(CC) $(CFLAGS) -c Point.cpp

ConvexHull: Point.o PointSet.o
	$(CC) $(CFLAGS) Point.o PointSet.o ConvexHull.cpp -o ConvexHull

clean:
	rm -f *.o *.a *.tar ConvexHull