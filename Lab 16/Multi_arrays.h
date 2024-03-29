#ifndef MULTI_ARRAYS_H_INCLUDED
#define MULTI_ARRAYS_H_INCLUDED

#include <limits.h>
#include <stdbool.h>

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

bool isUnique(long long *a, int n){

    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (a[i] == a[j]){
                return false;
            }
        }
    }

    return true;
}

long long getSum(int *a, int n){
    long long sum = 0;
    for (int i = 0; i < n; i++){
        sum += a[i];
    }

    return sum;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m){

    long long int rowSums[m.nCols];

    for (int i = 0; i < m.nCols; i++){
        rowSums[i] = getSum(m.values[i], m.nRows);
    }

    if (isUnique(rowSums, m.nCols)){
        transposeSquareMatrix(&m);
    }
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2){

    matrix m_mul = getMemMatrix(m1.nRows, m1.nCols);
    m_mul = mulMatrices(m1,m2);

    for (int i = 0; i < m1.nCols; i++){
        if (m_mul.values[i][i] != 1){
            return false;
        }
    }

    return true;
}

int max (int a, int b){

    return a > b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m){

    long long max_num_sum = 0;
    int max_number = 0;

    for (int i = 1; i < m.nCols; i++) {

        int cur_row = 0;
        int cur_col = i;

        max_number = m.values[cur_row][cur_col];

        while (cur_col < m.nCols && cur_row < m.nRows) {
            max_number = max(max_number, m.values[cur_row][cur_col]);
            cur_row++;
            cur_col++;
        }
        max_num_sum += max_number;
    }

    for (int i = 1; i < m.nRows; i++) {

        int cur_row = i;
        int cur_col = 0;

        max_number = m.values[cur_row][cur_col];

        while (cur_col < m.nRows && cur_row < m.nRows) {
            max_number = max(max_number, m.values[cur_row][cur_col]);
            cur_row++;
            cur_col++;
        }
        max_num_sum += max_number;
    }

    return max_num_sum;

}

int getMinInArea(matrix m){

    position max_pos = getMaxValuePos(m);

    int min = m.values[max_pos.rowIndex][max_pos.colIndex];
    int row = max_pos.rowIndex - 1;
    int start_col;

    if(max_pos.colIndex - 1 >= 0){
        start_col = max_pos.colIndex - 1;
    }else{
        start_col = 0;
    }

    int col = start_col;
    int col_final;

    if(max_pos.colIndex + 1 <= m.nCols - 1){
        col_final = max_pos.colIndex + 1;
    }else{
        col_final = m.nCols - 1;
    }

    for (int i = row; i >= 0; i--){
        for (int j = col; j <= col_final; j++){
            min = min < m.values[i][j] ? min : m.values[i][j];
        }

        if(start_col - 1 >= 0){
            start_col = start_col - 1;
        }else{
            start_col = 0;
        }

        col = start_col;

        if(col_final + 1 <= m.nCols - 1){
            col_final = col_final + 1;
        }else{
            col_final = m.nCols - 1;
        }
    }

    return min;
}

float getDistance(int *a, int n) {

    float distance = 0;

    for (int i = 0; i < n; i++) {
        distance += a[i] * a[i];
    }

    distance = sqrt(distance);

    return distance;
}

void insertionSortRowsMatrixByRowCriteriaF(matrix *m, float (*criteria)(int *, int)){

    float temp[m->nRows];

    for (int i = 0; i < m->nRows; i++){

        temp[i] = criteria(m->values[i], m->nCols);
    }

    int min_pos;

    for (int j = 0; j < m->nRows; j++){

        min_pos = j;

        for (int i = j + 1; i < m->nRows; i++){
            if (temp[i] < temp[min_pos]){
                min_pos = i;
            }
        }
        if (min_pos != j){
            swap(&temp[j], &temp[min_pos]);
            swapRows(*m, j, min_pos);
        }
    }
}

