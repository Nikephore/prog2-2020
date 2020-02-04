/*** @file  node.c
* @author Luis & Pelayo (pareja 3)
* @date 4 February 2020
* @version 1.0
* @brief Library to manage TAD Node
*
* @details
*
* @see4
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"


#define NAME_L 64 /*!< Maximum node name length */

struct _Node {
  char name[NAME_L]; /*!<Node name */
  long id;           /*!<Node id */
  int nConnect;      /*!<Node number of connections */
  Label label;       /*!<Node state */
};


Node * node_init(){
  Node *newNode = NULL;

  newNode = (Node*) malloc(sizeof(Node));
  if(!newNode){
    printf("Error al reservar memoria creando el nodo");
    return NULL;
  }

  node_setName(newNode, "");
  node_setId(newNode, 0);
  node_setLabel(newNode, WHITE);
  node_setNConnect(newNode, 0);

  return newNode;
}

void node_free(void * n){
  if(!n) return;
  
  free(n);

  return;
}

long node_getId (const Node * n){
  if(!n) return ERROR;

  return n->id;
}

char* node_getName (const Node * n){
  if(!n) return NULL;

  return (char *)n->name;
}

int node_getConnect (const Node * n){
  if(!n) return ERROR;

  return n->nConnect;
}

Label node_getLabel (const Node*n){
  if(!n) return ERROR_NODE;

  return n->label;
}

Status node_setLabel (Node *n, Label l){
  if(!n || l == ERROR_NODE) return ERROR;

  n->label = l;

  return OK;
}

Status node_setId (Node *n, const long id){
  if(!n || id == -1) return ERROR;

  n->id = id;

  return OK;
}

Status node_setName (Node *n, const char *name){
  if(!n || !name) return ERROR;

  strcpy(n->name, name);

  return OK;
}

Status node_setNConnect (Node *n, const int cn){
  if(!n || cn == -1) return ERROR;

  n->nConnect = cn;

  return OK;
}

int node_cmp (const void *n1, const void *n2){
  int cmp;

  if(!n1 || !n2) return ERROR;

  cmp = strcmp(node_getName(n1), node_getName(n2));

  if(node_getId(n1) == node_getId(n2)){
    return cmp;
  }
  else if(node_getId(n1) < node_getId(n2)){
    return -1;
  }
  else return 1;
}

void * node_copy (const void *src){
  Node *des = NULL;

  des = node_init();

  des->id = node_getId(src);
  des->nConnect = node_getConnect(src);
  des->label = node_getLabel(src);
  strcpy(des->name, node_getName(src));

  return des;
}

int node_print (FILE *pf, const void *n){
  int i = 0;

  if(!n) return ERROR;

  i = fprintf(pf, "[%ld, %s, %d, %d]\n",node_getId(n), node_getName(n), node_getConnect(n), node_getLabel(n));

  return i;
}


