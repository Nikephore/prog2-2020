#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#inlude "node.h"


#define NAME_L 64 /*!< Maximum node name length */

typedef struct _Node {
  char name[NAME_L]; /*!<Node name */
  long id;           /*!<Node id */
  int nConnect;      /*!<Node number of connections */
  Label label;       /*!<Node state */
} Node;


Node * node_init(){
  Node *newNode = NULL;

  newNode = (Node*) malloc(sizeof(Node));
  if(!newNode){
    printf("Error al reservar memoria creando el nodo")
    return NULL;
  }

  node_setName(newNode, "");
  node_setId(newNode, 0);
  node_setLabel(newNode, BLANCO);
  node_setNConnect(newNode, 0);

  return newNode;
}

void node_free(void * n){
  if(!n) return;
  
  free(n);

  return;
}
