#include <stdio.h>
#include <assert.h>
#include "String_lib.h"

void testStrlen(){
    const char *str = "stren test";
    int size = strlen_(str);
    assert(size == 10);
}

void testFind(){
    char str[] = "find test";
    char *found = find(str, str + 9, 'e');
    assert(*found == 'e');
}

int main(){

    testFind();
    return 0;
}
