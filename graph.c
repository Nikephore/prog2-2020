#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct _Graph {
    Node *nodes[MAX_NODES]; /*!<Array with the graph nodes */
    Bool connections[MAX_NODES][MAX_NODES]; /*!<Adjacency matrix */
    int num_nodes; /*!<Total number of nodes in te graph */
    int num_edges; /*!<Total number of connection in the graph */
};


Graph * graph_init (){
    int i, j;
    Graph *g=NULL;
    g=(Graph*)malloc(sizeof(Graph));
    if(!g) return NULL;
    
    g->num_nodes=0;
    g->num_edges=0;

    for(i=0; i<MAX_NODES; i++){
        g->nodes[i]=NULL;
        for(j=0; j<MAX_NODES; j++){
            g->connections[i][j];
        }
    }

    return g;
}

void graph_free (Graph *g){
    int i;
    for(i=0; i<g->num_nodes; i++0){
        node_destroy(g->nodes[i]);
    }

    free(g);
}

Status graph_insertNode (Graph *g, const Node *n){
  Node *aux;
  int i;

  if(!g) return ERROR;
  if(!n) return ERROR;

  aux=node_copy(n);

  g->nodes[g->num_nodes]=aux;

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


  f1=find_node_index(g, nId1);
  f2=find_node_index(g, nId2);

  if(f1==-1) return ERROR;
  if(f2==-1) return ERROR;

  g->connections[f1][f2]=1;

  return OK;
}

Node *graph_getNode (const Graph *g, long nId){

  Node *n;
  int i;

  if(!g) return NULL;

  i=find_node_index(g, nId);

  n=g->nodes[i];

  return n;
}

Status graph_setNode (Graph *g, const Node *n){
  int f;

  if(!g || !n) return ERROR;

  f=find_node_index(g, node_getId(n));

  if(f == -1) return ERROR;

  g->nodes[f]=node_copy(n);

  return OK
}

long * graph_getNodesId (const Graph *g){

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

}

int graph_getNumberOfConnectionsFrom (const Graph *g, const long fromId){

}

long* graph_getConnectionsFrom (const Graph *g, const long fromId){

}

int graph_print (FILE *pf, const Graph *g){

}

Status graph_readFromFile (FILE *fin, Graph *g){

}

// It returns the index of the node with id nId1
int find_node_index(const Graph * g, long nId1) {
  int i;
  
  if (!g) return -1;
  
  for(i=0; i < g->num_nodes; i++) {
    if (node_getId (g->nodes[i]) == nId1) return i;
  }
  // ID not found
  return -1;
}

// It returns an array with the indices of the nodes connected to the node
// whose index is index
// It also allocates memory for the array.
int* graph_getConnectionsIndex(const Graph * g, int index) {
  int *array = NULL, i, j = 0, size;
  
  if (!g) return NULL;
  
  if (index < 0 || index >g->num_nodes) return NULL;
  
  // get memory for the array
  size = node_getConnect (g->nodes[index]);
  
  array = (int *) malloc(sizeof (int) * size);
  if (!array) {
  // print error message
  fprintf (stderr, "%s\n", strerror(errno));
  return NULL;
  }
// assign values to the array with the indices of the connected nodes
  for(i = 0; i< g->num_nodes; i++) {
    if (g->connections[index][i] == TRUE) {
      array[j++] = i;
    }
  }
  return array;
}
