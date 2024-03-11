#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int pai(int filho);
int filho_esq(int pai);
int filho_dir(int pai);
void gerar_heap(int*lista, int max_size);
void desce(int pai, int*lista, int n);

int main(void){
    int v[7] = { 88,3,92,4,15,81,51};

    gerar_heap(v,7);

    for (int i = 6; i >= 0; i--){
        for(int j = 0; j < i; j++){
            printf(" ");
        }
        printf("%d\n",v[i]);
    }

    return EXIT_SUCCESS;
}

void gerar_heap(int*lista, int max_size){

    for (int i = pai(max_size -1); i >= 0; --i)
        desce(i, lista, max_size);
}

void desce(int pai, int*lista, int n){
    int f_esq = filho_esq(pai);
    int f_dir = filho_dir(pai);

    int maior_filho;

    if (f_dir < n && lista[f_dir] > lista[f_esq]){
        maior_filho = f_dir;
    }
    else if (f_esq < n){
        maior_filho = f_esq;
    }
    else{
        maior_filho = pai;
    }
    
    if (maior_filho != pai && lista[maior_filho] > lista[pai]){
        int aux = lista[maior_filho];
        lista[maior_filho] = lista[pai];
        lista[pai] = aux;

        desce(maior_filho, lista, n);
    }
}

int pai(int filho){
    return (filho - 1) / 2;
}

int filho_esq(int pai){
    return (pai * 2) + 1;
}

int filho_dir(int pai){
    return 2 * (pai + 1);
}