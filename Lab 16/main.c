#include <stdio.h>
#include <stdlib.h>
#include "Matrix_lib.h"
#include "Multi_arrays.h"
#include <assert.h>

void MinMaxRowsSwapTest(){

    matrix a = createMatrixFromArray((int[])
    {1, 2, 3,
     4, 5, 6,
     7, 8, 9},
     3, 3);

     matrix a_res = createMatrixFromArray((int[])
    {7, 8, 9,
     4, 5, 6,
     1, 2, 3},
     3, 3);

     MinMaxRowsSwap(&a);

     assert(areTwoMatrixEqual(&a, &a_res));
}

void sortColsMAxByIncreasingTest(){

    matrix a = createMatrixFromArray((int[])
    {7, 1, 2,
     1, 8, 1,
     3, 2, 3},
     3, 3);

     matrix a_res = createMatrixFromArray((int[])
    {3, 2, 3,
     7, 1, 2,
     1, 8, 1},
     3, 3);

     sortColsMAxByIncreasing(&a);

     assert(areTwoMatrixEqual(&a, &a_res));

}

void sortColsByMinElementsTest(){

    matrix a = createMatrixFromArray((int[])
    {3, 5, 2, 4, 3, 3,
    2, 5, 1, 8, 2, 7,
    6, 1, 4, 4, 8, 3},
     6, 3);

     matrix a_res = createMatrixFromArray((int[])
    {5, 2, 3, 3, 3, 4,
    5, 1, 2, 2, 7, 8,
    1, 4, 6, 8, 3, 4},
     6, 3);

     sortColsByMinElements(&a);

     assert(areTwoMatrixEqual(&a, &a_res));
}
/*
void tests(){


}*/

int main(){

    //3 5 2 4 3 3 2 5 1 8 2 7 6 1 4 4 8 3

    matrix a = getMemMatrix(6,3);

    inputMatrix(&a);

    sortColsByMinElements(&a);

    outputMatrix(a);

    //sortColsByMinElementsTest();

    return 0;
}
