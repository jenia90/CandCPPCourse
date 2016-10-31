CC = g++
CFLAGS = -Wall -Wextra -Wvla -pthread -std=c++11

default: GenericMatrixDriver.exe

GenericMatrixDriver.exe: Complex.o Matrix
	$(CC) $(CFLAGS) $(ADDFLAGS) Complex.o GenericMatrixDriver.cpp -o GenericMatrixDriver.exe

Complex.o: Complex.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Complex.cpp

Matrix: Matrix.hpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Matrix.hpp

tar:
	tar cvf ex3.tar Matrix.hpp Makefile README

clean:
	rm -f *.o *.exe *.tar *.gch
