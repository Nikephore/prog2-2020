#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"

struct _Element {
    char *a;
}

Element * element_init(){
    Element *ele=NULL:

    ele=(Element *)malloc(sizeof(Element));
    if(!ele) return NULL;

    ele->c = NULL;

    return ele;
}
void element_free(Element *ele){
    if(!ele) return;

    free(ele->c);
    free(ele);

    return;
}

Element * element_setInfo(Element *, void*){

}
void * element_getInfo(Element *ele){
    if(!ele) return NULL;

    return ele;
}

Element * element_copy(const Element *ele){
    Element *s;
    
    s=element_init();
    if(!s) return NULL;

    element_setInfo(s, ele->c);

    return s;
}

Bool element_equals(const Element *e1, const Element *e2){
    if(!e1 || !e2) return FALSE;

    if(e1->c == e2->c) return TRUE;
    
    return FALSE;
}

int element_print(FILE *f, const Element *ele){
    int k=0;
    
    if(!f || !ele) return -1;

    k=fprintf(f, [%s], *(ele->c));

    if(!k) return -1;

    return k;
}