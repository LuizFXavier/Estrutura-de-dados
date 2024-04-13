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

t_heap * initHeap(int max, int sizeVar, int (*cmp)(const void*, const void*)){

    t_heap* novaHeap = (t_heap*) malloc(sizeof(t_heap));

    novaHeap->sizeVar = sizeVar;
    novaHeap->max = max;
    novaHeap->size = 0;
    novaHeap->cmp = cmp;

    
    novaHeap->table = malloc(sizeVar * max);

    return novaHeap;
}

void constroi_heap(t_heap* heap){

    for(int i = heap->size - 1; i > 0; i--)
        desce(heap, pai(i));
    
}
void troca(t_heap* heap, int n1, int n2){
    void * temp = malloc(heap->sizeVar);

    memcpy(temp, heap->table + n1 * heap->sizeVar, heap->sizeVar);

    memcpy(heap->table + n1 * heap->sizeVar, heap->table + n2 * heap->sizeVar, heap->sizeVar);

    memcpy(heap->table + n2 * heap->sizeVar, temp, heap->sizeVar);

    free(temp);
}

int insere_elemento(t_heap* heap, int valor){
    
    if(heap->max == heap->size)
        return EXIT_FAILURE;

    memcpy(heap->table + heap->size * heap->sizeVar, &valor, heap->sizeVar);

    sobe(heap, heap->size);

    heap->size += 1;

    return EXIT_SUCCESS;
}

void desce(t_heap* heap, int n){
    int f_esq = filho_esq(n);
    int f_dir = filho_dir(n);

    int maior = n;

    if((f_dir < heap->size) && heap->cmp((heap->table)+ n * heap->sizeVar, (heap->table) + f_dir * heap->sizeVar) < 0){
        maior = f_dir;
    }

    if((f_esq < heap->size) && heap->cmp((heap->table) + maior * heap->sizeVar, (heap->table) + f_esq * heap->sizeVar) < 0){
        maior = f_esq;
    }

    if(maior != n){
        troca(heap, n, maior);
        desce(heap, maior);
    }
}

void sobe(t_heap* heap, int n){

    int paiN = pai(n);

    if(heap->cmp((heap->table)+ n * heap->sizeVar, (heap->table) + paiN * heap->sizeVar) > 0){

        troca(heap, n, paiN);
        sobe(heap, paiN);
    }
}

void* get_max(t_heap* heap){
    
    return heap->table;
}

void* extrair_max(t_heap* heap){
    void* max = malloc(heap->sizeVar);
    memcpy(max, heap->table, heap->sizeVar);

    memcpy(heap->table, heap->table + (heap->size -1) * heap->sizeVar, heap->sizeVar);

    heap->size -=1;

    desce(heap, 0);

    return max;
}

int altera_prioridade(t_heap* heap, void* valor, int onde){

    if (onde >= heap->size){
        return EXIT_FAILURE;
    }
    memcpy(heap->table + onde * heap->sizeVar, valor, heap->sizeVar);

    desce(heap, onde);
    sobe(heap, onde);

    return EXIT_SUCCESS;
}

void* heap_sort(t_heap* heap){

    int tam = heap->size;

    for (int i = tam -1; i >= 0; --i){

        troca(heap, 0, i);

        heap->size -=1;
        desce(heap, 0);
    }
    heap->size = tam;

    void * ret = malloc(tam * heap->sizeVar);

    memcpy(ret, heap->table, tam * heap->sizeVar);

    constroi_heap(heap);

    return ret;
}

void free_heap(t_heap* heap){
    free(heap->table);

    free(heap);
}