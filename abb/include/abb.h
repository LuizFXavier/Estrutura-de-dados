#pragma once

typedef struct no
{
    void * conteudo;
    struct no* esq;
    struct no* dir;

}t_no;

typedef struct{
    t_no * raiz;
    int (*cmp)(const void*, const void*);

}t_arvore;

t_arvore* initArvore(int (*cmp)(const void*, const void*));
int insereABB(t_arvore* arvore, void* reg);
void* buscaABB(t_arvore* arvore, void* reg);
void removeABB(t_arvore* t_arvore, void* reg);
void apagaABB(t_arvore* arvore);
void apagaNos(t_no* no);