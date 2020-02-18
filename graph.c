#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "graph.h"

#define MAX_NODES 256 /*!< Maximum node name length */

/*Defini de funciones privadas*/

int find_node_index(const Graph *, long);
int* graph_getConnectionsIndex(const Graph *, int);

/*Definition of the structure*/
struct _Graph {
    Node *nodes[MAX_NODES]; /*!<Array with the graph nodes */
    Bool connections[MAX_NODES][MAX_NODES]; /*!<Adjacency matrix */
    int num_nodes; /*!<Total number of nodes in te graph */
    int num_edges; /*!<Total number of connection in the graph */
};


Graph * graph_init (){
    int i, j;

    Graph *g = NULL;

    g=(Graph*)malloc(sizeof(Graph));

    if(!g) return NULL;
    
    g->num_nodes=0;
    g->num_edges=0;

    for(i=0; i < MAX_NODES; i++){
        g->nodes[i]=NULL;
        for(j=0; j<MAX_NODES; j++){
            g->connections[i][j] = 0;
        }
    }

    return g;
}

void graph_free (Graph *g){
    int i;
    for(i=0; i<g->num_nodes; i++){
        node_free(g->nodes[i]);
    }

    free(g);
}

Status graph_insertNode (Graph *g, const Node *n){
  Node* aux = NULL;
  int i;

  if(!g) return ERROR;
  if(!n) return ERROR;
  
  if(find_node_index(g, node_getId(n)) != -1) return ERROR;

  aux = node_copy(n);

  g->nodes[g->num_nodes]= aux;

  for(i=0; i<g->num_nodes; i++){
    g->connections[i][g->num_nodes]=0;
  }

  for(i=0; i<g->num_nodes; i++){
    g->connections[g->num_nodes][i]=0;
  }

  g->num_nodes++;

  return OK;
}

Status graph_insertEdge (Graph *g, const long nId1, const long nId2){

  long f1, f2;

  if(!g) return ERROR;


  f1 = find_node_index(g, nId1);
  f2 = find_node_index(g, nId2);

  if(f1 == -1) return ERROR;
  if(f2 == -1) return ERROR;

  g->connections[f1][f2] = 1;

  return OK;
}

Node *graph_getNode (const Graph *g, long nId){

  Node *n = NULL;
  int i;

  if(!g) return NULL;

  i = find_node_index(g, nId);

  n = g->nodes[i];

  return n;
}

Status graph_setNode (Graph *g, const Node *n){
  int f;

  if(!g || !n) return ERROR;

  f=find_node_index(g, node_getId(n));

  if(f == -1) return ERROR;

  g->nodes[f]=node_copy(n);

  return OK;
}

long * graph_getNodesId (const Graph *g){
  int i, num;
  long* Ids = NULL;

  num = graph_getNumberOfNodes(g);

  Ids = (long*) malloc(num * sizeof(long));

  for(i = 0; i < num; i++){
    Ids[i] = node_getId(g->nodes[i]);
  }

  return Ids;
}

int graph_getNumberOfNodes (const Graph *g){
  
  if(!g) return -1;

  return g->num_nodes;
}

int graph_getNumberOfEdges (const Graph *g){
  int i, j, k;

  if(!g) return -1;

  for(i=0; i<g->num_nodes; i++){
    for(j=0; j<g->num_nodes; j++){
      if(g->connections[i][j]==TRUE)
        k++;
      }
    }
    return k;
}

Bool graph_areConnected (const Graph *g, const long nId1, const long nId2){
  int i, j;

  if(!g) return FALSE;
  if(nId1 < 0 || nId2 < 0) return FALSE;

  i = find_node_index(g, nId1);
  j = find_node_index(g, nId2);

  return g->connections[i][j];
}

int graph_getNumberOfConnectionsFrom (const Graph *g, const long fromId){
  int i, num, k = 0;
  long* j = NULL;

  if(!g) return ERROR;
  if(fromId < 0) return ERROR;

  num = graph_getNumberOfNodes(g);
  j = graph_getNodesId(g);

  for(i = 0; i < num; i++){
    if(graph_areConnected(g, fromId, j[i])) k++;
  }

  free(j);

  return k;
}

long* graph_getConnectionsFrom (const Graph *g, const long fromId){
  int i, num, k = 0;
  long* j = NULL;
  long* x = NULL;

  if(!g) return NULL;
  if(fromId < 0) return NULL;

  num = graph_getNumberOfConnectionsFrom(g, fromId);
  if(num == 0) return NULL;

  j = graph_getNodesId(g);

  x = (long*) malloc(num * sizeof(long));
  if(!x) return NULL;

  for(i = 0; i < num; i++){
    if(graph_areConnected(g, fromId, j[i])){
      x[k] = j[i];
      k++;
    }
  }

  free(j);

  return x;
}

int graph_print (FILE *pf, const Graph *g){
  int i, j, k = 0;
  long* gNodes = NULL;
  long* con = NULL;

  gNodes = graph_getNodesId(g);

  for(i=0; i<g->num_nodes; i++){
    k += node_print(pf, graph_getNode(g, gNodes[i]));
    con = graph_getConnectionsFrom(g, gNodes[i]);

    for(j = 0; j < graph_getNumberOfConnectionsFrom(g, gNodes[i]); j++){
      k += fprintf(pf, " %ld", con[j]);
    }
    fprintf(pf, "\n");
    free(con);
  }

  free(gNodes);
  

  return k;
}

Status graph_readFromFile (FILE *fin, Graph *g){
  Node *n = NULL;
  char buffer[MAX_NODES], name[MAX_NODES];
  int i, num = 0, id1, id2;
  Status flag = ERROR;

  if(fgets(buffer, MAX_NODES, fin)){
    if(sscanf(buffer, "%d", &num) != 1) return flag;
  }

  n = node_init();
  if(!n) return flag;

  for(i = 0; i < num; i++){
    if(fgets(buffer, MAX_NODES, fin)){
      if(!sscanf(buffer, "%d %s", &id1, name)) break;
    }
    node_setName(n, name);
    node_setId(n, id1);
    if(graph_insertNode(g, n) == flag) break;
  }

  if(i < num){
    node_free(n);
    return flag;
  }

  while(fgets(buffer, MAX_NODES, fin)){
    if(sscanf(buffer, "%d %d", &id1, &id2)){
      if(graph_insertEdge(g, id1, id2) == flag) break;
    }
  }

  if(feof(fin)) flag = OK;

  node_free(n);

  return flag;
}

int find_node_index(const Graph * g, long nId1) {
  int i;
  
  if (!g) return -1;
  
  for(i=0; i < g->num_nodes; i++) {
    if (node_getId (g->nodes[i]) == nId1) return i;
  }

  return -1;
}

int* graph_getConnectionsIndex(const Graph * g, int index) {
  int *array = NULL, i, j = 0, size;
  
  if (!g) return NULL;
  
  if (index < 0 || index >g->num_nodes) return NULL;
  
  size = node_getConnect (g->nodes[index]);
  
  array = (int *) malloc(sizeof (int) * size);
  if (!array) {

  fprintf (stderr, "%s\n", strerror(errno));
  return NULL;
  }

  for(i = 0; i< g->num_nodes; i++) {
    if (g->connections[index][i] == TRUE) {
      array[j++] = i;
    }
  }

  return array;
}
