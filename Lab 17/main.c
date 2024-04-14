#include <stdio.h>
#include <assert.h>
#include "String_lib.h"

void testStrlen(){
    const char *str = "strlen test";
    int size = strlen_(str);
    assert(size == 11);
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
    char *Space = findSpace(str);
    assert(*Space == ' ');
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
    assert(*rbegin1 == *(str1 - 1));
}

void testStrcmp(){

    const char str1[] = "test strcmp";
    const char str2[] = "testStrcmp";
    assert(strcmp(str1,str2) < 0);

    const char str3[] =	"test strcmp";

    assert(strcmp(str1,str3) == 0);
}

void testCopy(){

    const char str[] = "testCopy";
    char str_[8];

    copy(str, str + 8,(char*) str_);

    assert(*(str + 7) == *(str_ + 7) && *(str + 6) == *(str_ + 6) && *(str + 5) == *(str_ + 5) && *(str + 0) == *(str_ + 0));

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

void testCopyIfReverse(){

    const char str[] = "testCopy1If";
    const char str1[] = "1test2 3copy4";

    char str_[1];
    char str__[4];

    copyIfReverse(str + 11, str, (char*) str_, isNumber);
    assert(*(str_ + 0) == '1');

    copyIfReverse(str1 + 13, str1, (char*) str__, isNumber);
    assert(*(str__ + 0) == '4' && *(str__ + 1) == '3' && *(str__ + 2) == '2' &&  *(str__ + 3) == '1');
}

void tests(){
    testStrlen();
    testFind();
    testFindNonSpace();
    testFindSpace();
    testFindSpaceReverse();
    testFindNonSpaceReverse();
    testStrcmp();
    testCopy();
    testCopyIf();
    testCopyIfReverse();
}

int main(){

    tests();
    return 0;
}
