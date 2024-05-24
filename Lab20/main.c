#include <stdio.h>
#include "Matrix_lib.h"
#include "Vector_bibl.h"
#include <assert.h>
#include <conio.h>

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

void find_res_matrix(matrix m, matrix *res_matrix, int rows, int cols) {
    for (size_t row_i = 0; row_i < rows; row_i++) {
        for (size_t col_i = 0; col_i < cols; col_i++) {
            if (m.values[row_i][col_i] == 1) {
                if (row_i != 0) {
                    res_matrix->values[row_i][col_i] = res_matrix->values[row_i - 1][col_i] + 1;
                } else {
                    res_matrix->values[row_i][col_i] = 1;
                }
            } else {
                res_matrix->values[row_i][col_i] = 0;
            }
        }
    }
}

void task_5(matrix m, int rows, int cols, size_t *res) {
    matrix res_matrix = getMemMatrix(rows, cols);
    find_res_matrix(m, &res_matrix, rows, cols);
    size_t mid_res = 0;

    for (size_t col_i = 0; col_i < cols; col_i++) {
        for (size_t row_i = 0; row_i < rows; row_i++) {
            for (size_t k_i = col_i + 1; k_i < cols + 1; k_i++) {
                int min = res_matrix.values[row_i][col_i];
                for (size_t col_k = col_i; col_k < k_i; col_k++) {
                    if (res_matrix.values[row_i][col_k] < min)
                        min = res_matrix.values[row_i][col_k];
                }
                mid_res += min;
            }
        }
    }
    *res = mid_res;
}

void test_t_5() {
    int rows = 3;
    int cols = 3;
    matrix m = createMatrixFromArray((int[]) {
                                               1, 0, 1,
                                               1, 1, 0,
                                               1, 1, 0},
                                       rows, cols);
    size_t amount = 0;

    task_5(m, rows, cols, &amount);

    assert(amount == 13);

}

void task_6(const char *str, size_t length, char *res, size_t *res_length) {
    char buff[10];
    size_t buff_len = 0;
    size_t mid_res_len = 0;
    char num = '1';

    for (size_t i = 0; i < length; i++) {
        buff[buff_len++] = num++;
        if (str[i] == 'I') {
            while (buff_len > 0) {
                res[mid_res_len++] = buff[--buff_len];
            }
        }
    }
    buff[buff_len++] = num;

    while (buff_len > 0) {
        res[mid_res_len++] = buff[--buff_len];
    }

    res[mid_res_len] = '\0';
    *res_length = mid_res_len;
}

void test_t_6_1() {
    char s[10] = "IIIDIDDD";
    size_t len = 8;
    char res[10];

    size_t res_length;

    task_6(s, len, res, &res_length);
    char answer[10] = "123549876";

    assert(strcmp(res, answer) == 0);
}

void test_t_6_2() {
    char s[5] = "DDD";
    size_t len = 3;
    char res[5];

    size_t res_length;

    task_6(s, len, res, &res_length);
    char answer[10] = "4321";

    assert(strcmp(res, answer) == 0);
}

void test_task_6() {
    test_t_6_1();
    test_t_6_2();
}

typedef struct tree_node {
    int value;
    struct tree_node* left;
    struct tree_node* right;
} tree_node;

tree_node* task_7(int *a, int left, int right) {
    if (left > right) {
        return NULL;
    }
    int max_pos = left;
    for (int i = left; i <= right; i++) {
        if (a[i] > a[max_pos]) max_pos = i;
    }

    tree_node* root = (tree_node*)malloc(sizeof(tree_node));
    root->value = a[max_pos];

    root->left = task_7(a, left, max_pos - 1);
    root->right = task_7(a, max_pos + 1, right);
    return root;
}

tree_node* task_7_start(int* numbers, int numbers_size) {
    return task_7(numbers, 0, numbers_size - 1);
}

void print_tree(tree_node* root) {
    if (root != NULL) {
        printf("%d ", root->value);

        print_tree(root->left);
        print_tree(root->right);
    } else {
        printf("null ");
    }
}

