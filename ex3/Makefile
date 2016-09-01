CC = gcc
CFLAGS = -Wall -Wextra -Wvla -std=c99

all: HashIntSearch HashStrSearch
	./HashIntSearch 1 0
	./HashStrSearch 1 lmno

HashIntSearch: HashIntSearch.o MyIntFunctions.o libgenericHashTable.a
	$(CC) $(CFLAGS) $(ADDFLAGS) HashIntSearch.c -L. -lgenericHashTable MyIntFunctions.o -o HashIntSearch

HashStrSearch: HashStrSearch.o MyStringFunctions.o libgenericHashTable.a
	$(CC) $(CFLAGS) $(ADDFLAGS) HashStrSearch.c -L. -lgenericHashTable MyStringFunctions.o -o HashStrSearch

GenericHashTable.o: GenericHashTable.c TableErrorHandle.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c GenericHashTable.c TableErrorHandle.c
    
libgenericHashTable.a: GenericHashTable.o TableErrorHandle.o
	ar rcs libgenericHashTable.a GenericHashTable.o TableErrorHandle.o

MyIntFunctions.o: MyIntFunctions.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c MyIntFunctions.c

MyStringFunctions.o: MyStringFunctions.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c MyStringFunctions.c


tar:
	tar cvf ex3_late.tar GenericHashTable.c MyIntFunctions.c MyStringFunctions.c MyStringFunctions.h MyIntFunctions.h Key.h

clean:
	rm -f *.o *.a *.tar HashIntSearch HashStrSearch