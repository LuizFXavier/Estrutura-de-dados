#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#define SEED 0x123456

t_hash* criaHash(int tam, char *(*get_key)(const void*)){
    t_hash* nova = (t_hash*)malloc(sizeof(t_hash));

    nova->get_key = get_key;
    nova->max = tam;
    nova->size = 0;
    nova->deletado = (void*) nova->max;
    nova->tabela = (void**) calloc(tam, sizeof(void*));

    // for(int i = 0; i < tam; i++)
    //     nova->tabela[i] = NULL;

    return nova;
}

void apagaHash(t_hash* hash){
    if (hash == NULL)
        return;
    
    for(int i = 0; i < hash->max; i++){
        if(hash->tabela[i] != hash->deletado)
        free((hash->tabela[i]));
        
    }
    free(hash->tabela);
    free(hash);
}

int insereHash(t_hash* hash, void * bucket){
    uint32_t n = hash_f(hash->get_key(bucket), SEED);

    int pos = n % hash->max;

    if(hash->size +1 == hash->max){
        free(bucket);
        return EXIT_FAILURE;
    }

    for(;hash->tabela[pos] != hash->deletado && hash->tabela[pos]; pos = (pos +1) % hash->max){
        
    }

    hash->tabela[pos] = (void*)bucket;
    hash->size += 1;

    return EXIT_SUCCESS;
}
int removeHash(t_hash *hash, const char* key){

    int pos = hash_f(key, SEED) % hash->max;
    while (hash->tabela[pos] != hash->deletado && hash->tabela[pos] != 0)
    {
        if(hash->get_key((char*)hash->tabela[pos]) == key){
            hash->tabela[pos] = hash->deletado;

            return EXIT_SUCCESS;
        }
        pos = (pos+1) % hash->max;
    }
    return EXIT_FAILURE;
}

void * buscaHash(t_hash *hash, const char* key){
    int pos = hash_f(key, SEED) % hash->max;

    while (hash->tabela[pos] != hash->deletado && hash->tabela[pos] != 0)
    {
        if(hash->get_key((char*)hash->tabela[pos]) == key){
            return (void *)(hash->tabela[pos]);
        }
        pos = (pos+1) % hash->max;

    }

    return NULL;
}

uint32_t hash_f(const char* str, uint32_t h){
    for (; *str; ++str) {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}