void test_task_7() {
    int a[6] = {3, 2, 1, 6, 0, 5};
    int len = 6;
    tree_node* res = task_7_start(a, len);
    print_tree(res);
}

void task_8(const char *s, size_t length, const size_t *positions, char *res_str) {
    for (size_t i = 0; i < length; i++) {
        res_str[i] = s[positions[i]];
    }
    res_str[length] = '\0';
}

void test_t_8_1() {
    char str[4] = "abc";
    size_t length_str = 3;
    size_t indices[3] = {0, 1, 2};
    char res_str[4];

    task_8(str, length_str, indices, res_str);

    char answer[4] = "abc";
    assert(strcmp(res_str, answer) == 0);
}

void test_t_8_2() {
    char str[5] = "abap";
    size_t length_str = 4;
    size_t indices[4] = {0, 3, 2, 1};
    char res_str[5];

    task_8(str, length_str, indices, res_str);

    char answer[5] = "apab";
    assert(strcmp(res_str, answer) == 0);
}

void test_t_8(){
    test_t_8_1();
    test_t_8_2();
}

void writing_to_file(int *a, size_t a_len, char *file_name) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (size_t index = 0; index < a_len; index++) {
        fprintf(file, "%d ", a[index]);
    }
    fclose(file);
}
void filter_files(vector *v, char *r_file_name, int N, char *w_file_name) {
    FILE *r_file = fopen(r_file_name, "r");
    if (r_file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    FILE *w_file = fopen(w_file_name, "w");
    if (w_file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int number;
    while (fscanf(r_file, "%d", &number) == 1) {
        if (number < N) {
            pushBack(v, number);
            fprintf(w_file, "%d ", number);
        }
    }

    fclose(r_file);
    fclose(w_file);
}

void task_9(int *a, size_t a_len, int N, char *first_file_name, char *second_file_name, vector *v) {

    writing_to_file(a, a_len, first_file_name);

    filter_files(v, first_file_name, N,second_file_name);
    shrinkToFit(v);
}

void test_t_9() {
    int a[9] = {6, 7, 15, 22, 9, 11, 44, 50, 65} ;
    size_t a_len = 9;
    int N = 20;

    char *first_file = "D:\\GitHub\\OP\\Lab20\\task_9_1.txt";
    char *second_file = "D:\\GitHub\\OP\\Lab20\\task_9_2.txt";

    vector v = createVector(10);
    task_9(a, a_len, N,first_file, second_file, &v);

    size_t answer_len = 5;
    assert(answer_len == v.size);
}

void opening_file_with_text(char *file_name, char *text) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }
    fprintf(file, "%s", text);
    fclose(file);
}

void task_10(char *file_name, size_t count_output_lines, char *text) {
    opening_file_with_text(file_name, text);

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    char line[128];
    size_t counter = 0;
    while (fgets(line, 128, file) != NULL) {
        printf("%s", line);
        counter++;
        if (counter == count_output_lines) {
            printf("Press Ctrl + C for showing\n");
            while (getch() != 3);
        }
    }
}
void test_t_10_1() {
    char *file_name = "D:\\GitHub\\OP\\Lab20\\task_10_1.txt";
    size_t count_output_lines = 3;
    char text[100] = "eWSAWD\nhmxgxg\nzsgkopc\n???";
    task_10(file_name, count_output_lines, text);
}

void test_t_10_2() {
    char *file_name = "D:\\GitHub\\OP\\Lab20\\task_10_2.txt";
    size_t count_output_lines = 4;
    char text[100] = "\nsfdsdf\n dasfdsa\n deasfdas\n";
    task_10(file_name, count_output_lines, text);
}

void test_t_10() {
    test_t_10_1();
    //test_t_10_2();
}

void tests(){
    test_t_1();
    test_t_2();
    test_t_3();
    test_t_4();
    test_t_5();
    test_task_6();
    test_task_7();
    test_t_8();
    test_t_9();
    test_t_10();
}

int main() {
    test_t_10();
}
