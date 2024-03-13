#include <stdio.h>
#include "Matrix_lib.h"



int main(){

    //matrix a = *getMemArrayOfMatrices(2,2,2);

    //inputMatrices(&a,2);

    //outputMatrices(&a,2);




    //freeMemMatrices(&a,2);

    matrix a = getMemMatrix(3,2);
    matrix b = getMemMatrix(2,2);

    inputMatrix(&a);

    printf("\n");

    //inputMatrix(&b);

    //printf("%d", areTwoMatrixEqual(&a, &b));

    //selectionSortColsMatrixByColCriteria(&a,getSum());

    transposeMatrix(&a);

    //swapRows(a,0,1);
    //swapColumns(a,0,1);

    outputMatrix(a);

    //printf("%d", isSymmetricMatrix(&a));

    //freeMemMatrix(&a);







    return 0;
}
