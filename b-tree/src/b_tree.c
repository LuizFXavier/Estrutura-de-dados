#include <stdlib.h>
#include <stdio.h>
#include "b_tree.h"

t_no* cria_no(int t){
    
    t_no* novo = (t_no*) malloc(sizeof(t_no));
    novo->n = 0;
    novo->chaves = calloc(t+1, sizeof(void*));
    novo->filhos = calloc(t+2, sizeof(t_no*));

    for(int i = 0; i < t+1;i++){
        novo->filhos[i] = NULL;
    }

    return novo;
}

t_arvB *cria_arvore(int t, int (*cmp)(void *, void *))
{
    t_arvB* nova = (t_arvB*) malloc(sizeof(t_arvB));

    nova->raiz = cria_no(t);
    nova->raiz->folha = TRUE;
    nova->t = t;
    nova->cmp = cmp;

    return nova;
}

void insere_Btree(t_arvB *arv, void *item)
{
    _insere_Btree(arv, arv->raiz, item);
}

void _insere_Btree(t_arvB *arv, t_no *no, void *item)
{
    if(no->folha){
        _insereNaoCheio(arv, no, item);

        if(no->n > arv->t){
            _split_Btree(arv, no);
        }
        return;
    }

    int i = 0;
    while (i < no->n && arv->cmp(no->chaves[i], item) < 0)
    {
        i++;
    }
    int tamFilho = no->filhos[i]->n;
    _insere_Btree(arv, no->filhos[i], item);

    if(no->filhos[i]->n < tamFilho){ //Houve split no filho
        
        _promove(arv, no, no->filhos[i], i);
    }
    if(no->n > arv->t){
        _split_Btree(arv, no);
    }

    
}
void _promove(t_arvB *arv, t_no* dest, t_no* src, int i){
    

    for(int j = dest->n; j > i; j--){
        dest->chaves[j] = dest->chaves[j-1];
    }
    for(int j = dest->n + 1; j > i; j--){
        dest->filhos[j] = dest->filhos[j-1];
    }

    dest->chaves[i] = src->chaves[0];
    dest->filhos[i] = src->filhos[0];
    dest->filhos[i+1] = src->filhos[1];

    free(src);
    dest->n += 1;

}
void _split_Btree(t_arvB *arv, t_no* no){

    int meio = no->n / 2;


    t_no* esq = cria_no(arv->t);
    t_no* dir = cria_no(arv->t);

    esq->folha = FALSE;
    dir->folha = FALSE;
    
    for(int i = 0; i < meio; i++){
        _insereNaoCheio(arv, esq, no->chaves[i]);
        esq->filhos[i] = no->filhos[i];
    }

    esq->filhos[meio] = no->filhos[meio];

    for(int i = meio +1; i < no->n; i++){
        _insereNaoCheio(arv, dir, no->chaves[i]);
        dir->filhos[i - meio -1] = no->filhos[i];
    }
    

    dir->filhos[no->n - meio -1] = no->filhos[no->n];

    no->chaves[0] = no->chaves[meio];

    no->filhos[0] = esq;
    no->filhos[1] = dir;

    
    no->n = 1;
    no->folha = FALSE;


    if(!dir->filhos[0]){
        dir->folha = TRUE;
        esq->folha = TRUE;
    }
    else{
        dir->folha = FALSE;
        esq->folha = FALSE;
    }

}

void _insereNaoCheio(t_arvB *arv, t_no *no, void *item)
{   

    no->chaves[no->n] = item;
    
    for(int i = no->n; i > 0; i--){

        if(arv->cmp(no->chaves[i], no->chaves[i-1]) > 0)
            break;
        void* aux = no->chaves[i];
        no->chaves[i] = no->chaves[i-1];
        no->chaves[i-1] = aux;
    }
    no->n += 1;
}

void percorre(t_no* no){
    if(!no->folha)
        printf("\n");
    for(int i = 0; i < no->n; i++){
        printf("%d ", *(int*)(no->chaves[i]));
    }
    printf("; ");
    if(no->folha){
        return;
    }
    printf("\n");
    for(int i = 0; i < no->n+1; i++){

    
        if(no->filhos[i]){
            percorre(no->filhos[i]);
        }
    }
}

void *busca_Btree(t_arvB *arv, void *item)
{
    return _busca_Btree(arv, arv->raiz, item);
}
void *_busca_Btree(t_arvB *arv, t_no* no, void* item){

    int i = _busca_no(arv, no, item);
    if(i != -1){
        
        return no->chaves[i];
    }
    else if (i == -1 && no->folha){
        
        return NULL;
    }
    
    i = 0;
    while (arv->cmp(no->chaves[i], item) < 0 && i < no->n)
    {
        i++;
    }
    return _busca_Btree(arv,no->filhos[i],item);
    
    
}
int _busca_no(t_arvB *arv, t_no* no, void* item){
    
    for(int i = 0; i < no->n; i++){
        if(arv->cmp(no->chaves[i], item) == 0)
            return i;
    }
    return -1;
}

int remove_Btree(t_arvB *arv, void *item)
{   
    int ret = _remove_Btree(arv, arv->raiz, item);

    if(arv->raiz->n == 0){
        if(arv->raiz->filhos[0]){

        t_no* aux = arv->raiz;
        arv->raiz = arv->raiz->filhos[0];
        free(aux);
        }
        printf("Raiz ficou vazia!\n");
    }
    return ret;
}

