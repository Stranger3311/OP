#include <stdio.h>
#include <assert.h>
#include "Matrix_lib.h"

void test_countZeroRows() {
    matrix m = createMatrixFromArray(
            (int[]) {
            1, 1, 0,
            0, 0, 0,
            0, 0, 1,
            0, 0, 0,
            0, 1, 1,
            },
            5, 3
            );

        assert(countZeroRows(m) == 2);
        freeMemMatrix(&m);
}

int countZeroRows(matrix m){

    int res = 0;

    for (int i = 0; i < m.nRows; i++){
            int zeros_amount = 0;
            for (int j = 0; j < m.nCols; j++){
                if (m.values[i][j] == 0){
                    zeros_amount++;
                }
                if(zeros_amount == m.nCols){
                    res++;
                }
            }
    }

    return res;
}

void test_getMemMatrix() {
    matrix m = getMemMatrix(2, 2);
    assert(m.nCols == 2 && m.nRows == 2);

    assert(m.values != NULL);
    freeMemMatrix(&m);


    m = getMemMatrix(2, 9);
    assert(m.nCols == 9 && m.nRows == 2);
    assert(m.values != NULL);


    freeMemMatrix(&m);
}

void test_getMemArrayOfMatrices() {
    matrix *ms = getMemArrayOfMatrices(2, 2, 2);

    assert(ms->nCols == 2 && ms->nRows == 2);

    assert(ms != NULL);
    freeMemMatrices(ms, 2);

    ms = getMemArrayOfMatrices(9, 5, 2);

    assert(ms->nCols == 2 && ms->nRows == 5);

    assert(ms != NULL);
    freeMemMatrices(ms, 2);
}

void test_freeMemMatrix() {

    matrix m = getMemMatrix(2, 2);
    freeMemMatrix(&m);
    assert(m.values == NULL);

    m = getMemMatrix(3, 6);
    freeMemMatrix(&m);
    assert(m.values == NULL);
}

