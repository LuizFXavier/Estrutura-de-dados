#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int compare(void* a, void* b){
    return *(int*)a - *(int*)b;
}


int main(){

    t_avl* arv = cria_avl(compare);

    int v[] = {7,5,2,8,9,3,4};

    for(int i = 0; i < (sizeof(v) / sizeof(v[0])); i++){
        
        insere_AVL(arv, (v+i));
    }
    printf("Main:\n");

    percorre(arv->raiz);

    int *p = (int*) busca_AVL(arv, v+1);

    printf("p:%d\n",*p);

    destroi_AVL(arv->raiz);

    free(arv);

    return EXIT_SUCCESS;
}