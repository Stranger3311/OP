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
                row = row[i];
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

    swap(m->values[min_index], m->values[max_index]);

}

void sortColsMAxByIncreasing(matrix *m){

    int max = INT_MIN;
    int max_cur;
    //int max_index;

    int arrays_max[m->nCols];

    /*for (int i = 0; i < m->nCols; i++){
        min_cur = getMin(m->values[i], m->nRows);*/


            for (int j = 0; j < m->nCols; j++){

                max_cur = getMax(m->values[j], m->nRows);

                arrays_max[j] = max_cur;

                /*if (max_cur > max){
                    max = max_cur;
                    arrays_max[i] = j;
                }*/
            }

            for (int i = 0; i < m->nCols - 1; i++){
                for (int q = i + 1; q < m->nCols; q++){
                    if (arrays_max[i] < arrays_max[q]){
                        swap(arrays_max[i], arrays_max[q]);
                        swapRows(*m,i,q);
                    }
                }
            }

    //}


}

#endif // MULTI_ARRAYS_H_INCLUDED
