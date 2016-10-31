all: ListExample CheckDependency ReadDirectory
	./ListExample

ListExample.o: ListExample.c
	gcc -Wall -Wextra -Wvla -std=c99 $(ADDFLAGS) -c ListExample.c

MyLinkedList.o: MyLinkedList.c
	gcc -Wall -Wextra -Wvla -std=c99 $(ADDFLAGS) -c MyLinkedList.c

ListExample: ListExample.o MyLinkedList.o
	gcc -Wall -Wextra -Wvla -std=c99 $(ADDFLAGS) ListExample.o MyLinkedList.o -o ListExample

CheckDependency.o: CheckDependency.c
	gcc -Wall -Wextra -Wvla -std=c99 $(ADDFLAGS) -c CheckDependency.c

CheckDependency: CheckDependency.o
	gcc -Wall -Wextra -Wvla -std=c99 $(ADDFLAGS) CheckDependency.o -o CheckDependency

ReadDirectory.o: ReadDirectory.c
	gcc -Wall -Wextra -Wvla -std=c99 $(ADDFLAGS) -c ReadDirectory.c

ReadDirectory: ReadDirectory.o
	gcc -Wall -Wextra -Wvla -std=c99 $(ADDFLAGS) ReadDirectory.o -o ReadDirectory

tar:
	tar cvf ex2_late.tar CheckDependency.c ReadDirectory.c MyLinkedList.c Makefile README extension.pdf valdbg_check_dependency.out valdbg_list_example.out

clean:
	rm -f ListExample ListExample.o MyLinkedList.o CheckDependency CheckDependency.o ReadDirectory ReadDirectory.o ex2_late.tar
