#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct{
    void* table;
    int size;
    int max;
    int sizeVar;
    int (*cmp)(const void*, const void*);
}t_heap;

t_heap * initHeap(int max, int sizeVar, int (*cmp)(const void*, const void*));

int pai(int n);
int filho_esq(int n);
int filho_dir(int n);

void constroi_heap(t_heap* heap);
int insere_elemento(t_heap* heap, int valor);

void desce(t_heap* heap, int n);
void sobe(t_heap* heap, int n);
void* get_max(t_heap* heap);
void* extrair_max(t_heap* heap);
int altera_prioridade(t_heap* heap, void* valor, int onde);
void* heap_sort(t_heap* heap);
void free_heap(t_heap* heap);