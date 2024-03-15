#include <stdio.h>
#include <assert.h>
#include "Matrix_lib.h"

//Тесты функций
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

    for (int i = 0; i < m.nCols; i++){
            int zeros_amount = 0;
            for (int j = 0; j < m.nRows; j++){
                if (m.values[i][j] == 0){
                    zeros_amount++;
                }
                if(zeros_amount == m.nRows){
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
    // проверка на данные о колоннах и столбцах
    assert(ms->nCols == 2 && ms->nRows == 2);
    //проверка выделения памяти
    assert(ms != NULL);
    freeMemMatrices(ms, 2);

    ms = getMemArrayOfMatrices(9, 5, 2);
    // проверка на данные о колоннах и столбцах
    assert(ms->nCols == 2 && ms->nRows == 5);
    // проверка выделения памяти
    assert(ms != NULL);
    freeMemMatrices(ms, 2);
}

void test_freeMemMatrix() {
    // создаем и чистим массив
    matrix m = getMemMatrix(2, 2);
    freeMemMatrix(&m);
    assert(m.values == NULL);

    //проверка на других данных
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
    1, 3, 1,},
    2, 3);

    matrix exp_res = createMatrixFromArray((int[]) {
    1, 1, 3,
    1, 1, 3,},
    2, 3);

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
    2, 3);

    matrix exp_res = createMatrixFromArray((int[]) {
    5, 4, 3,
    2, 1, 0,},
    2, 3);

    assert(areTwoMatrixEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);

    m = createMatrixFromArray((int[]) {
    1, 3, 1,
    1, 3, 3,},
    2, 3);

    exp_res = createMatrixFromArray((int[]) {
    8, 6, 4,
    2, 3, 3,},
    2, 3);

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
    3,
    3);
    assert(isSymmetricMatrix(&m));

    matrix m_1 = createMatrixFromArray((int[]) {
    1, 0, 0,
    0, 1, 0},
    2, 3);
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
    4, 5, 6,},
    2, 3);
    matrix exp_res = createMatrixFromArray((int[]) {
    1, 4,2,
    5,3, 6,},
    3, 2);

    transposeMatrix(&m);

    assert(areTwoMatrixEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

void test_getMinValuePos() {

    matrix m = createMatrixFromArray((int[]) {
    -1, 6, 3,
    18, 7, 0,},
    2, 3);
    position p = getMinValuePos(m);

    assert(p.rowIndex == 1 && p.colIndex == 1);
    freeMemMatrix(&m);
}

void test_getMaxValuePos() {

    matrix m = createMatrixFromArray((int[]) {
    11, 10, 10,
    4, 15, 12,},
    2, 3);
    position p1 = getMaxValuePos(m);

    assert(p1.rowIndex == 2 && p1.colIndex == 2);
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
/*


void inOutTestMatrix(){

    matrix m0 = getMemMatrix(2,2);
    matrix m1 = getMemMatrix(3,2);

    inputMatrix(&m0);
    printf("\n");
    inputMatrix(&m1);

    outputMatrix(m0);
    printf("\n");
    outputMatrix(m1);

}

void inOutTestMatrices(){

    matrix m0 = *getMemArrayOfMatrices(2,2,2);
    matrix m1 = *getMemArrayOfMatrices(2,3,2);

    inputMatrices(&m0,2);
    printf("\n");
    inputMatrices(&m1,2);

    outputMatrices(&m0,2);
    printf("\n");
    outputMatrices(&m1,2);

}

void swapColumnsTest(){

    int a[6] = {1,2,3,4,5,6};
    int b[4] = {1,2,3,4};
    matrix m0 = createMatrixFromArray(&a,3,2);
    matrix m1 = createMatrixFromArray(&b,2,2);

    swapColumns(m0,0,1);
    swapColumns(m1,0,1);

    outputMatrix(m0);
    printf("\n");
    outputMatrix(m1);

}
/*
void test_countZeroRows(){
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
    assert(countZeroRows(m, 5, 3) == 2);
    freeMemMatrix(&m);
}
*/

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
    swapColumns(&a, 1, 2);
*/
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