void test_swapRows() {

    matrix m = createMatrixFromArray((int[])
    {4, 5,
    1, 2,
    7, 8,
        },
    3, 2);

    matrix exp_res = createMatrixFromArray((int[]) {
    1, 2,
    4, 5,
    7, 8
    },
    3, 2);
    swapRows(m, 0, 1);

    assert(areTwoMatrixEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_swapColumns() {

    matrix m = createMatrixFromArray((int[]) {
    4, 5,
    1, 2,
    3, 4},
    3, 2);

    matrix exp_res = createMatrixFromArray((int[]) {
    5, 4,
    2, 1,
    3, 4
     },
    3, 2);

    swapColumns(&m, 0, 1);

    assert(areTwoMatrixEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_insertionSortRowsMatrixByRowCriteria() {

    matrix m = createMatrixFromArray((int[]) {
    3, 3,
    1, 1,
    3, 1},
    3, 2);

    matrix exp_res = createMatrixFromArray((int[]) {
    1, 1,
    3, 1,
    3, 3},
    3, 2);

    insertionSortRowsMatrixByCriteria(m, getSum);

    assert(areTwoMatrixEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_selectionSortColsMatrixByColCriteria() {

    matrix m = createMatrixFromArray((int[]) {
    1, 3, 1,
    1, 3, 1,
    1, 3, 1},
    3, 3);

    matrix exp_res = createMatrixFromArray((int[]) {
    1, 1, 3,
    1, 1, 3,
    1, 1, 3},
    3, 3);

    selectionSortColsMatrixByColCriteria(&m, getSum);

    assert(areTwoMatrixEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_isSquareMatrix() {

    matrix m = getMemMatrix(4, 4);
    assert(isSquareMatrix(&m));
    freeMemMatrix(&m);


    m = getMemMatrix(5, 8);
    assert(!isSquareMatrix(&m));
    freeMemMatrix(&m);
}

void test_areTwoMatricesEqual() {
    matrix m = createMatrixFromArray((int[]) {
    5, 4,
    3, 2,
    1, 0},
    3, 2);

    matrix exp_res = createMatrixFromArray((int[]) {
    5, 4,
    3, 2,
    1, 0},
    3, 2);

    assert(areTwoMatrixEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);

    m = createMatrixFromArray((int[]) {
    1, 3,
    1, 1,
    3, 3,},
    3, 2);

    exp_res = createMatrixFromArray((int[]) {
    8, 6,
    4, 2,
    3, 3,},
    3, 2);

    assert(!areTwoMatrixEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_isEMatrix() {
    matrix m = createMatrixFromArray((int[]) {
    1, 0, 0,
    0, 1, 0,
    0, 0, 1},
    3, 3);
    assert(isEMMatrix(&m));

    matrix m_1 = createMatrixFromArray((int[]) {
    0, 1, 0,
    0, 1, 0,
    0, 1, 0},
    3, 3);
    assert(isEMMatrix(&m_1) == 0);
}

void test_isSymmetricMatrix() {
    matrix m = createMatrixFromArray((int[]) {
    1, 0, 0,
    0, 1, 0,
    0, 0, 1},
    3, 3);
    assert(isSymmetricMatrix(&m));

    matrix m_1 = createMatrixFromArray((int[]) {
    1, 0, 0,
    0, 1, 0,
    0, 1, 1},
    3, 3);
    assert(isSymmetricMatrix(&m_1) == 0);
}

void test_transposeSquareMatrix() {
    matrix m = createMatrixFromArray((int[]) {
    1, 2, 3,
    4, 5, 0,
    -1, 3, 4},
    3, 3);
    matrix exp_res = createMatrixFromArray((int[]) {
    1, 4, -1,
    2, 5, 3,
    3, 0, 4},
    3, 3);

    transposeSquareMatrix(&m);

    assert(areTwoMatrixEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_transposeMatrix() {
    matrix m = createMatrixFromArray((int[]) {
    1, 2, 3,
    4, 5, 6,
    7, 8, 9},
    3, 3);
    matrix exp_res = createMatrixFromArray((int[]) {
    1, 4, 7,
    2, 5, 8,
    3, 6, 9},
    3, 3);

    transposeMatrix(&m);

    assert(areTwoMatrixEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_getMinValuePos() {

    matrix m = createMatrixFromArray((int[]) {
    1, 6,
    3,18,
    7, 0},
    3, 2);
    position p = getMinValuePos(m);

    assert(p.rowIndex == 2 && p.colIndex == 0);
    freeMemMatrix(&m);
}

void test_getMaxValuePos() {

    matrix m = createMatrixFromArray((int[]) {
    11, 10, 10,
    4, 15, 12,
    7, 8, 10},
    3, 3);
    position p1 = getMaxValuePos(m);

    assert(p1.rowIndex == 1 && p1.colIndex == 1);
    freeMemMatrix(&m);
}


void test() {

test_getMemMatrix();
test_getMemArrayOfMatrices();
test_freeMemMatrix();

test_swapRows();
test_swapColumns();

test_insertionSortRowsMatrixByRowCriteria();
test_selectionSortColsMatrixByColCriteria();

test_countZeroRows();

test_isSquareMatrix();
test_areTwoMatricesEqual();
test_isEMatrix();
test_isSymmetricMatrix();

test_transposeSquareMatrix();
test_transposeMatrix();

test_getMinValuePos();
test_getMaxValuePos();
}


int main(){
/*
    matrix a = *getMemArrayOfMatrices(2,2,2);

    inputMatrices(&a,2);
/*
    outputMatrices(&a,2);
*/

    test();

    //freeMemMatrices(&a,2);
/*
    matrix a = getMemMatrix(3,2);
    matrix b = getMemMatrix(3,2);

    //position pos;

    inputMatrix(&a);
    transposeMatrix(&a);

 /*   printf("\n");

    inputMatrix(&b);

    printf("%d", areTwoMatrixEqual(&a, &b));
    //pos = getMinValuePos(a);
    //selectionSortColsMatrixByColCriteria(&a,getSum());
*/
    //transposeSquareMatrix(&a);
    //printf("%d %d", pos.colIndex, pos.rowIndex);

    //swapRows(a,0,1);
    //swapColumns(a,0,1);

    //outputMatrix(a);


    //freeMemMatrix(&a);

    return 0;
}
