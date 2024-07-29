#include <stdio.h>

#define MAX_LEN 100

void sum(char *num1, char *num2, char *result);
void subtract(char *num1, char *num2, char *result);
int isValidInput(char *input);
void cleanInput(char *input);
void output(char *result);
int input(char *num);

int main() {
    char num1[MAX_LEN] = "";
    char num2[MAX_LEN] = "";
    char resultSum[MAX_LEN + 1];   // +1 для символа конца строки
    char resultDiff[MAX_LEN + 1];  // +1 для символа конца строки

    // Ввод чисел
    if (!input(num1) || !input(num2)) {
        printf("n/a\n");
        return 0;
    }

    // Очистка ввода от пробелов
    cleanInput(num1);
    cleanInput(num2);

    // Сложение
    sum(num1, num2, resultSum);

    // Вывод результата сложения без ведущих нулей
    output(resultSum);

    // Вычитание
    subtract(num1, num2, resultDiff);

    // Вывод результата вычитания без ведущих нулей
    if (resultDiff[0] == 'n') {
        printf("n/a");  // Выводим n/a без пробела
    } else {
        output(resultDiff);
    }

    return 0;
}

int input(char *num) {
    scanf("%[^\n]", num);
    getchar();  // Считываем символ новой строки

    if (!isValidInput(num)) {
        return 0;
    }

    return 1;
}

// Функция для сложения длинных чисел
void sum(char *num1, char *num2, char *result) {
    int carry = 0;
    int i = 0;

    int len1 = 0, len2 = 0;
    while (num1[len1] != '\0') len1++;
    while (num2[len2] != '\0') len2++;

    while (len1 > 0 || len2 > 0 || carry) {
        int digit1 = (len1 > 0) ? num1[--len1] - '0' : 0;
        int digit2 = (len2 > 0) ? num2[--len2] - '0' : 0;
        int total = digit1 + digit2 + carry;
        result[i++] = (total % 10) + '0';
        carry = total / 10;
    }

    result[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }
}

// Функция для вычитания длинных чисел
void subtract(char *num1, char *num2, char *result) {
    int borrow = 0;
    int i = 0;

    int len1 = 0, len2 = 0;
    while (num1[len1] != '\0') len1++;
    while (num2[len2] != '\0') len2++;

    // Сравнение строк без strcmp
    if (len1 < len2) {
        result[0] = 'n';
        result[1] = '/';
        result[2] = 'a';
        result[3] = '\0';
        return;
    } else if (len1 == len2) {
        for (int k = 0; k < len1; k++) {
            if (num1[k] > num2[k]) {
                break;
            } else if (num1[k] < num2[k]) {
                result[0] = 'n';
                result[1] = '/';
                result[2] = 'a';
                result[3] = '\0';
                return;
            }
        }
    }

    while (len1 > 0) {
        int digit1 = (len1 > 0) ? num1[--len1] - '0' : 0;
        int digit2 = (len2 > 0) ? num2[--len2] - '0' : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i++] = diff + '0';
    }

    result[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }
}

// Функция для проверки корректности ввода
int isValidInput(char *input) {
    int hasDigit = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if ((input[i] < '0' || input[i] > '9') && input[i] != ' ' && input[i] != '\n') {
            return 0;  // Некорректный символ найден
        }
        if (input[i] >= '0' && input[i] <= '9') {
            hasDigit = 1;
            if (i > 0 && input[i - 1] != ' ') {
                return 0;  // Цифра не отделена пробелом
            }
        }
    }
    return hasDigit;  // Должен быть хотя бы один символ и хотя бы одна цифра
}

// Функция для очистки входных данных от лишних символов
void cleanInput(char *input) {
    int i = 0;
    int j = 0;
    while (input[i] != '\0') {
        if (input[i] >= '0' && input[i] <= '9') {
            input[j++] = input[i];
        }
        i++;
    }
    input[j] = '\0';
}

void output(char *result) {
    int leadingZeros = 1;
    for (int i = 0; result[i] != '\0'; i++) {
        if (result[i] != '0') {
            leadingZeros = 0;
        }
        if (!leadingZeros) {
            printf("%c", result[i]);
            if (result[i + 1] != '\0') {
                printf(" ");
            }
        }
    }
    if (leadingZeros) {
        printf("0");  // Выводим хотя бы один ноль, если результат равен нулю
    }
    printf("\n");
}
