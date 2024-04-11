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

void testCopy(){

    const char str[] = "testCopy";
    const char str1[] = "test copy";

    char str_[8];
    char str__[8];

    copy(str, str + 8,(char*) str_);

    assert(*(str + 7) == *(str_ + 7) && *(str + 6) == *(str_ + 6) && *(str + 5) == *(str_ + 5) && *(str + 0) == *(str_ + 0));

    copy(str1, str1 + 9,(char*) str__);

    assert(*(str1 + 7) == *(str__ + 7) && *(str1 + 6) == *(str__ + 6) && *(str1 + 5) == *(str__ + 5) && *(str1 + 0) == *(str__ + 0));

}

int isNumber(int a){
    return a <= '9' && a >= '0';
}

void testCopyIf(){

    const char str[] = "testCopy1If";
    const char str1[] = "1test2 3copy4";

    char str_[11];
    char str__[13];

    copyIf(str, str + 11, (char*) str_, isNumber);
    assert(*(str_ + 0) == '1');

    copyIf(str1, str + 13, (char*) str__, isNumber);
    assert(*(str__ + 0) == '1' && *(str__ + 1) == '2' && *(str__ + 2) == '3' &&  *(str__ + 3) == '4');
}

int main(){

    testCopyIf();
    return 0;
}
