#ifndef VOID_VECTOR_BIBL_H_INCLUDED
#define VOID_VECTOR_BIBL_H_INCLUDED

#include <limits.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct vectorVoid{
    void *data;
    size_t size;
    size_t capacity;
    size_t baseTypeSize;// ������ �������� ����:
                        // ��������, ���� ������ ������ int -
                        // �� ���� baseTypeSize = sizeof(int)
                        // ���� ������ ������ float -
                        // �� ���� baseTypeSize = sizeof(float)
}vectorVoid;

vectorVoid createVoidVector(size_t *n, size_t baseTypeSize){

    vectorVoid vector;

    vector.data = (void *) malloc(*n * baseTypeSize);
    vector.size = 0;
    vector.capacity = *n;

    if (vector.data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    return vector;
}

void reserveVoid(vectorVoid *v, size_t newCapacity){

     if (newCapacity == 0){
        v->data = NULL;
    }

    if (newCapacity < v->size){
        v->size = newCapacity;
    }

    v->capacity = newCapacity;
    v->data = (void *) realloc(v->data, newCapacity * v->baseTypeSize);

    if (v->data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void shrinkToFitVoid(vectorVoid *v){

    v->data = (void *) realloc(v->data, v->size);

}

void clearVoid(vectorVoid *v){

    v->data = NULL;
}

void deleteVoidVector(vectorVoid *v){

    free(v->data);
    v->size = 0;
    v->capacity = 0;
    v->baseTypeSize = 0;
}

bool isEmptyVoid(vectorVoid *v){

    return v->data == NULL ? true : false;
}

bool isFullVoid(vectorVoid *v){

    return v->size == v->capacity ? true : false;
}

void getVoidVectorValue(vectorVoid *v, size_t index, void *destination){

    destination = v->data[index];

}

#endif // VOID_VECTOR_BIBL_H_INCLUDED
