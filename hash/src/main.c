#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

typedef struct{
    char * nome;
    int * idade;
}aluno;

char *get_key(const void * aln){
    
    aluno* a = (aluno*)aln;

    return a->nome;
}


int main(){

    t_hash* t = criaHash(5, get_key);
    
    aluno* a = (aluno*)malloc(sizeof(aluno));

    a->idade = 19;
    a->nome = "Sandor";
    
    insereHash(t, a);

    for(int i = 0; i < t->max; i++){
        printf("%p\n",t->tabela[i]);
    }

    printf("\ndel: %p\n\n",t->deletado);
    // removeHash(t, get_key(a));

    for(int i = 0; i < t->max; i++){
        printf("%p\n",t->tabela[i]);
    }
    aluno* pedro = (aluno*)buscaHash(t, get_key(a));

    if(pedro)
        printf("%d\n",pedro->idade);

    apagaHash(t);

    return EXIT_SUCCESS;
}