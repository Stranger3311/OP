#include <stdio.h>
#include "Matrix_lib.h"



int main(){

    matrix a = *getMemArrayOfMatrices(2,2,2);

    inputMatrices(&a,2);

    //freeMemMatrices(&a,2);

    //matrix a = getMemMatrix(2,2);

    //inputMatrix(&a);







    return 0;
}