int _remove_Btree(t_arvB* arv, t_no* no, void* item){
    
    
    int rPos = _busca_no(arv, no, item);
    int ret;

    if(rPos != -1 && no->folha){
        _remove_na_pagina(no, rPos);
        return TRUE;
    }
    if(rPos == -1 && no->folha){
        return FALSE;
    }

    int i = 0;
    int qIrmaoEsq = -1;
    int qIrmaoDir = -1;

    if(rPos != -1){
          
        void * ant = antecessor(no->filhos[rPos]);
        no->chaves[rPos] = ant;
        ret = _remove_Btree(arv, no->filhos[rPos], ant);
        i = rPos;
    }
    else{
        
        while (i < no->n && arv->cmp(no->chaves[i], item) < 0){
            i++;
        }
        ret = _remove_Btree(arv, no->filhos[i], item);

    }

    if(no->filhos[i]->n != 0) //Não faz nada caso não haja filhos de tamanho zero
        return ret;

    if(i-1 >= 0)
        qIrmaoEsq = no->filhos[i-1]->n;
    if(i+1 <= no->n)
        qIrmaoDir = no->filhos[i+1]->n;

    if(qIrmaoEsq <= 1 && qIrmaoDir <= 1){
        merge(arv, no, i);
    }
    else{
        _rouba_irmao(arv, no, i);
    }
    return ret;

}
void merge(t_arvB *arv, t_no *no, int fPos)
{
    int irmao;
    int cPos;
    int nIrmao;

    if(fPos != 0){
        printf("Merge com a esquerda!\n");

        irmao = fPos -1;
        cPos = fPos-1;
        nIrmao = no->filhos[irmao]->n;

        no->filhos[irmao]->chaves[nIrmao] = no->chaves[cPos];
        nIrmao += 1;

        no->filhos[irmao]->n = nIrmao;
        no->filhos[irmao]->filhos[nIrmao] = no->filhos[fPos]->filhos[0];
        
    }
    else{
        printf("Merge com a direita!\n");
        irmao = fPos +1;
        cPos = fPos;
        nIrmao = no->filhos[irmao]->n;

        for(int i = nIrmao+1; i > 0; i--){ //Shift a direita do irmão para receber chave do nó pai

            no->filhos[irmao]->chaves[i] = no->filhos[irmao]->chaves[i-1];
            no->filhos[irmao]->filhos[i] = no->filhos[irmao]->filhos[i-1];
        }
        nIrmao += 1;

        no->filhos[irmao]->n = nIrmao;
        no->filhos[irmao]->chaves[0] = no->chaves[cPos];
        no->filhos[irmao]->filhos[0] = no->filhos[fPos]->filhos[0];

    }

    free(no->filhos[fPos]);

    if(fPos != 0)
        for(int i = cPos; i < no->n; i++){ //Shift a esquerda do nó pai
            no->chaves[i] = no->chaves[i+1];
            no->filhos[i+1] = no->filhos[i+2];
        }
    else
        for(int i = cPos; i < no->n; i++){ //Shift a esquerda do nó pai
            no->chaves[i] = no->chaves[i+1];
            no->filhos[i] = no->filhos[i+1];
        }

    no->n -=1;

}

void _rouba_irmao(t_arvB *arv, t_no *no, int fPos)
{   
    int irmao;
    int cPos;
    int nIrmao;
    if(fPos != 0 && no->filhos[fPos-1]->n > 1){
        printf("Rouba da esquerda!\n");

        irmao = fPos -1;
        cPos = fPos -1;
        nIrmao = no->filhos[irmao]->n;

        no->filhos[fPos]->chaves[0] = no->chaves[cPos]; //Passar chave de pai para filho
        no->filhos[fPos]->filhos[1] = no->filhos[fPos]->filhos[0]; //Shift a direita do filho do assaltante
        no->filhos[fPos]->filhos[0] = no->filhos[irmao]->filhos[nIrmao]; //Sequestro de sobrinho
        
        nIrmao -=1;
        no->chaves[cPos] = no->filhos[irmao]->chaves[nIrmao];
        no->filhos[irmao]->n = nIrmao;
    }
    else{
        printf("Rouba da direita!\n");

        irmao = fPos +1;
        cPos = fPos;
        nIrmao = no->filhos[irmao]->n;

        no->filhos[fPos]->chaves[0] = no->chaves[cPos]; //Passar chave de pai para filho
        no->filhos[fPos]->filhos[1] = no->filhos[irmao]->filhos[0]; //Passar sobrinho para o irmão que rouba
        
        no->chaves[cPos] = no->filhos[irmao]->chaves[0]; //Passar chave da vítima para o pai
        
        for(int i = 0; i < nIrmao; i++){ //Shift à esquerda do irmão para tirar chave e filho roubados

            no->filhos[irmao]->chaves[i] = no->filhos[irmao]->chaves[i+1];
            no->filhos[irmao]->filhos[i] = no->filhos[irmao]->filhos[i+1];
        }
        nIrmao -=1;
        no->filhos[irmao]->n = nIrmao;
    }

    no->filhos[fPos]->n = 1;
    percorre(no);
    printf("\n");
}

void* antecessor(t_no* no){
    if(!no->folha)
        return antecessor(no->filhos[no->n]);
    else
        return no->chaves[no->n-1];
}
void _remove_na_pagina(t_no *no, int pos)
{

    for(int i = pos; i < no->n; i++){
        no->chaves[i] = no->chaves[i+1];
    }
    no->n -=1;
}