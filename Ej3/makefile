CC=gcc
CFLAGS=-Wall -ggdb
EXE = p2_e3_a

all:$(EXE)


$(EXE): %: %.o node.o stack.o element.o
	$(CC) $(CFLAGS) -o $@ $@.o node.o stack.o element.o

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c -o stack.o stack.c

element.o: element.c element.h
	$(CC) $(CFLAGS) -c -o element.o element.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c -o node.o node.c

clean:
	rm -f *.o core $(EXE)

val:
	valgrind --tool=memcheck --leak-check=yes ./p2_e3_a
