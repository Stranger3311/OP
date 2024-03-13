#include <stdio.h>
#include "Matrix_lib.h"
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

    //matrix a = *getMemArrayOfMatrices(2,2,2);

    //inputMatrices(&a,2);

    //outputMatrices(&a,2);




    //freeMemMatrices(&a,2);

    matrix a = getMemMatrix(2,2);
    matrix b = getMemMatrix(2,2);

    position pos;

    inputMatrix(&a);

    printf("\n");

    //inputMatrix(&b);

    //printf("%d", areTwoMatrixEqual(&a, &b));
    pos = getMinValuePos(a);
    //selectionSortColsMatrixByColCriteria(&a,getSum());

    //transposeSquareMatrix(&a);
    //printf("%d %d", pos.colIndex, pos.rowIndex);

    //swapRows(a,0,1);
    //swapColumns(a,0,1);

    outputMatrix(a);

    //printf("%d", isSymmetricMatrix(&a));

    //freeMemMatrix(&a);

    return 0;
}
