#pragma once

typedef struct no{

    void* reg;
    int altura;
    struct no* esq;
    struct no* dir;
}t_no;

typedef struct{
    t_no* raiz;
    int (*cmp)(void*, void*);
}t_avl;

t_avl* cria_avl(int (*cmp)(void*, void*));
t_no* cria_no(void* reg);
void rebalanceia(t_no** sub_arv);
int max(int a, int b);
int altura_no(t_no* no);
void insere_no(t_avl* arv, t_no** no_atual, void* reg);
void insere_AVL(t_avl* arv, void* reg);
void rot_esq(t_no** sub_arv);
void rot_dir(t_no** sub_arv);
void * busca_AVL(t_avl* arv, void* reg);
void * busca_no(t_avl* arv, t_no* no_atual, void* reg);
t_no** percorre_esq(t_no** sub_arv);
void * remove_AVL(t_avl* arv, void* item);
void * _remove_no(t_avl* arv, t_no** no, void* item);
void destroi_AVL(t_no* no);

void percorre(t_no* no);