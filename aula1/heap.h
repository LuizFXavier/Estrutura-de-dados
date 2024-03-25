#ifndef __HEAP__
#define __HEAP__

int pai(int filho);
int filho_esq(int pai);
int filho_dir(int pai);
void gerar_heap(int*lista, int max_size);
void desce(int pai, int*lista, int n);
void troca(int v[], int n, int m);
int acessa_max(int v[]);
void heap_sort(int v[], int tam);
void inserir_elemento(int v[], int *tam, int max, int valor);
void alterar_prioridade(int v[], int pos, int valor, int tam);

#endif