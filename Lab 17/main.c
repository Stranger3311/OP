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
    char str1[] = "findSpaceReversetest";
    char *rend1 = str1 - 1;
    char *rbegin1 = findSpaceReverse(str1 + 19,rend1);
    assert(*rbegin1 == '\0');
}

void testStrcmp(){

    const char str1[] = "test strcmp";
    const char str2[] = "testStrcmp";
    assert(strcmp(str1,str2) < 0);

    const char str3[] = "test strcmp";
    assert(strcmp(str1,str3) == 0);
}

int main(){

    testStrcmp();
    return 0;
}
