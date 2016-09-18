CC = g++
CFLAGS = -Wall -Wextra -Wvla -pthread -std=c++11
OBJECTS = ShapeUtils.o Shape.o Triangle.o Trapezoid.o Line.o Point.o PrintOuts.o

all: Shapes

Shapes: Shapes.cpp ShapeUtils.o Shape.o Triangle.o Trapezoid.o Line.o Point.o PrintOuts.o
	$(CC) $(CFLAGS) $(ADDFLAGS) $(OBJECTS) Shapes.cpp -o Shapes

Shape.o: Shape.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Shape.cpp

Triangle.o: Triangle.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Triangle.cpp

Trapezoid.o: Trapezoid.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Trapezoid.cpp

Line.o: Line.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Line.cpp

Point.o: Point.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Point.cpp

PrintOuts.o: PrintOuts.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c PrintOuts.cpp

ShapeUtils.o: ShapeUtils.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c ShapeUtils.cpp


tar:
	tar cvf ex2.tar Defs.h Shapes.cpp Shape.* ShapeUtils.* Triangle.* Trapezoid.* Point.* Line.* PrintOuts.* README Makefile

clean:
	rm -f *.o *.tar Shapes