void sortByDistances(matrix *m){
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

int cmp_long_long(const void *pa, const void *pb){

    if (*(long long int *) pa - *(long long int *) pb < 0)
        return -1;
    if (*(long long int *) pa - *(long long int *) pb > 0)
        return 1;
    return 0;
}

int countNUnique(long long *a, int n) {

    int amount = 0;
    int is_unique = 0;

    for (int i = 0; i < n - 1; i++){

        if (!is_unique && a[i] == a[i + 1]){
            amount += 1;
            is_unique = 1;

        }else{
            is_unique = 0;
        }
    }
    return amount;
}

int countEqClassesByRowsSum(matrix m) {

    long long sums[m.nRows];

    for (int i = 0; i < m.nRows; i++){
        sums[i] = getSum(m.values[i], m.nCols);
    }

    qsort(sums, m.nRows, sizeof(long long int), cmp_long_long);

    return countNUnique(sums, m.nRows);
}

int getNSpecialElement(matrix m){

    int sum;
    int max;
    int amount = 0;

    for (int i = 0; i < m.nCols; i++){
        max = m.values[0][i];
        sum = max;

        for (int j = 1; j < m.nRows; j++){

            if(max < m.values[j][i]){
                max = m.values[j][i];
            }

            sum += m.values[j][i];
        }

        sum -= max;

        if(sum < max){
            amount += 1;
        }
    }

    return amount;
}

position getLeftMin(matrix m){
    return getMinValuePos(m);
}

void swapPenultimateRow(matrix *m, int n){

    for (int i = m->nRows - 1; i >= 0; i--){
        m->values[m->nRows - 2][i] = m->values[i][n];
    }
}

bool isNonDescendingSorted(int *a, int n){

    for (int i = 0; i < n - 1; i++){
        if (a[i] > a[i + 1]){
            return false;
        }
    }

    return true;
}

bool hasAllNonDescendingRows(matrix m){

    for (int i = 0; i < m.nRows; i++){
        if (!isNonDescendingSorted(m.values[i], m.nCols)){
            return false;
        }
    }

    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix){

    int amount = 0;

    for (int i = 0; i < nMatrix; i++){
        if (hasAllNonDescendingRows(ms[i])){
            amount++;
        }
    }

    return amount;
}

int countValues(const int *a, int n, int value) {

    int amount = 0;
    for (size_t i = 0; i < n; i++){
        if (a[i] == value){
            amount++;
        }
    }

    return amount;
}

int countZeroRows(matrix m) {

    int result = 0;
    for (size_t i = 0; i < m.nRows; i++){
        int amount = countValues(m.values[i], m.nCols, 0);
        if (amount == m.nCols){
            result++;
        }
    }

    return result;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix){

    int arr_count[nMatrix];
    int max;
    int amount;

    for (int i = 0; i < nMatrix; i++){
        amount = countZeroRows(ms[i]);
        if (max < amount){
            max = amount;
        }
        arr_count[i] = amount;
    }
    for (int i = 0; i < nMatrix; ++i){
        if (arr_count[i] == max){
            outputMatrix(ms[i]);
        }
    }
}

void lowestNorm(matrix *ms, int nMatrix) {

    int temp[nMatrix];
    int abs;
    int max = 0;

    for (int i = 0; i < nMatrix; i++){
        for (int j = 0; j < ms->nRows; j++){
            for (int k = 0; k < ms->nCols; k++){

                abs = ms[i].values[j][k] > 0 ? ms[i].values[j][k] : -1 * ms[i].values[j][k];
                max = max < abs ? abs : max;
            }
        }

        temp[i] = max;
        max = 0;
    }

    int min = temp[0];

    for (int i = 1; i < nMatrix; i++){
        min = min > temp[i] ? temp[i] : min;
    }

    for (int i = 0; i < nMatrix; i++){
        if (temp[i] == min){
            outputMatrix(ms[i]);
        }
    }
}

#endif // MULTI_ARRAYS_H_INCLUDED
