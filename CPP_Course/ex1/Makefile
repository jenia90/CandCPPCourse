CC = g++
CFLAGS = -Wall -Wextra -Wvla -std=c++11

PointSet.o: PointSet.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c PointSet.cpp

Point.o: Point.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Point.cpp

ConvexHull: Point.o PointSet.o
	$(CC) $(CFLAGS) $(ADDFLAGS) Point.o PointSet.o ConvexHull.cpp -o ConvexHull

clean:
	rm -f *.o *.a *.tar ConvexHull