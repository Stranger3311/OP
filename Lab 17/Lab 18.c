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
    char res[] = "90 88 67";
    removeExtraSpaces(str);

    ASSERT_STRING(res, str);

    char str1[] = "      ";
    char res1[] = "";
    removeExtraSpaces(str1);

    ASSERT_STRING(res1, str1);

    char str2[] = "ID DQ D";
    char res2[] = "ID DQ D";
    removeExtraSpaces(str2);

    ASSERT_STRING(res2, str2);
}

int getWord(char *beginSearch, WordDescriptor *word){
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
    char res1[] = "         Z        X      C";
    digitsToSpaces(str1);

    ASSERT_STRING(res1, str1);

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

void test_replace(){
    char str[MAX_STRING_SIZE] = "eee";
    char w1[] = "eee";
    char w2[] = "sun strike";
    replace(str, w1, w2);
    char res[MAX_STRING_SIZE] = "sun strike";

    ASSERT_STRING(res, str);

    char str1[MAX_STRING_SIZE] = "OP Labwork 18";
    char w1_1[] = "Labwork";
    char w2_1[] = "Lab";
    replace(str1, w1_1, w2_1);
    char res1[MAX_STRING_SIZE] = "OP Lab 18";

    ASSERT_STRING(res1, str1);

    char str3[MAX_STRING_SIZE] = "EEE";
    char w1_3[] = "EEE";
    char w2_3[] = "eee";
    replace(str3, w1_3, w2_3);
    char res3[MAX_STRING_SIZE] = "eee";

    ASSERT_STRING(res3, str3);
}

bool areWordsEqual(WordDescriptor w1, WordDescriptor w2){

    char *ptr1 = w1.begin;
    char *ptr2 = w2.begin;

    while (ptr1 <= w1.end && ptr2 <= w2.end) {
        if (*ptr1 != *ptr2){
            return 0;
        }

        ptr1++;
        ptr2++;
    }

    return ptr1 > w1.end && ptr2 > w2.end;

}

bool areWordsOrdered(char *s){

    WordDescriptor word1;
    WordDescriptor word2;

    if (getWord(s, &word1)){
        word2 = word1;
        while (getWord(s, &word1)){
            if (!areWordsEqual(word1, word2)){
                return false;
            }
            word2 = word1;
            s = word1.end;
        }

        return true;

    }else{
        return true;
    }
}

void test_areWordsOrdered(){
    char s[] = "abc";
    assert(areWordsOrdered(s) == true);

    char s2[] = "b a c";
    assert(areWordsOrdered(s2) == false);

    char s3[] = "a";
    assert(areWordsOrdered(s3) == true);

    char s4[] = " ";
    assert(areWordsOrdered(s4) == true);

}

void getBagOfWords(BagOfWords *bag, char *s){

    WordDescriptor word;
    bag->size = 0;

    while (getWord(s, &word)){
        bag->words[bag->size] = word;
        bag->size++;
        s = word.end;
    }
}

char *Copy_Reverse(char *rbeginSource, const char *rendSource, char *beginDestination){
    while (rbeginSource != rendSource)
        (*beginDestination++) = *rbeginSource--;

    return beginDestination;
}

void reverseWordsBag(char *s){

    *copy(s, getEndOfString(s), _stringBuffer) = '\0';

    getBagOfWords(&_bag, _stringBuffer);

    char *copy_str = s;

    for (int i = 0; i < _bag.size; i++){
        copy_str = Copy_Reverse(_bag.words[i].end - 1, _bag.words[i].begin - 1, copy_str);
        *copy_str++ = ' ';
    }
    if (copy_str != s){
        copy_str--;
    }

    *copy_str = '\0';
}

void test_reverseWordsBag(){

    char s[MAX_STRING_SIZE] = "qwerty";
    reverseWordsBag(s);

    ASSERT_STRING("ytrewq", s);

    char s2[MAX_STRING_SIZE] = "ABC";
    reverseWordsBag(s2);

    ASSERT_STRING("CBA", s2);

}


int isWordPalindrome(char *begin, char *end){

    while (begin < end){

        if (!isalpha(*begin)){
            begin++;
        }else if (!isalpha(*end)){
            end--;
        }else{

            if (tolower(*begin) != tolower(*end)) {
                return 0;
            }
            begin++;
            end--;
        }
    }

    return 1;
}

size_t WordsPalindromesAmount(char *s){

    char *end_str = getEndOfString(s);
    char *beginSearch = findNonSpace(s);

    int countPalindromes = 0;

    char *position_first_comma = find(beginSearch, end_str, ',');
    int last_comma = *position_first_comma == '\0' && end_str - beginSearch != 0;

    while (*position_first_comma != '\0' || last_comma){

        beginSearch = findNonSpace(beginSearch);
        countPalindromes += isWordPalindrome(beginSearch, position_first_comma);

        beginSearch = position_first_comma + 1;
        if (last_comma){
            break;
        }

        position_first_comma = find(beginSearch, end_str, ',');
        last_comma = *position_first_comma == '\0';
    }

    return countPalindromes;
}

void test_WordsPalindromesAmount(){
    char s[] = "";
    assert(WordsPalindromesAmount(s) == 0);

    char s1[] = "fbgjkfjffsejjsfkek";
    assert(WordsPalindromesAmount(s1) == 0);

    char s2[] = "o";
    assert(WordsPalindromesAmount(s2) == 1);

    char s3[] = "IDDI";
    assert(WordsPalindromesAmount(s3) == 1);

    char s4[] = "eve, qrttrq";
    assert(WordsPalindromesAmount(s4) == 2);

    char s5[] = "IDDI, zvqrt";
    assert(WordsPalindromesAmount(s5) == 1);

}

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w){
    if (s == NULL || strlen(s) == 0)
        return EMPTY_STRING;

    char *wordBegin = NULL;
    char *wordEnd = NULL;
    char *s_copy = strtok(s, " ");

    while (s_copy != NULL){
        bool found_a = false;
        for (int i = 0; s_copy[i] != '\0'; i++){
            if (tolower(s_copy[i]) == 'a'){
                found_a = true;
                break;
            }
        }

        if (found_a){

            if (wordBegin != NULL){
                w->begin = wordBegin;
                w->end = wordEnd;
                return WORD_FOUND;

            }else{
                return FIRST_WORD_WITH_A;
            }

        }else{
            wordBegin = s_copy;
            wordEnd = s_copy + strlen(s_copy);
        }

        s_copy = strtok(NULL, " ");
    }

    return NOT_FOUND_A_WORD_WITH_A;
}

