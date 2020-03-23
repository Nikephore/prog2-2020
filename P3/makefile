CC = gcc -g -ansi -pedantic
CFLAGS = -Wall
EXE = p3_e1

all: $(EXE)

$(EXE) : % : %.o node.o graph.o queue.o
	$(CC) $(CFLAGS) -o $@ $@.o node.o graph.o queue.o

node.o: node.c node.h
	$(CC) $(CFLAGS) -c -o node.o node.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c -o graph.o graph.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c -o queue.o queue.c

clean:
		rm -f *.o core $(EXE)

val_1:
	valgrind --tool=memcheck --leak-check=yes ./p3_e1

p1_e1t:
	@./p1_e1

p1_e2t:
	@./p1_e2
