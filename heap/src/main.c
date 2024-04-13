#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int cmp(const void * n1, const void * n2){

    if (*(char*)n1 < *(char*)n2)
        return 1;
    if (*(char*)n2 < *(char*)n1)
        return -1;
    if (*(char*)n1 == *(char*)n2)
        return 0;
}

int main(){

    t_heap* sas = initHeap(10, 1, cmp);
    insere_elemento(sas, 'D');
    insere_elemento(sas, 'C');
    insere_elemento(sas, 'B');
    insere_elemento(sas, 'E');
    insere_elemento(sas, 'A');
    insere_elemento(sas, 'F');
    insere_elemento(sas, 'G');


    int k = 7;

    for (int i = 0; i < k; i++)
        printf("%d: %c\n", i,*((char*)(sas->table) +i));

    heap_sort(sas);

    printf("----------------------\n");

    for (int i = 0; i < k; i++)
        printf("%d: %c\n", i,*((char*)(sas->table) +i));

    printf("----------------------\n");

    void * vet = heap_sort(sas);

    for(int i = 0; i < sas->size; i++){
        printf("%c ", *((char*)vet + i));
    }
    printf("\n");

    free(vet);

    return EXIT_SUCCESS;
}