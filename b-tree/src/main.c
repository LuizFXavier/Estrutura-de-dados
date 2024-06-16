#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

int cmp(void* a, void* b){
    return *(int*)a - *(int*)b;
}

int main(){
    t_arvB *arv = cria_arvore(8, cmp);
    

    int v[] = {
            9, 26, 40, 2, 6, 43, 1, 42, 25, 47, 13, 18, 4, 21, 33, 46, 30, 45, 35, 28, 41, 5, 36, 10, 44, 50, 31, 48, 29, 22, 14, 12, 49, 32, 16, 8, 38, 11, 15, 39, 3, 7, 37, 17, 24, 23, 27, 19, 20, 34
    };
    int t[] = { 
            26, 42, 38, 43, 27, 36, 10, 30, 15, 5, 46, 21, 11, 49, 16, 8, 1, 18, 7, 35, 25, 28, 22, 39, 23, 33, 41, 44, 50, 29, 14, 37, 24, 4, 12, 47, 6, 32, 2, 40, 20, 48, 19, 45, 3, 34, 17, 31, 9, 13
};
    for(int i = 0; i < sizeof(v) / sizeof(int); i++){
       
        printf("Insere %d:\n",v[i]);
        insere_Btree(arv, v+i);
        percorre(arv->raiz);
        printf("\n\n");
    }

    percorre(arv->raiz);
    printf("\n");
    
    for(int i = 0; i < sizeof(t) / sizeof(int) ; i++){
        int k = t[i];
        
        printf("Remove %d:\n",k);
        remove_Btree(arv, &k);
        percorre(arv->raiz);
        printf("\n\n");
    }

    free(arv);

    return 0;
}