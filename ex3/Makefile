CC = gcc
CFLAGS = -Wall -Wextra -Wvla -std=c99

all: GenericHashTable MyIntFunctions MyStringFunctions HashIntSearch HashStringSearch
    ./HashIntSearch
    ./HashStringSearch

GenericHashTable.o: GenericHashTable.c
    $(CC) $(CFLAGS) $(ADDFLAGS) -c GenericHashTable

MyIntFunctions.o: MyIntFunctions.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c MyIntFunctions.c

MyStringFunctions.o: MyStringFunctions.c
	$(CC) $(CFLAGS) $(ADDFLAGS) -c MyStringFunctions.c
