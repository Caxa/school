#include "s21_string.h"
#include <stdio.h>
#include <stdlib.h>

int s21_strlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int s21_strcmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) return -1;
        if (str1[i] > str2[i]) return 1;
        i++;
    }
    return (str1[i] == '\0' && str2[i] == '\0') ? 0 : (str1[i] == '\0' ? -1 : 1);
}

void s21_strcpy(char* destination, const char* source) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

void s21_strcat(char* destination, const char* source) {
    int len = s21_strlen(destination);
    int i = 0;
    while (source[i] != '\0') {
        destination[len + i] = source[i];
        i++;
    }
    destination[len + i] = '\0';
}

char* s21_strchr(const char* source, int chCode) {
    while (*source) {
        if (*source == (char)chCode) {
            return (char*)source;
        }
        source++;
    }
    return NULL;
}

char* s21_strstr(const char* haystack, const char* need) {
    int i = 0, j;
    while (haystack[i] != '\0') {
        j = 0;
        while (need[j] != '\0' && haystack[i + j] == need[j]) {
            j++;
        }
        if (need[j] == '\0') {
            return (char*)&haystack[i];
        }
        i++;
    }
    return NULL;
}

int* create_delim_dict(const char* delim) {
    int* d = (int*)malloc(256 * sizeof(int)); // Allocate for all ASCII characters
    for (int i = 0; i < 256; i++) {
        d[i] = 0; // Initialize to 0
    }
    for (int i = 0; delim[i] != '\0'; i++) {
        d[(unsigned char)delim[i]] = 1; // Mark delimiters
    }
    return d;
}

char* s21_strtok(char* str, const char* delim) {
    static char* last;
    int* deliDict = create_delim_dict(delim);
    if (!deliDict) return NULL;

    if (str) {
        last = str;
    }

    while (deliDict[(unsigned char)*last] && *last != '\0') {
        last++;
    }

    if (*last == '\0') {
        free(deliDict);
        return NULL;
    }

    char* token_start = last;
    while (*last != '\0' && !deliDict[(unsigned char)*last]) {
        last++;
    }

    if (*last != '\0') {
        *last = '\0';
        last++;
    }

    free(deliDict);
    return token_start;
}
