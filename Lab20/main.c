#include <stdio.h>
#include "Matrix_lib.h"
#include "Vector_bibl.h"
#include <assert.h>

void task_1(matrix *m, size_t queries, size_t *query[]){
    size_t row_1, col_1, row_2, col_2;
    for (size_t request = 0; request < queries; request++) {

        row_1 = query[request][0];
        col_1 = query[request][1];
        row_2 = query[request][2];
        col_2 = query[request][3];

        for (size_t row_i = row_1; row_i <= row_2; row_i++)
            for (size_t col_i = col_1; col_i <= col_2; col_i++)
                m->values[row_i][col_i]++;
    }
}

void test_t_1(){
    matrix m = createMatrixFromArray((int[]) {0,0,0,
                                             0,0,0,
                                             0,0,0},3,3);

    size_t queries = 2;

    size_t query_1[4] = {1, 1, 2, 2};
    size_t query_2[4] = {0, 0, 1, 1};

    size_t *query[2] = {query_1, query_2};

    task_1(&m, queries, query);

    matrix res = createMatrixFromArray((int[]) {1, 1, 0,
                                                  1, 2, 1,
                                                  0, 1, 1},
                                          3, 3);

    assert(areTwoMatrixEqual(&m, &res));
}

bool is_index_in_m(int rows, int cols, int row_i, int col_i) {
    if (row_i > -1 && row_i < rows && col_i > -1 && col_i < cols) {
        return true;
    } else {
        return false;
    }
}

size_t count_neighbors(matrix m, int row_i, int col_i, int rows, int cols) {
    size_t amount_neighbors = 0;
    for (int row_i_nbrs = row_i - 1; row_i_nbrs <= row_i + 1; row_i_nbrs++) {
        for (int col_i_nbrs = col_i - 1; col_i_nbrs <= col_i + 1; col_i_nbrs++) {
            if (is_index_in_m(rows, cols, row_i_nbrs, col_i_nbrs) && m.values[row_i_nbrs][col_i_nbrs] && (row_i != row_i_nbrs || col_i != col_i_nbrs)) {
                amount_neighbors++;
            }
        }
    }
    return amount_neighbors;
}

int cell_res_by_position(matrix m, int row_i, int col_i, size_t count_neighbors) {
    return ((m.values[row_i][col_i] == 1 && (count_neighbors == 2 || count_neighbors == 3)) || (m.values[row_i][col_i] == 0 && count_neighbors == 3));
}

void task_2(matrix m, matrix *res_m, int rows, int cols) {
    for (int row_i = 0; row_i < rows; row_i++) {
        for (int col_i = 0; col_i < cols; col_i++) {
            size_t amount_neighbors = count_neighbors(m, row_i, col_i, rows, cols);
            res_m->values[row_i][col_i] = cell_res_by_position(m, row_i, col_i, amount_neighbors);
        }
    }
}

void test_t_2() {
    int rows = 4;
    int cols = 3;
    matrix m = createMatrixFromArray((int[]) {0, 1, 0,
                                              0, 0, 1,
                                              1, 1, 1,
                                              0, 0, 0},
                                                   4, 3);

    matrix res_m = getMemMatrix(rows, cols);

    task_2(m, &res_m, rows, cols);

    matrix res = createMatrixFromArray((int[]) {0, 0, 0,
                                                  1, 0, 1,
                                                  0, 1, 1,
                                                  0, 1, 0},
                                          4, 3);
    assert(areTwoMatrixEqual(&res_m, &res));
}

int sorting_numbers_comp(const void *first_num, const void *second_num) {
    return (*(int *) first_num - *(int *) second_num);
}

void filling_Num_Sorted(int *a, matrix m, int row_i, int col_i) {
    int a_i = 0;
    for (size_t row_near_i = row_i - 1;row_near_i <= row_i + 1; row_near_i++) {
        for (size_t col_near_i = col_i - 1; col_near_i <= col_i + 1; col_near_i++) {
            if (row_near_i != col_i || col_near_i != col_i)
                a[a_i++] = m.values[row_near_i][col_near_i];
        }
    }

    qsort(a, 8, sizeof(int), sorting_numbers_comp);
}

void task_3(matrix *m, int window_size) {
    int m_sorted[8];
    for (int row_i = 1; row_i < window_size - 1; row_i++) {
        for (int col_i = 1; col_i < window_size - 1; col_i++) {
            filling_Num_Sorted(m_sorted, *m, row_i, col_i);
            int median_m = (m_sorted[3] + m_sorted[4]) / 2;
            m->values[row_i][col_i] = median_m;
        }
    }
}

void test_t_3() {
    int filter_window = 3;
    matrix m = createMatrixFromArray((int[]) {10, 20, 30,
                                              25, 35, 45,
                                              15, 25, 35},
                                           3, 3);

    task_3(&m, filter_window);

    matrix transformed_matrix = createMatrixFromArray((int[]) {10, 20, 30,
                                                                 25, 25, 45,
                                                                 15, 25, 35},
                                                              3, 3);

    assert(areTwoMatrixEqual(&m, &transformed_matrix));
}

void tests(){
    test_t_1();
    test_t_2();
    test_t_3();
}

int main() {
    test_t_3();
}
