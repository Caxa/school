#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

char *my_strcpy(char *str1, char *str2);
int my_strcmp(char *str1, char *str2, int n);

void replace_math_function(char *str) {
    char temp[MAX_LEN];
    char *s = str;
    int j = 0;

    if (*s == '-') {
        temp[j++] = '~';
        s++;
    }
    while (*s != '\n' && *s != '\0') {
        if (my_strcmp(s, "sin", 3)) {
            temp[j++] = ',';
            s += 3;
        } else if (my_strcmp(s, "(-", 2)) {
            temp[j++] = '(';
            temp[j++] = '~';
            s += 2;
        } else if (my_strcmp(s, "cos", 3)) {
            temp[j++] = '?';
            s += 3;
        } else if (my_strcmp(s, "tan", 3)) {
            temp[j++] = '{';
            s += 3;
        } else if (my_strcmp(s, "ctg", 3)) {
            temp[j++] = '}';
            s += 3;
        } else if (my_strcmp(s, "sqrt", 4)) {
            temp[j++] = '<';
            s += 4;
        } else if (my_strcmp(s, "ln", 2)) {
            temp[j++] = '>';
            s += 2;
        } else {
            temp[j++] = *s;
            s++;
        }
    }
    temp[j] = '\0';
    my_strcpy(str, temp);
}

char *my_strcpy(char *str1, char *str2) {
    char *current = str1;
    while (*str2 != '\0') {
        *current++ = *str2++;
    }
    *current = '\0';
    return str1;
}

int my_strcmp(char *str1, char *str2, int n) {
    while (*str1 != '\0' && *str2 != '\0' && n > 0) {
        if (*str1 != *str2) return 0;
        str1++;
        str2++;
        n--;
    }
    return (n == 0 || *str2 == '\0') ? 1 : 0;
}

int check_valid_str(char *str) {
    const char valid_symbols[26] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '~', ' ',
                                    '+', '-', '*', '/', ',', '?', '{', '}', '<', '>', 'x', '(', ')'};
    int res_flag = 1;
    char *s = str;
    while (*s != '\0') {
        int valid = 0;
        for (int i = 0; i < 26 && valid != 1; i++) {
            if (*s == valid_symbols[i]) {
                valid = 1;
            }
        }
        if (valid != 1) res_flag = 0;
        s++;
    }
    if (*(s - 1) != ')' && !(*(s - 1) >= '0' && *(s - 1) <= '9') && *(s - 1) != 'x') res_flag = 0;
    return res_flag;
}

char *delete_spaces(char *in, char *out) {
    int j = 0;
    for (int i = 0; in[i]; i++) {
        if (in[i] != ' ') {
            out[j] = in[i];
            j += 1;
        }
    }
}

int main() {
    char str[256];
    char ch = ' ';
    int i = 0;
    while (ch != '\n') {
        ch = getchar();
        str[i] = ch;
        i += 1;
    }
    char out[256];
    delete_spaces(str, out);
    replace_math_function(out);
    int result = check_valid_str(out);
    printf("result: %d, str: %s", result, out);
}