#ifndef STRING_LIB_H_INCLUDED
#define STRING_LIB_H_INCLUDED

#include <stdio.h>
#include <ctype.h>

size_t strlen_(const char* begin){

    char *end = begin;
    while (*end != '\0'){
        end++;
    }
    return end - begin;
}

char* find(char *begin, char *end, int ch){

    while (begin != end && *begin != ch){
        begin++;
    }
    return begin;
}

char* findNonSpace(char *begin){

    while (*begin != '\0' && isspace(*begin)){
        begin++;
    }
    return begin;
}

char* findSpace(char* begin){

    while(*begin != '\0' && !isspace(*begin)){
        begin++;
    }
    return begin;
}

#endif // STRING_LIB_H_INCLUDED
