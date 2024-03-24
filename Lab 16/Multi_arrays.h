#ifndef MULTI_ARRAYS_H_INCLUDED
#define MULTI_ARRAYS_H_INCLUDED

#include <limits.h>

int getMin(int *row, int n) {
    int min = row[0];
        for (int i = 1; i < n; i++) {
            if (row[i] < min) {
                min = row[i];
            }
        }

    return min;
}

int getMax(int *row, int n) {
    int max = row[0];
        for (int i = 1; i < n; i++) {
            if (row[i] > max) {
                max = row[i];
            }
        }

    return max;
}

void MinMaxRowsSwap(matrix *m){

    int min = INT_MAX;
    int min_cur;
    int min_index;

    int max = INT_MIN;
    int max_cur;
    int max_index;

    for (int i = 0; i < m->nCols; i++){

        min_cur = getMin(m->values[i], m->nRows);
        if (min_cur < min){
            min = min_cur;
            min_index = i;
        }
        max_cur = getMax(m->values[i], m->nRows);
        if (max_cur > max){
            max = max_cur;
            max_index = i;
        }

    }

    swapRows(*m,min_index, max_index);

}

void sortColsMAxByIncreasing(matrix *m){

    int max_cur;

    int arrays_max[m->nCols];

        for (int j = 0; j < m->nCols; j++){
            max_cur = getMax(m->values[j], m->nRows);
            arrays_max[j] = max_cur;
        }

        for (int i = 0; i < m->nCols - 1; i++){
            for (int q = i + 1; q < m->nCols; q++){
                if (arrays_max[i] > arrays_max[q]){
                    swap(&arrays_max[i], &arrays_max[q]);
                    swapRows(*m,i,q);
                }
            }
        }
}

void sortColsByMinElements(matrix *m){

    int arrays_min[m->nRows];
    int col[m->nCols];

    for (int i = 0; i < m->nRows; i++){
        for (int q = 0; q < m->nCols; q++){
            col[q] = m->values[q][i];
        }
        arrays_min[i]  = getMin(&col, m->nCols);

    }

    for (int i = 0; i < m->nRows - 1; i++){
            for (int q = i + 1; q < m->nRows; q++){
                if (arrays_min[i] > arrays_min[q]){
                    swap(&arrays_min[i], &arrays_min[q]);
                    swapColumns(m,i,q);
                }
            }
    }
}

matrix mulMatrices(matrix m1, matrix m2){

    matrix res = getMemMatrix(m1.nCols, m2.nRows);

    for (int i = 0; i < res.nCols; i++){
        for (int q = 0; q < res.nRows; q++){
            res.values[i][q] = 0;
        }
    }

    for (int i = 0; i < m1.nCols; i++){
        for (int q = 0; q < m2.nRows; q++){
            for (int k = 0; k < m1.nRows; k++){
                res.values[i][q] += m1.values[i][k] * m2.values[k][q];
            }
        }
    }

    return res;

}

void getSquareOfMatrixIfSymmetric(matrix *m){

    if (isSymmetricMatrix(m)){
        matrix m_sq = mulMatrices(*m,*m);
        freeMemMatrix(m);
        *m = m_sq;
    }

}

#endif // MULTI_ARRAYS_H_INCLUDED
