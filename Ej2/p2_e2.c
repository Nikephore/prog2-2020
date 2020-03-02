#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "stack_types.h"

Status infix2postfix (char *suf, const char *in);

/*Hay que añadir las funciones isOperator y int prec, y el define */

int main(){


    return 0;
}
/**
* @brief: Get the postfix expression of an infix expression.

* The infix and postfix strings may not overlap and
* the destination postfix string must be
* large enough to receive the infix expression
* (to be checked before calling this function).
*
* @param in Pointer to the infix expression
* @param suf Pointer to the suffix expression
* @return The function returns OK on success or ERROR
* when any of its parametrs is NULL
**/
Status infix2postfix (char *suf, const char *in){
  Status ret = TRUE;
  Stack *s = NULL;
  char *ele = NULL;
  int i = 0, j = 0;

  s=stack_init(char_free, char_copy, char_print);
  if(!s) return ERROR;

  while(in[i] != Eos){
    if(isOperator(in[i]) == TRUE){
      while((stack_isEmpty(s) == FALSE) && (prec(stack_top(s)) >= prec(in[i]))){
        ele = (char *)stack_pop(s);
        suf[j] = ele;
        j++;
      }
      stack_push(s, in[i]);
    }

    else if(in[i] == "("){
      stack_push(s, in[i]);
    }

    else if(in[i] == ")"){
      while((stack_isEmpty(s) == FALSE) && (stack_top(s) != "()")){
        ele = (char *)stack_pop(s);
        suf[j] = ele;
        j++;
      }
      stack_pop(s);
    }

    else{
      suf[j] = in[i];
      j++;
    }
    i++;
  }

  while(stack_isEmpty(s) == FALSE){
    ele = (char *)stack_pop(s);
    suf[j] = ele;
    j++;
  }

  stack_free(s);

  return TRUE;
}
