#ifndef VECTOR_BIBL_H_INCLUDED
#define VECTOR_BIBL_H_INCLUDED

#include <malloc.h>
#include <stdio.h>

typedef struct vector{
    int *data;
    size_t size;
    size_t capacity;
}vector;

vector createVector(size_t n){

    vector vector;

    vector.data = (int *) malloc(n * sizeof(int));
    vector.size = 0;
    vector.capacity = n;

    if (vector.data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    return vector;
}

#endif // VECTOR_BIBL_H_INCLUDED
