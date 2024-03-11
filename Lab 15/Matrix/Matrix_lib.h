#ifndef MATRIX_LIB_H_INCLUDED
#define MATRIX_LIB_H_INCLUDED

typedef struct matrix{
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
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
        //inputMatrix(&ms->values[i]);
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

#endif // MATRIX_LIB_H_INCLUDED
