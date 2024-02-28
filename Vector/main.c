#include <stdio.h>
#include "Vector_bibl.h"
#include <assert.h>

void test_pushBack_emptyVector(){

    vector v = createVector(5);

    pushBack(&v,10);

    printf("pushBack_emptyVector :%d\n", v.data[0]);

}

void test_pushBack_fullVector(){

    vector v = createVector(5);

    v.size = 5;
    v.data[0] = 40;
    v.data[1] = 40;
    v.data[2] = 40;
    v.data[3] = 40;
    v.data[4] = 40;

    pushBack(&v, 41);

    printf("\npushBack_fullVector: %d\n", v.data[5]);

}

void test_atVector_notEmptyVector(){

    vector v = createVector(5);

    v.size = 4;
    v.data[0] = 40;
    v.data[1] = 41;
    v.data[2] = 42;
    v.data[3] = 43;

    printf("\natVector_notEmptyVector address: %d\n", atVector(&v, 2));
    printf("\natVector_notEmptyVector value: %d\n", *atVector(&v, 2));
}

void test_atVector_requestToLastElement(){

    vector v = createVector(5);

    v.size = 3;
    v.data[0] = 40;
    v.data[1] = 40;
    v.data[2] = 40;

    printf("\nrequestToLastElement value: %d \n", *atVector(&v, 2));
    printf("\nrequestToLastElement address: %d \n", atVector(&v, 2));
}

void test_back_oneElementInVector(){

    vector v = createVector(5);

    v.size = 1;
    v.data[0] = 40;

    printf("\nback_oneElementInVector address: %d \n", back(&v));
    printf("\nback_oneElementInVector value: %d \n", *back(&v));
}

void test_front_oneElementInVector(){

    vector v = createVector(5);

    v.size = 1;
    v.data[0] = 30;

    printf("\nfront_oneElementInVector address: %d \n", front(&v));
    printf("\nfront_oneElementInVector value: %d \n", *front(&v));
}

tests(){

    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    test_back_oneElementInVector();
    test_front_oneElementInVector();


}


int main(){
/*
    vector v = createVector(3);

    v.size = 3;
    v.data[0] = 40;
    v.data[1] = 40;
    v.data[2] = 40;
    //v.data[3] = 40;*/

    vector v = createVector(0);
pushBack(&v, 10);
assert(v.size == 1);
popBack(&v);
assert(v.size == 0);
assert(v.capacity == 1);


    //printf("%d", atVector(&v,2));

    //printf("%d ", back(&v));
    //printf("%d", front(&v));

    //printf("%d\n", getVectorValue(&v,2));
    //reserve(&v, 1);

    //popBack(&v);

    //pushBack(&v, 41);

    //clear(&v);

    //printf("%d", isEmpty(&v));

    tests();


    return 0;
}
