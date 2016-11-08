CC = gcc
CFLAGS = -Wall -Wextra -Wvla -std=c99
DFLAGS = -DMAX_ROW_ELEMENTS=2 -DNDEBUG
ARGS_INT = 1 0
ARGS_STR = 1 lmno

all: HashIntSearch
	./HashIntSearch $(ARGS_INT)

HashIntSearch: HashIntSearch.o MyIntFunctions.o libgenericHashTable.a
	$(CC) $(CFLAGS) $(ADDFLAGS) HashIntSearch.c -L. -lgenericHashTable MyIntFunctions.o -o HashIntSearch

HashStrSearch: HashStrSearch.o MyStringFunctions.o libgenericHashTable.a
	$(CC) $(CFLAGS) $(ADDFLAGS) HashStrSearch.c -L. -lgenericHashTable MyStringFunctions.o -o HashStrSearch

libgenericHashTable.a: GenericHashTable.o TableErrorHandle.o
	ar rcs libgenericHashTable.a GenericHashTable.o TableErrorHandle.o

GenericHashTable.o: GenericHashTable.c TableErrorHandle.c
	$(CC) $(CFLAGS) $(DFLAGS) $(ADDFLAGS) -c GenericHashTable.c TableErrorHandle.c

MyIntFunctions.o: MyIntFunctions.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c MyIntFunctions.c

MyStringFunctions.o: MyStringFunctions.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c MyStringFunctions.c

tar:
	tar cvf ex3_late.tar Makefile GenericHashTable.c MyIntFunctions.c MyStringFunctions.c MyStringFunctions.h MyIntFunctions.h Key.h extension.pdf

clean:
	rm -f *.o *.a *.tar HashIntSearch HashStrSearch
