#pragma once
#define TRUE 1
#define FALSE 0

typedef struct no{
    int folha; //Guarda se é folha ou não
    int n; //Quantidade atual de items no nó

    void** chaves;
    struct no** filhos;

}t_no;

typedef struct{
    t_no* raiz;
    int t; //Quantidade de items em um nó

    int(*cmp)(void*, void*);
}t_arvB;

t_no* cria_no(int t);
t_arvB* cria_arvore(int t, int(*cmp)(void*, void*));

void insere_Btree(t_arvB *arv , void* item);
void _insere_Btree(t_arvB *arv , t_no *no, void* item);
void _insereNaoCheio(t_arvB *arv, t_no *no, void* item);
void _split_Btree(t_arvB *arv, t_no* no);
void _promove(t_arvB *arv, t_no* dest, t_no* src, int i);

void percorre(t_no* no);
void* antecessor(t_no* no);

void * busca_Btree(t_arvB *arv, void* item);
void *_busca_Btree(t_arvB *arv, t_no* no,void *item);
int _busca_no(t_arvB *arv, t_no* no, void* item);


int remove_Btree(t_arvB *arv, void* item);
int _remove_Btree(t_arvB* arv, t_no* no, void* item);
void _remove_na_pagina(t_no* no, int pos);
void merge(t_arvB *arv, t_no *no, int fPos);
void _rouba_irmao(t_arvB *arv, t_no *no, int fPos);