#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "element.h"


Status reverseWords (char *strout, const char *strin);

int main(){
  char in, *out=NULL;

  printf("Input: ");
  scanf("%s", &in);

  reverseWords(out, &in);

  printf("Output: %s", out);

  /*free(out);*/

    return 0;
}

/***@brief: Reverse the words of an input string to an output string.
* The words in the input string are separated by a space character.
* The strings may not overlap, and the destination string strout
* must be large enough to receive the inverted expression.
*
*@paramstrout, Pointer to the output buffer
*@paramstrin, Pointer to the input expression
*@returnThe function returns OK or ERROR
**/
Status reverseWords (char *strout, const char *strin){
  Stack *s=NULL;
  /*char aux[strlen(strin)];*/
  int i, j=0;

  s=stack_init();
  if(!s) return ERROR;

  for(i=0; i<strlen(strin); i++){
    if(strcmp((char *)stack_push(s, (const Element *)&strin[i]), "\0")){
      for(j=0; j<i; j++){
        strout[j]=*(char *)stack_pop(s);
      }
    }
  }

  stack_free(s);

  return OK;
}
