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

void getSquareOfMatrixIfSymmetricTest(){

     matrix a = createMatrixFromArray((int[])
    {1, 4, 2,
    4, 3, 6,
    2, 6, 5},
     3, 3);

     matrix a_res = createMatrixFromArray((int[])
    {21, 28, 36,
    28, 61, 56,
    36, 56, 65},
     3, 3);

     getSquareOfMatrixIfSymmetric(&a);

     assert(areTwoMatrixEqual(&a, &a_res));

}

void transposeIfMatrixHasNotEqualSumOfRowsTest(){

     matrix a = createMatrixFromArray((int[])
    {18, 17, 12,
    8, 13, 6,
    2, 11, 10},
     3, 3);

     matrix a_res = createMatrixFromArray((int[])
    {18, 8, 2,
    17, 13, 11,
    12, 6, 10},
     3, 3);

     transposeIfMatrixHasNotEqualSumOfRows(a);

     assert(areTwoMatrixEqual(&a, &a_res));

}

void isMutuallyInverseMatricesTest(){

     matrix a = createMatrixFromArray((int[])
    {1, 2,
    3, 5},
     2, 2);

     matrix a_res = createMatrixFromArray((int[])
    {-5, 2,
    3, -1},
     2, 2);

     assert(isMutuallyInverseMatrices(a,a_res));

}
/*
void tests(){


}*/

int main(){

/*
    matrix a = getMemMatrix(2,2);

    inputMatrix(&a);

    matrix b = getMemMatrix(2,2);

    inputMatrix(&b);

    printf("%d",isMutuallyInverseMatrices(a,b));*/
    //sortColsByMinElements(&a);

    //outputMatrix(a);

isMutuallyInverseMatricesTest();
    return 0;
}
