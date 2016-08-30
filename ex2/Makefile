all: ListExample CheckDependency ReadDirectory
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

ReadDirectory.o: ReadDirectory.c
	gcc -Wall -Wextra -Wvla -std=c99 -c ReadDirectory.c

ReadDirectory: ReadDirectory.o
	gcc -Wall -Wextra -Wvla -std=c99 ReadDirectory.o -o ReadDirectory

tar:
	tar cvf ex2_late.tar CheckDependency.c ReadDirectory.c MyLinkedList.c Makefile README extension.pdf

clean:
	rm -f ListExample ListExample.o MyLinkedList.o CheckDependency CheckDependency.o ReadDirectory ReadDirectory.o ex2_late.tar
