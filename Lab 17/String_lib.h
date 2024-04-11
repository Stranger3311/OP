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

char* findNonSpaceReverse(char *rbegin, const char *rend){

    while (rbegin >= rend && isspace(*rbegin )){
        rbegin--;
    }
    return rbegin;
}

char* findSpaceReverse(char *rbegin, const char *rend){

    while(rbegin >= rend && !isspace(*(rbegin))){
        rbegin--;
    }
    return rbegin;
}

int strcmp(const char *lhs, const char *rhs){

    while (*lhs == *rhs && *lhs != '\0'){
        lhs++;
        rhs++;
    }
    return *lhs - *rhs;
}

char* copy(const char *beginSource, const char *endSource, char *beginDestination){

    while (beginSource != endSource) {
        *beginDestination = *beginSource;
        beginSource++;
        beginDestination++;
    }
    return beginDestination;
}



#endif // STRING_LIB_H_INCLUDED
