CC = gcc -g -ansi -pedantic
CFLAGS = -Wall
EXE = p1_e1

all: $(EXE)

$(EXE) : % : %.o node.o
	$(CC) $(CFLAGS) -o $@ $@.o node.o

node.o: node.c node.h
	$(CC) $(CFLAGS) -c -o node.o node.c

clean:
		rm -f *.o core $(EXE)

val:
	valgrind --tool=memcheck --leak-check=yess ./p1_e1

p1_e1t:
	@./p1_e1