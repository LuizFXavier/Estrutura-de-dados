#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int compare(void* a, void* b){
    return *(int*)a - *(int*)b;
}


int main(){

    t_avl* arv = cria_avl(compare);

    int v[] = {0,1,2,3,4,5,6,7,8};

    for(int i = 0; i < (sizeof(v) / sizeof(v[0])); i++){
        
        insere_AVL(arv, (v+i));
    }
    printf("Pré:\n");

    percorre(arv->raiz);

    int *p = (int*) busca_AVL(arv, v+1);

    printf("p:%d\n",*p);

    printf("Pós:\n");

    p = (int*)remove_AVL(arv, p);
    remove_AVL(arv, p);

    percorre(arv->raiz);

    destroi_AVL(arv->raiz);

    free(arv);

    return EXIT_SUCCESS;
}