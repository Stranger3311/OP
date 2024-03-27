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

void findSumOfMaxesOfPseudoDiagonalTest(){

     matrix a = createMatrixFromArray((int[])
    {3, 2, 5, 4,
    1, 3, 6, 3,
    3, 2, 1, 2},
     4, 3);

    int b =findSumOfMaxesOfPseudoDiagonal(a);

     assert(findSumOfMaxesOfPseudoDiagonal(a) == 20);

}

void getMinInAreaTest(){

    matrix m = createMatrixFromArray((int[]){
        6, 8, 9, 2,
        7, 12, 3, 4,
        10, 11, 5, 1}, 3, 4);

    assert(getMinInArea(m) == 6);
    freeMemMatrix(&m);
}

void sortByDistancesTest(){

    matrix m = createMatrixFromArray((int[]){
        10, -25,
        15, -15,
        -10, -45},
        3, 2);

    matrix m_res = createMatrixFromArray((int[]){
        15, -15,
        10, -25,
        -10, -45},
        3, 2);

    sortByDistances(&m);

    assert(areTwoMatrixEqual(&m, &m_res));

}

void countEqClassesByRowsSumTest(){

    matrix m = createMatrixFromArray((int[]) {7, 1,
                                              2, 7,
                                              5, 4,
                                              4, 3,
                                              1, 6,
                                              8, 0},
                                              6, 2);

    assert(countEqClassesByRowsSum(m) == 3);
    freeMemMatrix(&m);
}
/*
void tests(){


}*/

int main(){

/*
    matrix a = getMemMatrix(4,3);

    inputMatrix(&a);
    outputMatrix(a);

    /*matrix b = getMemMatrix(2,2);

    inputMatrix(&b);

    printf("%lld",findSumOfMaxesOfPseudoDiagonal(a));*/
    //sortColsByMinElements(&a);

    //outputMatrix(a);

    countEqClassesByRowsSumTest();
    return 0;
}
