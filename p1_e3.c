#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "graph.h"

int main(int argc, char const *argv[]){
    Graph *g1 = NULL;
    FILE * f = argv[1];

    g1 = graph_init();

    graph_readFromFile(f, g1);

    graph_print(stdout, g1);

    graph_free(g1);

    return 0;
}