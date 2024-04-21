#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

int cmp(const void* n1, const void* n2){
    return *((int*)n1) - *((int*)n2);
}
void preOrdem(t_no* no);
void inOrdem(t_no* no);
void posOrdem(t_no* no);

int main(){

    t_arvore *arv = initArvore(cmp);

    int v[10] = {10, 7, 15, 5, 9, 20, 18, 16, 19, 4};
    
    for(int i = 0; i < 10; i++){
        insereABB(arv,v+i);
    }
    preOrdem(arv->raiz);
    printf("\n\n");
    inOrdem(arv->raiz);
    printf("\n\n");
    posOrdem(arv->raiz);
    printf("\n");

    apagaABB(arv);

    return EXIT_SUCCESS;
}

void preOrdem(t_no* no){
    printf("%d ",*(int*)(no->conteudo));

    if(no->esq){
        preOrdem(no->esq);
    }
    if(no->dir){
        preOrdem(no->dir);
    }
}

void inOrdem(t_no* no){

    if(no->esq){
        inOrdem(no->esq);
    }
    printf("%d ",*(int*)(no->conteudo));
    if(no->dir){
        inOrdem(no->dir);
    }
}
void posOrdem(t_no* no){

    if(no->esq){
        posOrdem(no->esq);
    }
    if(no->dir){
        posOrdem(no->dir);
    }
    printf("%d ",*(int*)(no->conteudo));
}