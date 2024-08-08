#include "s21_string.h"

#include <stdio.h>

void s21_strlen_test(const char *test_str);
void s21_strcmp_test(const char *str1, const char *str2);
void s21_strcpy_test(const char *source, char *destination);
void s21_strcat_test(char *destination, const char *source);
void s21_strchr_test(const char *str, char ch);
void s21_strstr_test(const char *haystack, const char *needle);
void s21_strtok_test(char *str, const char *delim);

int main() {
#ifdef Quest_1
    s21_strlen_test("School");
    s21_strlen_test("\0");
    s21_strlen_test("");
#endif
#ifdef Quest_2
    s21_strcmp_test("School", "Sshool");
    s21_strcmp_test("", "ABC");
    s21_strcmp_test("ABD", "ABD");
#endif
#ifdef Quest_3
    char str1[100] = "SCHOOL21";
    char str2[100] = "21";
    s21_strcpy_test(str2, str1);
    s21_strcpy_test(str1, str2);
    s21_strcpy_test("ABC", str1);
#endif
#ifdef Quest_4
    char str_cat[100] = "SCHOOL21";
    s21_strcat_test(str_cat, "SCHOOL");
    s21_strcat_test(str_cat, "ABC");
#endif
#ifdef Quest_5
    s21_strchr_test("School 21", 'o');
    s21_strchr_test("School 21", 'c');
    s21_strchr_test("School 21", 'D');
#endif
#ifdef Quest_6
    s21_strstr_test("School 21", "chool 21");
    s21_strstr_test("School 21", "42");
#endif
#ifdef Quest_7
    char str_tok[] = "Hello Worrrrrrld, hi people.";
    s21_strtok_test(str_tok, " ,.");
#endif
    return 0;
}

void s21_strlen_test(const char *test_str) {
    int expected_length = s21_strlen(test_str);
    printf("Input: \"%s\"\n", test_str ? test_str : "NULL");
    printf("Expected Output: %d\n", expected_length);
    printf("Test Result: %s", (expected_length == s21_strlen(test_str)) ? "SUCCESS " : "FAIL ");
}

void s21_strcmp_test(const char *str1, const char *str2) {
    printf("Input: \"%s\" and \"%s\"\n", str1, str2);
    printf("Test Result: %s", (s21_strcmp(str1, str2) < 0) ? "SUCCESS " : "FAIL ");
}

void s21_strcpy_test(const char *source, char *destination) {
    s21_strcpy(destination, source);
    printf("Source: \"%s\", Destination after copy: \"%s\"\n", source, destination);
    printf("Test Result: %s", (s21_strcmp(destination, source) == 0) ? "SUCCESS " : "FAIL ");
}

void s21_strcat_test(char *destination, const char *source) {
    s21_strcat(destination, source);
    printf("Destination after concatenation: \"%s\"\n", destination);
    printf("Test Result: %s", (s21_strcmp(destination, "SCHOOL2121") == 0) ? "SUCCESS " : "FAIL ");
}

void s21_strchr_test(const char *str, char ch) {
    char *p = s21_strchr(str, ch);
    printf("Input: \"%s\", Character: '%c'\n", str, ch);
    printf("Test Result: %s", (p != NULL && *p == ch) ? "SUCCESS " : "FAIL ");
}

void s21_strstr_test(const char *haystack, const char *needle) {
    char *pointer = s21_strstr(haystack, needle);
    printf("Haystack: \"%s\", Needle: \"%s\"\n", haystack, needle);
    printf("Test Result: %s", (pointer != NULL && s21_strcmp(pointer, needle) == 0) ? "SUCCESS " : "FAIL ");
}

void s21_strtok_test(char *str, const char *delim) {
    char *pch = s21_strtok(str, delim);
    int i = 0;
    while (pch != NULL) {
        printf("Token %d: \"%s\"\n", i + 1, pch);
        pch = s21_strtok(NULL, delim);
        i++;
    }
    printf("Test Result: SUCCESS ");
}
