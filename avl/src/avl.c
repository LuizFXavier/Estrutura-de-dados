#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

t_avl* cria_avl(int (*cmp)(void*, void*)){
    t_avl* nova = malloc(sizeof(t_avl));

    nova->raiz = NULL;
    nova->cmp = cmp;

    return nova;
}
t_no* cria_no(void* reg){
    t_no* novo = malloc(sizeof(t_no));
    
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->reg = reg;

    return novo;
}

int max(int a, int b){
    return a > b ? a:b;
}

int altura_no(t_no* no){
    if(no == NULL){
        return -1;
    }
    return no->altura;
}

void rebalanceia(t_no** sub_arv){
    int fatorB;
    int fB_filho;
    t_no* filho;

    fatorB = altura_no((*sub_arv)->esq) - altura_no((*sub_arv)->dir);

    if(fatorB == -2){ //Lado direito mais pesado
        filho = (*sub_arv)->dir;
        fB_filho = altura_no(filho->esq) - altura_no(filho->dir);

        if(fB_filho <= 0){
            rot_esq(sub_arv);
        }
        else{
            rot_dir(&((*sub_arv)->dir));
            rot_esq(sub_arv);
        }
    }
    if(fatorB == 2){
        filho = (*sub_arv)->esq;
        fB_filho = altura_no(filho->esq) - altura_no(filho->dir);

        if(fB_filho > 0){
            rot_dir(sub_arv);
        }
        else{
            rot_esq(&((*sub_arv)->esq));
            rot_dir(sub_arv);
        }
    }
    
}
void percorre(t_no* no){
    
    printf("%d: %d\n", *((int*)(no->reg)), no->altura);
    if(no->esq){
        percorre(no->esq);
    }
    if(no->dir){
        percorre(no->dir);
    }
}

void insere_no(t_avl* arv, t_no** no_atual, void* reg){

    if(arv->cmp((*no_atual)->reg, reg) < 0){
        if((*no_atual)->dir){
            
            insere_no(arv, &(*no_atual)->dir, reg);
        }
        else{
            (*no_atual)->dir = cria_no(reg);
            
        }
    }
    else{
        if((*no_atual)->esq){
            
            insere_no(arv, &(*no_atual)->esq, reg);
        }
        else{
            (*no_atual)->esq = cria_no(reg);
            
        }
    }
    (*no_atual)->altura = max(altura_no((*no_atual)->esq), altura_no((*no_atual)->dir)) + 1;

    rebalanceia(no_atual);
}

void insere_AVL(t_avl* arv, void* reg){

    if(arv->raiz == NULL){
        arv->raiz = cria_no(reg);
        return;
    }

    insere_no(arv, &arv->raiz, reg);
}

void rot_esq(t_no **sub_arv)
{
    t_no* X = *sub_arv;
    t_no* A = X->esq;
    t_no* Y = X->dir;
    t_no* B = Y->esq;
    t_no* C = Y->dir;

    X->esq = A;
    X->dir = B;
    Y->esq = X;
    *sub_arv = Y;

    X->altura = max(altura_no(A), altura_no(B)) + 1;
    Y->altura = max(altura_no(X), altura_no(C)) + 1;
}

void rot_dir(t_no **sub_arv)
{
    t_no* Y = *sub_arv;
    t_no* X = Y->esq;
    t_no* A = X->esq;
    t_no* B = X->dir;
    t_no* C = Y->dir;

    X->dir = Y;
    Y->esq = B;
    *sub_arv = X;

    Y->altura = max(altura_no(B), altura_no(C)) + 1;
    X->altura = max(altura_no(Y), altura_no(A)) + 1;

}

void *busca_AVL(t_avl *arv, void *reg)
{
    void * busca = busca_no(arv, arv->raiz, reg);
    return busca;
}

void destroi_AVL(t_no* no){
    if(no->esq){
        destroi_AVL(no->esq);
    }
    if(no->dir){
        destroi_AVL(no->dir);
    }
    free(no);   
}

void *busca_no(t_avl *arv, t_no *no_atual, void *reg)
{
    if(no_atual == NULL){
        return NULL;
    }
    else if(arv->cmp(no_atual->reg, reg) < 0){
        
        return busca_no(arv, no_atual->dir, reg);

    }
    else if(arv->cmp(no_atual->reg, reg) > 0){
        
        return busca_no(arv, no_atual->esq, reg);
    }
    else{
        return no_atual->reg;
    }
}
