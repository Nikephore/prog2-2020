#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"
#include "graph.h"

int main()
{
    Node *n1 = NULL;
    Node *n2 = NULL;
    Graph *g1 = NULL;
 
    /*inicializamos los nodos*/

    n1 = node_init();
    if(!n1) return ERROR;

    n2 = node_init();
    if(!n2){
        node_free(n1);
        return ERROR;
    }

    /*Establecemos valores de n1*/
    node_setName(n1, "first");
    node_setId(n1, 111);
    node_setLabel(n1, WHITE);

    /*Establecemos valores de n2*/
    node_setName(n2, "second");
    node_setId(n2, 222);
    node_setLabel(n2, WHITE);

    g1 = graph_init();
    if(!g1){
        node_free(n1);
        node_free(n2);
        return ERROR;
    }
    
    fprintf(stdout, "Insertando nodo 1...resultado...: %d\n", graph_insertNode(g1, n1));
    /*if(graph_insertNode(g1, n1) == ERROR) return -1;*/

    fprintf(stdout, "Insertando nodo 2...resultado...: %d\n", graph_insertNode(g1, n2));
    /*if(graph_insertNode(g1, n2) == ERROR) return -1;*/

    graph_insertEdge(g1, node_getId(n2), node_getId(n1));
    fprintf(stdout, "Insertando edge: nodo 2 ---> nodo 1\n");

    if(graph_areConnected(g1, node_getId(n1), node_getId(n2)) == TRUE){
        fprintf(stdout, "¿Conectados nodo 1 y nodo 2? SI\n");
    }
    else{
        fprintf(stdout, "¿Conectados nodo 1 y nodo 2? NO\n");
    }

    if(graph_areConnected(g1, node_getId(n2), node_getId(n1)) == TRUE){
        fprintf(stdout, "¿Conectados nodo 2 y nodo 1? SI\n");
    }
    else{
        fprintf(stdout, "¿Conectados nodo 2 y nodo 1? NO\n");
    }

    
    fprintf(stdout, "Insertando nodo 2...resultado...: %d\n", (int)graph_insertNode(g1, n2));

    fprintf(stdout, "A E S T H E T I C . . . G R A F O:\n");
    graph_print(stdout, g1);

    node_free(n1);
    node_free(n2);
    graph_free(g1);

    return 0;
}