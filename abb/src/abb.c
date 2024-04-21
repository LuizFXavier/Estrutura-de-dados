#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

t_arvore* initArvore(int (*cmp)(const void*, const void*)){
    t_arvore *arv = malloc(sizeof(t_arvore));

    arv->cmp = cmp;
    arv->raiz = NULL;
}

void* buscaABB(t_arvore* arvore, void* reg){
    
    t_no* atual = arvore->raiz;
    
    while (atual)
    {
        if(arvore->cmp(atual->conteudo, reg) == 0){
            return atual->conteudo;
        }
        else if(arvore->cmp(atual->conteudo, reg) < 0){
            
            atual = atual->dir;
        }
        else{
            
            atual = atual->esq;
        }
        
    }
    return NULL;
}

int insereABB(t_arvore* arvore, void* reg){
    
    if(!arvore->raiz){
        arvore->raiz = (t_no*)malloc(sizeof(t_no));
        arvore->raiz->conteudo = reg;
        return EXIT_SUCCESS;
    }

    t_no* no_atual = arvore->raiz;
    while (no_atual)
    {
        if(arvore->cmp(no_atual->conteudo, reg) < 0){
            
            if(no_atual->dir == NULL){
                no_atual->dir = (t_no*)malloc(sizeof(t_no));
                no_atual->dir->conteudo = reg;
                return EXIT_SUCCESS;
            }
            no_atual = no_atual->dir;
        }
        else{

            if(no_atual->esq == NULL){
                no_atual->esq = (t_no*)malloc(sizeof(t_no));
                no_atual->esq->conteudo = reg;
                return EXIT_SUCCESS;
            }
            no_atual = no_atual->esq;
        }
    }
}

void apagaABB(t_arvore* arvore){
    apagaNos(arvore->raiz);
    free(arvore);
}
void apagaNos(t_no* no){

    if(no->esq){
        apagaNos(no->esq);
    }
    if(no->dir){
        apagaNos(no->dir);
    }
    free(no);
}