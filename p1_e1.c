#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"


int main ()
{
    Node *n1 = NULL;
    Node *n2 = NULL;

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

    node_print(stdout, n1);
    node_print(stdout, n2);

    fprintf(stdout, "\n");

    if (node_cmp(n1, n2) == 0){
        fprintf(stdout, "¿Son iguales?: SI\n");
    }
    else{
        fprintf(stdout, "¿Son iguales?: NO\n");
    }

    fprintf(stdout, "Id del primer nodo: %ld\n", node_getId(n1));
    fprintf(stdout, "Nombre del segundo nodo: %s\n\n", node_getName(n2));

    node_free(n2);

    n2 = node_copy(n1);

    node_print(stdout, n1);
    fprintf(stdout, "\n");
    node_print(stdout, n2);
    fprintf(stdout, "\n");

    if (node_cmp(n1, n2) == 0){
        fprintf(stdout, "¿Son iguales?: SI\n");
    }
    else{
        fprintf(stdout, "¿Son iguales?: NO\n");
    }

    node_free(n1);
    node_free(n2);

    return 0;
}