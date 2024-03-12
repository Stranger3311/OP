#ifndef MATRIX_LIB_H_INCLUDED
#define MATRIX_LIB_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void swap(int *a, int *b){

    int *temp = a;
    a = b;
    b = temp;

}

size_t getMaxElementIndexInArray(const int a[], size_t n) {

    int maxIndex = 0;

    for(size_t i = 1; i < n; i++){
        if(a[i] > a[maxIndex]){
        maxIndex = i;
        }
    }

    return maxIndex;
}


typedef struct matrix{
    int **values; // �������� �������
    int nRows; // ���������� �����
    int nCols; // ���������� ��������
}matrix;

typedef struct position{
    int rowIndex;
    int colIndex;
}position;

matrix getMemMatrix(int nRows, int nCols){
    int **values = (int **) malloc(sizeof(int*) * nRows);

    for (int i = 0; i < nRows; i++){
        values[i] = (int *) malloc(sizeof(int) * nCols);
    }

    return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols){

    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);

    for (int i = 0; i < nMatrices; i++){
        ms[i] = getMemMatrix(nRows, nCols);
    }

    return ms;
}

void freeMemMatrix(matrix *m){

    for (int i = 0; i < m->nCols; i++){
         for (int j = 0; j < m->nRows; j++){
            m->values[i][j] = NULL;
         }
    }
    m->values = NULL;
}

void freeMemMatrices(matrix *ms, int nMatrices){

    for (int q = 0; q < nMatrices; q++){
        freeMemMatrix(&ms[q]);
    }
}

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

/*
void inputMatrices(matrix *ms, int nMatrices){

    for (int i = 0; i <nMatrices; i++){
        for (int j = 0; j < ms->nCols; j++){
            for (int q = 0; q < ms->nRows; q++){
                scanf("%d", &ms[i]->values[j][q]);
            }
        }
    }

}*/

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

void swapRows(matrix m, int n1, int n2){

    int temp = m.values[n1];
    m.values[n1] = m.values[n2];
    m.values[n2] = temp;
}

void swapColumns(matrix m, int j1, int j2){

    for (int i = 0; i < m.nCols; i++){
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}

int getSum(int *a, int n){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += a[i];
    }

    return sum;
}

void insertionSortRowsMatrixByCriteria(matrix m, int (*criteria)(int*, int)){

    int *values = malloc(sizeof(int) * m.nRows);

    for (size_t i = 0; i < m.nRows; i++){
        values[i] = criteria(m.values[i], m.nCols);
    }

    for (size_t i = 1; i < m.nRows; i++){

        int j = i - 1;

        while (values[i] < values[j] && j >= 0) {
            values[j + 1] = values[j];
            swapRows(m, j + 1, j);
            --j;
        }

    values[j + 1] = values[i];
    }

}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)) {
    int *values = malloc(sizeof(int) * m.nCols);

    for (size_t i = 0; i < m.nCols; i++) {
        int *col = malloc( sizeof(int) * m.nRows);

    for (size_t j = 0; j < m.nRows; j++)
        col[j] = m.values[j][i];

        values[i] = criteria(col, m.nRows);
    }

    for (int i = m.nCols - 1; i > 0; --i) {

        int max = getMaxElementIndexInArray(values, i + 1);

        if (max != i) {
        swap(values + max, values + i);

        for (size_t j = 0; j < m.nRows; j++)
            swap(&m.values[j][max], &m.values[j][i]);
        }
    }
}

bool isSquareMatrix(matrix *m){

    return m->nCols == m->nRows;

}
/*
bool areTwoMatrixEqual(matrix *m1, matrix *m2){

    if (!(m1->nCols == m2->nCols && m1->nRows == m2->nRows)){
        return false;
    }

    for (int i = 0; i < m1->nCols; i++){
        for (int j = 0; j < m1->nRows; j++){
            if (m1->values[i][j] != m2->values[i][j]){
                return false;
            }
        }
    }

    return true;
}
*/

bool areTwoMatrixEqual(matrix *m1, matrix *m2){

    if (!(m1->nCols == m2->nCols && m1->nRows == m2->nRows)){
        return false;
    }

    for (int i = 0; i < m1->nCols; i++){
            if (memcmp(m1->values[i], m2->values[i], sizeof(int))){
                return false;
            }

    }

    return true;
}

bool isEMMatrix(matrix *m){

    for (int i = 0; i < m->nCols; i++){
        for (int j = 0; j < m->nRows; j++){
            if (i == j){
                if (m->values[i][j] != 1){
                    return false;
                }
            }else{
                if (m->values[i][j] != 0){
                    return false;
                }
            }
        }
    }

    return true;
}

bool isSymmetricMatrix(matrix *m){

    for (int i = 0; i < m->nCols; i++){
        for (int j = 0; j < m->nRows; j++){
            if (m->values[i][j] != m->values[j][i]){
                return false;
            }
        }
    }
    return true;
}



#endif // MATRIX_LIB_H_INCLUDED
