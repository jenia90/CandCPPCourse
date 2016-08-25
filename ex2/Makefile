all: ListExample CheckDependency ReadDependency
	./ListExample

ListExample.o: ListExample.c
	gcc -Wall -Wextra -Wvla -std=c99 -c ListExample.c

MyLinkedList.o: MyLinkedList.c
	gcc -Wall -Wextra -Wvla -std=c99 -c MyLinkedList.c

ListExample: ListExample.o MyLinkedList.o
	gcc -Wall -Wextra -Wvla -std=c99 ListExample.o MyLinkedList.o -o ListExample

CheckDependency.o: CheckDependency.c
	gcc -Wall -Wextra -Wvla -std=c99 -c CheckDependency.c

CheckDependency: CheckDependency.o
	gcc -Wall -Wextra -Wvla -std=c99 CheckDependency.o -o CheckDependency

ReadDependency.o: ReadDependencies.c
	gcc -Wall -Wextra -Wvla -std=c99 -c ReadDependency.c

ReadDependency: ReadDependency.o
	gcc -Wall -Wextra -Wvla -std=c99 ReadDependency.o -o ReadDependency

tar:
	tar cvf ex2_late.tar CheckDependency.c ReadDependency.c MyLinkedList.c Makefile README extension.pdf

clean:
	rm -f ListExample ListExample.o MyLinkedList.o CheckDependency CheckDependency.o ReadDependency ReadDependency.o ex2_late.tar
