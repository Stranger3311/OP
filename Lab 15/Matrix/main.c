#include <stdio.h>
#include "Matrix_lib.h"
/*
void inputMatrix(matrix *m){

    for (int i = 0; i < m->nCols; i++){
        for (int j = 0; j < m->nRows; j++){
            scanf("%d", &m->values[i][j]);
        }
    }
}

void inputMatrices(matrix *ms, int nMatrices){

    for (int i = 0; i < nMatrices; i++){
        inputMatrix(&ms[i]);
    }
}

void outputMatrix(matrix m){

    printf("{");
    for (int i = 0; i < m.nCols; i++){
        for (int j = 0; j < m.nRows; j++){
            printf("%d ", m.values[i][j]);
        }
        //printf("\n");
    }
    printf("}");
}

void outputMatrices(matrix *ms, int nMatrices){

    for (int i = 0; i < nMatrices; i++){
        outputMatrix(ms[i]);
    }

}
*/
int main(){

    matrix a = *getMemArrayOfMatrices(2,2,2);

    inputMatrices(&a,2);

    outputMatrices(&a,2);


    //freeMemMatrices(&a,2);

    //matrix a = getMemMatrix(2,2);

    //inputMatrix(&a);

    //swapRows(a,0,1);
    //swapColumns(a,0,1);

    //outputMatrix(a);

    //printf(" %d", isSquareMatrix(&a));

    //freeMemMatrix(&a);







    return 0;
}
