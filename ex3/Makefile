CC = gcc
CFLAGS = -Wall -Wextra -Wvla -std=c99

all: GenericHashTable MyIntFunctions MyStringFunctions HashIntSearch HashStrSearch
    ./HashIntSearch 

GenericHashTable.o: GenericHashTable.c TableErrorHandle.c
    $(CC) $(CFLAGS) $(ADDFLAGS) -c GenericHashTable.c TableErrorHandle.c -o GenericHashTable.o
    
libgenericHashTable.a: GenericHashTable.o
	ar rcs libgenericHashTable.a

MyIntFunctions.o: MyIntFunctions.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c MyIntFunctions.c

MyStringFunctions.o: MyStringFunctions.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c MyStringFunctions.c

HashIntSearch: HashIntSearch.o MyIntFunctions.o libgenericHashTable.a
	$(CC) $(CFLAGS) $(ADDFLAGS) -static HashIntSearch.c MyIntFunctions.o -lgenericHashTable -o HashIntSearch

HashStrSearch: HashStrSearch.o MyIntFunctions.o libgenericHashTable.a
	$(CC) $(CFLAGS) $(ADDFLAGS) -static HashStrSearch.c MyStringFunctions.o -lgenericHashTable -o HashStrSearch

