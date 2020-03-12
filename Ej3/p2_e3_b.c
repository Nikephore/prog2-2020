#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "element.h"


int main(){
    char array[3]={'a', 'b', 'c'};
    Stack *s=NULL;
    Element *ele=NULL;
    int i;

    s=stack_init();
    if(!s) return -1;

    ele=element_init();
    if(!ele) return -1;

    for(i=0; i<3; i++){
      ele->a[i]=array[i];
      s->item[i]=ele->a[i];
    }



    for(i=0; i<3; i++){
        stack_push (s, &array[i]);
    }

    stack_print(stdout, s);

    fprintf(stdout, "Stack size: %ld\n", stack_size(s));

    while(stack_isEmpty(s)==FALSE){

        fprintf(stdout, "El elemento extraido: %c\n", *(char *)stack_pop(s));
    }

    fprintf(stdout, "Stack size: %ld\n", stack_size(s));

    stack_free(s);

    return 0;
}
