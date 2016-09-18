CC = g++
CFLAGS = -Wall -Wextra -Wvla -pthread -std=c++11

all: Shapes

Shapes: Shapes.cpp Shape.o Triangle.o Trapezoid.o Line.o Point.o PrintOuts.o
	$(CC) $(CFLAGS) $(ADDFLAGS) Shape.o Trapezoid.o Triangle.o Line.o Point.o PrintOuts.o Shapes.cpp -o Shapes

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


tar:
	tar cvf ex2.tar Shapes.cpp Shape.* Triangle.* Trapezoid.* Point.* Line.* PrintOuts.* README

clean:
	rm -f *.o *.tar Shapes