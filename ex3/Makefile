CC = gcc
CFLAGS = -Wall -Wextra -Wvla -std=c99
DFLAGS = -DMAX_ROW_ELEMENTS=2
ARGS_INT = 1 0
ARGS_STR = 1 lmno

all: HashIntSearch HashStrSearch
	./HashIntSearch $(ARGS_INT)
	./HashStrSearch $(ARGS_STR)

HashIntSearch: HashIntSearch.o MyIntFunctions.o libgenericHashTable.a
	$(CC) $(CFLAGS) $(ADDFLAGS) HashIntSearch.c -L. -lgenericHashTable MyIntFunctions.o -o HashIntSearch

HashStrSearch: HashStrSearch.o MyStringFunctions.o libgenericHashTable.a
	$(CC) $(CFLAGS) $(ADDFLAGS) HashStrSearch.c -L. -lgenericHashTable MyStringFunctions.o -o HashStrSearch

GenericHashTable.o: GenericHashTable.c TableErrorHandle.c
	$(CC) $(CFLAGS) $(DFLAGS) $(ADDFLAGS) -c GenericHashTable.c TableErrorHandle.c
    
libgenericHashTable.a: GenericHashTable.o TableErrorHandle.o
	ar rcs libgenericHashTable.a GenericHashTable.o TableErrorHandle.o

MyIntFunctions.o: MyIntFunctions.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c MyIntFunctions.c

MyStringFunctions.o: MyStringFunctions.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c MyStringFunctions.c

debug:
	make 'ADDFLAGS=-g'

valgrind: 
	make debug
	@echo Running int valgrind check:
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes ./HashIntSearch $(ARGS_INT)
	@echo Running string valgrind check:
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes ./HashStrSearch $(ARGS_STR)


tar:
	tar cvf ex3_late.tar Makefile GenericHashTable.c MyIntFunctions.c MyStringFunctions.c MyStringFunctions.h MyIntFunctions.h Key.h

clean:
	rm -f *.o *.a *.tar HashIntSearch HashStrSearch
