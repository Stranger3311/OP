#include "String_lib.h"

#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)


char *getEndOfString(char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;

    return end;
}

void removeNonLetters(char *s){
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

void removeAdjacentEqualLetters(char *s) {

    if (strlen_(s) == 0){
        return;
    }

    int i, j;

    for (i = 0, j = 0; s[i] != '\0'; i++) {
        if ( *(s + i) != *(s + (i + 1))){
            s[j] = *(s + i);
            j++;
        }
    }

    s[j] = '\0';
}

void test_removeAdjacentEqualLetters() {
    char str[] = "999000 888-888 667";
    char res[] = "90 8-8 67";
    removeAdjacentEqualLetters(str);

    ASSERT_STRING(res, str);

    char str1[] = "IDDQD";
    char res1[] = "IDQD";
    removeAdjacentEqualLetters(str1);

    ASSERT_STRING(res1, str1);

    char str2[] = "";
    char res2[] = "";
    removeAdjacentEqualLetters(str2);

    ASSERT_STRING(res2, str2);

    char str3[] = "OP Lab 18";
    char res3[] = "OP Lab 18";
    removeAdjacentEqualLetters(str3);

    ASSERT_STRING(res3, str3);
}

void removeExtraSpaces(char *s){

    if (strlen_(s) == 0){
        return;
    }

    int i, j;

    for (i = 0, j = 0; s[i] != '\0'; i++) {
        if ( (*(s + i) != ' ') || (i > 0 && (*(s + (i - 1)) != ' '))){
            s[j] = *(s + i);
            j++;
        }
    }

    s[j] = '\0';
}

void test_removeExtraSpaces(){
    char str[] = "90   88   67";
    char exp[] = "90 88 67";
    removeExtraSpaces(str);

    ASSERT_STRING(exp, str);

    char str1[] = "      ";
    char exp1[] = "";
    removeExtraSpaces(str1);

    ASSERT_STRING(exp1, str1);

    char str2[] = "ID DQ D";
    char exp2[] = "ID DQ D";
    removeExtraSpaces(str2);

    ASSERT_STRING(exp2, str2);
}

#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20
#define English_Alphabet 26

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

char _stringBuffer[MAX_STRING_SIZE + 1];

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitsToStart(char *s){

    char *beginSearch = s;
    WordDescriptor word;

    while (getWord(beginSearch, &word)){
        digitToStart(word);
        beginSearch = word.end;
    }
}

void test_digitsToStart() {
    char str[] = "9AbdSH7H6j";
    char res[] = "679AbdSHHj";
    digitsToStart(str);

    ASSERT_STRING(res, str);

    char str1[] = "";
    char res1[] = "";
    digitsToStart(str1);

    ASSERT_STRING(res1, str1);

}

void digitsToSpaces(char *s){

    copy(s, getEndOfString(s), _stringBuffer);

    char *recPtr = s;
    char *readPtr = _stringBuffer;

    for (int i = 0; i < strlen(_stringBuffer); i++){

        if (strlen(s) >= MAX_STRING_SIZE){
            fprintf(stderr, "Out of MAX_STRING_SIZE");
            return;(1);
        }

        if (!isdigit(_stringBuffer[i])){
            *recPtr = *readPtr;
            recPtr++;
            readPtr++;
        }else{
            int amount = _stringBuffer[i] - '0';
            for (int j = 0; j < amount; j++){
                *recPtr = ' ';
                recPtr++;
            }
            readPtr++;
        }
    }
    *(_stringBuffer + 0) = '\0';
    *recPtr = '\0';
}

void test_digitsToSpaces() {
    char str[MAX_STRING_SIZE] = "";
    char res[] = "";
    digitsToSpaces(str);

    ASSERT_STRING(res, str);

    char str1[MAX_STRING_SIZE] = "9Z8X6C";
    char exp1[] = "         Z        X      C";
    digitsToSpaces(str1);

    ASSERT_STRING(exp1, str1);

    char str2[MAX_STRING_SIZE] = "908867";
    char res2[] = "                                      ";
    digitsToSpaces(str2);

    ASSERT_STRING(res2, str2);

    char str3[MAX_STRING_SIZE] = "No numbers";
    char res3[] = "No numbers";
    digitsToSpaces(str3);

    ASSERT_STRING(res3, str3);
}

void replace(char *source, char *w1, char *w2) {


    size_t size_w1 = strlen(w1);
    size_t size_w2 = strlen(w2);
    WordDescriptor word1 = {w1, w1 + size_w1};
    WordDescriptor word2 = {w2, w2 + size_w2};
    char *readPtr, *recPtr;

    if (size_w1 >= size_w2){
        readPtr = source;
        recPtr = source;
    }else{
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }

    while (*readPtr != '\0'){
        if (memcmp(readPtr, w1, size_w1) == 0){
            for (int i = 0; i < size_w2; i++){
                *recPtr = w2[i];
                recPtr++;
            }
            readPtr += size_w1;

        }else{
            *recPtr = *readPtr;
            readPtr++;
            recPtr++;
        }
    }
    *recPtr = '\0';
}

void test_replace() {
    char str[MAX_STRING_SIZE] = "eee";
    char w1[] = "eee";
    char w2[] = "sun strike";
    replace(str, w1, w2);
    char exp[MAX_STRING_SIZE] = "sun strike";

    ASSERT_STRING(exp, str);

    char str1[MAX_STRING_SIZE] = "OP Labwork 18";
    char w1_1[] = "Labwork";
    char w2_1[] = "Lab";
    replace(str1, w1_1, w2_1);
    char exp1[MAX_STRING_SIZE] = "OP Lab 18";

    ASSERT_STRING(exp1, str1);

    char str3[MAX_STRING_SIZE] = "EEE";
    char w1_3[] = "EEE";
    char w2_3[] = "eee";
    replace(str3, w1_3, w2_3);
    char exp3[MAX_STRING_SIZE] = "eee";

    ASSERT_STRING(exp3, str3);
}

void tests(){
    test_removeAdjacentEqualLetters();
    test_removeExtraSpaces();
    test_digitsToStart();
    test_digitsToSpaces();
}

int main(){
    test_digitsToSpaces();
}
