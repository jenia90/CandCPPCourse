CC = g++
CFLAGS = -Wall -Wextra -Wvla -O -pthread -std=gnu++11

default: GenericMatrixDriver
	./GenericMatrixDriver

GenericMatrixDriver: Complex.o Matrix
	$(CC) $(CFLAGS) $(ADDFLAGS) Complex.o GenericMatrixDriver.cpp -o GenericMatrixDriver

Complex.o: Complex.cpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Complex.cpp

Matrix: Matrix.hpp
	$(CC) $(CFLAGS) $(ADDFLAGS) -c Matrix.hpp

tar:
	tar cvf ex3.tar Matrix.hpp Makefile README

clean:
	rm -f *.o *.tar *.gch GenericMatrixDriver BonusParallelChecker
