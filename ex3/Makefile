CC = gcc -Wall -Wextra -Wvla -std=c99

all: GenericHashTable MyIntFunctions MyStringFunctions HashIntSearch HashStringSearch
    ./HashIntSearch
    ./HashStringSearch

GenericHashTable.o: GenericHashTable.c
    $(CC) -c GenericHashTable