void testAll_getWordBeforeFirstWordWithA(){
    WordDescriptor word;
    char s1[] = "";
    assert(getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING);
    char s2[] = "ABC";
    assert(getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A);
    char s3[] = "BC A";
    assert(getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND);

    char s4[] = "B Q WE YR OW IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

WordDescriptor lastWordInFirstStringFindInSecondString(char *s1, char *s2){

    BagOfWords bag1, bag2;
    getBagOfWords(&bag1, s1);
    getBagOfWords(&bag2, s2);

    for (int i = bag1.size - 1; i >= 0; i--){
        WordDescriptor word = bag1.words[i];
        for (int j = 0; j < bag2.size; j++){
            if (areWordsEqual(word, bag2.words[j])){
                return word;
            }
        }
    }

    WordDescriptor emptyWord = {"", ""};
    return emptyWord;
}

void wordDescriptorToString(WordDescriptor word, char *destination){

    char *wordPtr = word.begin;
    while (wordPtr != word.end){
        *destination++ = *wordPtr++;
    }
    *destination = '\0';
}

void test_lastWordInFirstStringInSecondString(){

    char s1[] = "wasd rtg iddqd iqqdq ";
    char s2[] = "wasd iddqd ";
    char s3[] = "iqqdq ";
    char s4[] = "eee ";

    char result[MAX_WORD_SIZE];
    WordDescriptor word;

    word = lastWordInFirstStringFindInSecondString(s1, s2);
    wordDescriptorToString(word, result);
    ASSERT_STRING("iddqd", result);

    word = lastWordInFirstStringFindInSecondString(s1, s3);
    wordDescriptorToString(word, result);
    ASSERT_STRING("iqqdq", result);

    word = lastWordInFirstStringFindInSecondString(s1, s4);
    wordDescriptorToString(word, result);
    ASSERT_STRING("", result);
}

bool isHasEqualWords(char *s) {

    BagOfWords bag;
    getBagOfWords(&bag, s);

    for (int i = 0; i < bag.size - 1; i++){
        for (int j = i + 1; j < bag.size; j++){
            if (areWordsEqual(bag.words[i], bag.words[j])){
                return true;
            }
        }
    }
    return false;
}

void test_isHasEqialWords(){

    char s1[] = "wasd rtg iddqd iqqdq ";
    char s2[] = "wasd iddqd wasd rtg";

    assert(isHasEqualWords(s1) == false);

    assert(isHasEqualWords(s2));
}

void wordToIntLetters(WordDescriptor *w, int res[]){

    int len = (w->end - w->begin);
    for (int i = 0; i < len; i++){
        int j = *(w->begin + i);
        res[j - 'a'] = 1;
    }
}

bool hasWordWithSameLetters(char *s){

    int word1_letters[27] = {0};
    int word2_letters[27] = {0};

    WordDescriptor word1, word2;
    word1.end = s;


    for (int i = 0; i < strlen(s); i++){
        getWord(word1.end, &word1);
        wordToIntLetters(&word1, &word1_letters);
        word2.end = word1.end;

        for (int j = i + 1; j < strlen(s); j++){
            getWord(word2.end, &word2);
            wordToIntLetters(&word2, &word2_letters);

            int amount = 0;
            for (int q = 0; q < 27; q++){
                if (word1_letters[q] == word2_letters[q]){
                    amount++;
                }
            }
            if (amount == 27){
                return  true;
            }
        }
    }
    return false;
}

void test_hasWordWithSameLetters(){

    char s1[] = "iddqd iqqdq wasd rtg ";
    char s2[] = "wasd iddqd rtg ";

    assert(hasWordWithSameLetters(s1) == true);

    assert(hasWordWithSameLetters(s2) == false);
}


void tests(){
    test_removeAdjacentEqualLetters();
    test_removeExtraSpaces();
    test_digitsToStart();
    test_digitsToSpaces();
    test_replace();
    test_areWordsOrdered();
    test_reverseWordsBag();
    test_WordsPalindromesAmount();
    testAll_getWordBeforeFirstWordWithA();
    test_lastWordInFirstStringInSecondString();
    test_isHasEqialWords();
    test_hasWordWithSameLetters();
}


int main(){

}
