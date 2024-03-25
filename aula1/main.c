#include <stdio.h>
#include "heap.h"

int main(void){
    int v[7] = { 88,3,92,4,15,81,51};

    gerar_heap(v,7);

    for (int i = 6; i >= 0; i--){
        for(int j = 0; j < i; j++){
            printf(" ");
        }
        printf("%d\n",v[i]);
    }

    return 0;
}