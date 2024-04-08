#include "heap.h"

int pai(int n){
    return (n - 1) / 2;
}
int filho_esq(int n){
    return (n * 2) + 1;
}
int filho_dir(int n){
    return (n * 2) + 2;
}

void gerar_heap(t_heap* heap){

    for(int i = heap->size - 1; i > 0; i--)
        desce(heap, pai(i));
    
}
void troca(t_heap* heap, int n1, int n2){
    void * temp = heap->table + n1;

}
int insere_elemento();

void desce(t_heap* heap, int n){
    int f_esq = filho_esq(n);
    int f_dir = filho_dir(n);

    int maior = n;

    if(heap->cmp((heap->table)+ n, (heap->table) + f_dir) < 1){
        maior = f_esq;
    }
    else if(heap->cmp((heap->table) + n, (heap->table) + f_esq) < 1){
        maior = f_dir;
    }

    if(maior != n){

    }
}

void sobe(t_heap* heap, int n);