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

void desce(int n, int*lista, int max){
    int f_esq = filho_esq(n);
    int f_dir = filho_dir(n);

    int maior_filho;

    if (f_dir < max && lista[f_dir] > lista[f_esq]){
        maior_filho = f_dir;
    }
    else if (f_esq < max){
        maior_filho = f_esq;
    }
    else{
        maior_filho = n;
    }
    
    if (maior_filho != pai && lista[maior_filho] > lista[pai]){
        
        troca(lista, n, maior_filho);
        desce(maior_filho, lista, max);
    }
}

void alterar_prioridade(int v[], int pos, int valor, int tam){
    if (pos < tam){
        v[pos] = valor;
        sobe(v, pos);
        desce(pos, v, tam)
    }
}

void inserir_elemento(int v[], int *tam, int max, int valor){
    if(tam >= max){
        return;
    }

    v[tam] = valor; // O tamanho do vetor é também o valor do endereço da última posição dele

    sobe(tam);

    *tam += 1;
}

void heap_sort(int v[], int tam){
    // faz muito épico
}

int acessa_max(int v[]){
    return v[0];
}

int extrair_max(int v[], int* tam){
    v[0] = v[tam - 1];
    *tam -= 1;
    desce(v,0)
}

void sobe(int v[], int n){
    int pai = pai(n);

    if(v[pai] < v[n]){
        troca(v, n, pai);
        sobe(v,pai);
    }
}

void troca(v[], n, m){
    int aux = v[n];
    v[n] = v[m];
    v[m] = aux;
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