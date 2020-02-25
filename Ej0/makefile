CC=gcc
CFLAGS=-Wall -ggdb
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack_fp
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
all: p2_e0_a p2_e0_b
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' (dependencias)
########################################################################
p2_e0_b: p2_e0_b.o libstack_fp.a
	$(CC) -o $@ $< $(LDFLAGS) $(LDLIBS) $(LIBS)
p2_e0_b.o: p2_e0_b.c
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)