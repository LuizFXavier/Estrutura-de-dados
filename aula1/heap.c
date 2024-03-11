#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int pai(int filho);

int main(void){

    assert(pai(5) == 2);
    assert(pai(0) == 0);
    return EXIT_SUCCESS;
}

int pai(int filho){

    return (filho - 1) / 2;
}