#ifndef MATRIX_LIB_H_INCLUDED
#define MATRIX_LIB_H_INCLUDED

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
        inputMatrix(ms->values[i]);
    }

}


#endif // MATRIX_LIB_H_INCLUDED