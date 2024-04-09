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

void testFindNonSpace(){
    char str[] = "findNonSpace test";
    char *nonSpace = findNonSpace(str);
    assert(*nonSpace == 'f');
}

void testFindSpace(){
    char str[] = "findSpace test";
    char *nonSpace = findSpace(str);
    assert(*nonSpace == ' ');
}

void testFindNonSpaceReverse(){

    char str[] = "findNonSpaceReverse test  ";
    char *rend = str - 1;
    char *rbegin = findNonSpaceReverse(str + 23, rend);
    assert(*rbegin == 't');

}

void testFindSpaceReverse(){

    char str[] = "findSpaceReverse test";
    char *rend = str - 1;
    char *rbegin = findSpaceReverse(str + 20,rend);
    assert(*rbegin == ' ');
}

int main(){

    testFindSpaceReverse();
    testFindNonSpaceReverse();
    return 0;
}
