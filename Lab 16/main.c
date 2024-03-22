#include <stdio.h>
#include <stdlib.h>
#include "Matrix_lib.h"
#include "Multi_arrays.h"

int main(){

    matrix a = getMemMatrix(3,3);

    inputMatrix(&a);

    sortColsMAxByIncreasing(&a);

    outputMatrix(a);

    return 0;
}
