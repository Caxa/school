#include <stdio.h>

#include "s21_string.h"

void processor(char* str, int n);

int main(int argc, char** argv) {
    int flag, n;
    char str[100];

    flag = 1;

    if (argc != 2 || (argv[1][0] != '-' || argv[1][1] != 'w')) {
        flag = 0;
    }
    if (flag == 1) {
        if (scanf("%d", &n) != 1 || n < 2) flag = 0;
        if (flag == 1) {
            scanf("%c", &str[0]);
            for (int i = 0; i < 100; i++) {
                scanf("%c", &str[i]);
                if (str[i] == '\n') {
                    str[i] = '\0';
                    break;
                }
            }
            if (flag == 1) {
                processor(str, n);
            }
        }
    }
    if (flag == 0) {
        printf("n/a");
    }
    return flag;
}

void processor(char* str, int n) {
    char* pip = s21_strtok(str, " ,.");
    int inlenght, inname, len, flag;
    char buffer[100] = "";
    inlenght = 0;
    inname = 0;
    flag = 1;
    while (pip != NULL) {
        len = s21_strlen(pip);
        if (inlenght + len < n) {
            if (flag == 1) {
                if (inlenght != 0) {
                    buffer[inlenght++] = ' ';
                    buffer[inlenght] = '\0';
                }
                s21_strcat(buffer, pip);
            } else {
                s21_strcpy(buffer, pip);
                flag = 1;
            }
            inlenght += len;
            flag = 1;
        } else {
            if (len < n) {
                if (flag == 1) printf("%s\n", buffer);
                s21_strcpy(buffer, pip);
                inlenght = len;
                flag = 1;
            } else {
                if (flag == 1 && inlenght != 0) buffer[inlenght++] = ' ';
                for (int i = inlenght; i < n - 1; i++) {
                    buffer[i] = pip[inname++];
                }
                buffer[n - 1] = '-';
                inlenght = 0;
                buffer[n] = '\0';
                printf("%s\n", buffer);
                flag = 0;
                for (int i = inname, j = 0; i < len; i++) {
                    pip[j++] = pip[i];
                }
                pip[len - inname] = '\0';
                inlenght = 0;
                inname = 0;
            }
        }
        if (flag == 1) {
            pip = s21_strtok(NULL, " ,.");
        }
    }
    printf("%s", buffer);
}