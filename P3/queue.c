#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "types.h"

#define MAXQUEUE 64

/**
* @brief Structure to implement a queue. To be defined in queue_fp.c
*
**/
struct _Queue{
  void* items [MAXQUEUE];
  int front;
  int rear;
  free_element_function_type free_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
};
/**
* @brief Typedef for a function pointer to free a queue element
**/
typedef void (*destroy_element_function_type)(void*);
/**
* @brief Typedef for a function pointer to copy a queue element
**/
typedef void *(*copy_element_function_type)(const void*);
/**
* @brief Typedef for a function pointer to print a queue element
**/
typedef int (*print_element_function_type)(FILE *, const void*);
/**
* @brief This function initializes an empty queue.
*
13
* @param f1 A pointer to a funcion to free a element of the queue.
* @param f2 A pointer to a funcion to copy a element of the queue.
* @param f3 A pointer to a funcion to print a element of the queue.
* @return This function returns a pointer to the queue or a null
* pointer if insufficient memory is available to create the queue.
* */
Queue* queue_init(destroy_element_function_type f1,
copy_element_function_type f2, print_element_function_type f3){
  Queue *q = NULL;
  int i;

  q = (Queue *)malloc(sizeof(Queue));
  if(!q) return NULL;

  q->front = 0;
  q->rear = 0;
  q->destroy_element_function = f1;
  q->copy_element_function = f2;
  q->print_element_function = f3;

  for(i=0; i<MAXQUEUE; i++){
    q->items[i] = NULL;
  }

  return q;
}
/**
* @brief This function frees all the memory used by the queue.
* @param s A pointer to the queue
* */
void queue_free(Queue *q){
  int i;

  if(q != NULL){
    i = q->front;
    while(i != q->rear){
      q->destroy_element_function(q->items[i]);
      i = (i+1) % MAXQUEUE;
    }
    free(q);
  }
}
/**
* @brief Returns whether the queue is empty
* @param s A pointer to the queue.
* @return TRUE or FALSE
*/
Bool queue_isEmpty(const Queue *q){
  if(!q) return FALSE;

  if(q->front == q->rear) return TRUE;

  return FALSE;
}
/**
* @brief This function is used to insert a element at the queue.
*
* A copy of the element is added to the queue container and the
* size of the queue is increased by 1. Time complexity: O(1).
* This function allocates memory for a copy of the element.
* @param s A pointer to the queue.
* @param ele A pointer to the element to be inserted
* @return This function returns OK on success or ERROR if
* insufficient memory is available to allocate the element.
* */
Status queue_insert(Queue *q, const void* pElem){
  void *aux = NULL;

  if(!q || !pElem) return ERROR;

  aux = q->copy_element_function(pElem);
  if(!aux) return ERROR;

  q->items[q->rear] = aux;
  q->rear = (q->rear + 1) % MAXQUEUE;

  return OK;
}
/**
* @brief This function is used to extract a element from the top of the queue.
*
* The size of the queue is decreased by 1. Time complexity: O(1).
* @param s A pointer to the queue.
* @return This function returns a pointer to the extracted element
* on success or null when the queue is empty.
* */
void * queue_extract(Queue *q){
  void *e = NULL;

  if(!q) return NULL;
  if(queue_isEmpty(q) == TRUE) return NULL;

  e = q->items[q->front];
  q->items[q->front] = NULL;
  q->front = (q->front + 1) % MAXQUEUE;

  return e;
}
/**
* @brief This function returns the size of the queue.
*
* Time complexity: O(1).
* @param s A pointer to the queue.
* @return the queue size
*/
int queue_size (const Queue *q){
  int i, tam = 0;

  for(i=q->front; i!=q->rear; i=(i+1)%MAXQUEUE){
    tam++;
  }

  return tam;
}
/**
* @brief This function writes the elements of the queue to the stream.
* @param fp A pointer to the stream
* @param s A pointer to the element to the queue
* @return Upon successful return, these function returns the
* number of characters writted. The function returns a negative
* value if there was a problem writing to the file.
* */
int queue_print(FILE *pf, const Queue *q){
  int i, k = 0;

  if(!pf || !q) return -1;

  if(queue_isEmpty(q) == TRUE){
    fprintf(pf, "Cola vacia\n");
    return -1;
  }

  fprintf(pf, "Cola con %d elementos\n", queue_size(q));

  for(i=q->front; i!=q->rear; i=(i+1)%MAXQUEUE){
    k += q->print_element_function(pf, q->items[i]);
  }
  
  return k;
}
