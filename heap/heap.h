#pragma once

typedef struct{
    void* table;
    int size;
    int max;
    int (*cmp)(const void*, const void*);
}t_heap;

int pai(int n);
int filho_esq(int n);
int filho_dir(int n);

void gerar_heap(t_heap* heap);
int insere_elemento();

void desce(t_heap* heap, int n);
void sobe(t_heap* heap, int n);