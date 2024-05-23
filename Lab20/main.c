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

typedef struct domain {
    size_t visits_site;
    char name_site[1024];
} domain;

size_t find_domain_in_results(const domain *results, size_t size, char *s) {
    for (size_t index = 0; index < size; index++) {
        if (strcmp(results[index].name_site, s) == 0) {
            return index;
        }
    }
    return size;
}

bool find_number_in_arr(const size_t array[], size_t length, size_t num) {
    for (size_t index = 0; index < length; index++) {
        if (num == array[index])
            return true;
    }
    return false;
}
void dot_prt_not_null(domain *array, size_t index, char *dot_ptr, domain res[], size_t *size_res) {
    strcpy(array[index].name_site, dot_ptr + 1);
    size_t position = find_domain_in_results(res, *size_res, array[index].name_site);
    if (position == *size_res) {
        res[*size_res] = array[index];
        *size_res += 1;
    } else {
        res[position].visits_site += array[index].visits_site;
    }
}

void output_arrays_domains(domain *res, size_t size) {
    for (size_t index = 0; index < size; index++) {
        printf("%zd %s\n", res[index].visits_site, res[index].name_site);
    }
}

void task_4(domain a[], size_t size) {
    size_t close_index_size[size];
    size_t amount_close = 0;
    domain res[1024];
    size_t size_res = 0;
    for (size_t i = 0; i < size; i++) {
        res[size_res++] = a[i];
    }
    while (amount_close != size) {
        for (size_t index = 0; index < size; index++) {
            if (!find_number_in_arr(close_index_size, amount_close, index)) {
                char *dot_ptr;
                dot_ptr = strchr(a[index].name_site, '.');
                if (dot_ptr != NULL) {
                    dot_prt_not_null(a, index, dot_ptr, res, &size_res);
                }else {
                    close_index_size[amount_close++] = index;
                }
            }
        }
    }
    output_arrays_domains(res, size_res);
}

void test_t_4_1() {
    size_t size = 1;
    domain a[1] = {{9001, "discuss.codeforces.com"}};

    task_4(a, size);
}

void test_t_4_2() {
    size_t size = 4;
    domain a[4] = {{900, "google.mail.com"},
                     {50, "yahoo.com"},
                     {1, "intel.mail.com"},
                     {5, "wiki.org"}};
    task_4(a, size);
}

void test_t_4() {
    test_t_4_1();
    printf("\n");
    test_t_4_2();
}

void tests(){
    test_t_1();
    test_t_2();
    test_t_3();
    test_t_4();
}

int main() {
    test_t_4();
}
