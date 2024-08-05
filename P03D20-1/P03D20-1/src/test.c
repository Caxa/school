
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

int is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_function(const char* token) {
    return (strcmp(token, "sin") == 0) || (strcmp(token, "cos") == 0) ||
           (strcmp(token, "tg") == 0) || (strcmp(token, "ctg") == 0) ||
           (strcmp(token, "ln") == 0) || (strcmp(token, "sqrt") == 0);
}

void handle_digit(char* infix, char* postfix, int* i, int* j) {
    while (is_digit(infix[*i]) || infix[*i] == '.') {
        postfix[(*j)++] = infix[(*i)++];
    }
    postfix[(*j)++] = ' ';
    (*i)--;
}

void handle_alpha(char* infix, char* postfix, int* j, int* i) {
    char token[10];
    int k = 0;
    while (is_alpha(infix[*i])) {
        token[k++] = infix[(*i)++];
    }
    token[k] = '\0';
    if (is_function(token)) {
        if (strcmp(token, "sin") == 0) {
            postfix[(*j)++] = 's'; // sin: ,
        } else if (strcmp(token, "cos") == 0) {
            postfix[(*j)++] = 'c'; // cos: ?
        } else if (strcmp(token, "tg") == 0) {
            postfix[(*j)++] = 't'; // tg: {
        } else if (strcmp(token, "ctg") == 0) {
            postfix[(*j)++] = 'g'; // ctg: }
        } else if (strcmp(token, "sqrt") == 0) {
            postfix[(*j)++] = 'r'; // sqrt: <
        } else if (strcmp(token, "ln") == 0) {
            postfix[(*j)++] = 'l'; // ln: >
        }
        postfix[(*j)++] = ' ';
    } else {
        postfix[(*j)++] = token[0];
        postfix[(*j)++] = ' ';
    }
    (*i)--;
}

void handle_parentheses(char* infix, char* postfix, char* stack, int* top, int* j, int* i) {
    if (infix[*i] == '(') {
        stack[++(*top)] = infix[*i];
    } else {
        while (*top != -1 && stack[*top] != '(') {
            postfix[(*j)++] = stack[(*top)--];
            postfix[(*j)++] = ' ';
        }
        (*top)--;
    }
}

void handle_operator(char* infix, char* postfix, char* stack, int* top, int* j, int* i) {
    while (*top != -1 && precedence(stack[*top]) >= precedence(infix[*i])) {
        postfix[(*j)++] = stack[(*top)--];
        postfix[(*j)++] = ' ';
    }
    stack[++(*top)] = infix[*i];
}

void infix_to_postfix(char* infix, char* postfix) {
    char stack[MAX_SIZE];
    int top = -1, i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (c == ' ') continue;

        if (is_digit(c) || c == '.') {
            handle_digit(infix, postfix, &i, &j);
        } else if (is_alpha(c)) {
            handle_alpha(infix, postfix, &j, &i); // Убраны параметры stack и top
        } else if (c == '(' || c == ')') {
            handle_parentheses(infix, postfix, stack, &top, &j, &i);
        } else {
            handle_operator(infix, postfix, stack, &top, &j, &i);
        }
    }

    while (top != -1) {
        postfix[j++] = stack[top--];
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
}

int check_parentheses(const char* expression) {
    int open_count = 0;
    int close_count = 0;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(') {
            open_count++;
        } else if (expression[i] == ')') {
            close_count++;
        }
    }

    return open_count != close_count;
}

int check_consecutive_operators(const char* expression) {
    for (int i = 0; expression[i] != '\0'; i++) {
        if ((expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') &&
            (expression[i] == expression[i + 1])) {
            return 1; // Найдено подряд идущие операторы
        }
    }
    return 0; // Нет подряд идущих операторов
}

int check_consecutive_functions(const char* expression) {
    for (int i = 0; expression[i] != '\0'; i++) {
        if (is_alpha(expression[i])) {
            char token[10];
            int k = 0;
            while (is_alpha(expression[i]) && k < 9) {
                token[k++] = expression[i++];
            }
            token[k] = '\0';

            if (is_function(token)) {
                // Проверяем следующий символ
                if (is_alpha(expression[i])) {
                    return 1; // Найдены подряд функции
                }
            }
            i--; // Возвращаемся на один символ назад
        }
    }
    return 0; // Нет подряд функций
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Введите инфиксное выражение: ");
    fgets(infix, MAX_SIZE, stdin);

    if (check_parentheses(infix)) {
        printf("Ошибка: количество открывающих и закрывающих скобок не равно.\n");
        return 1;
    }
    if (check_consecutive_operators(infix)) {
        printf("Ошибка: два подряд оператора.\n");
        return 1;
    }
    if (check_consecutive_functions(infix)) {
        printf("Ошибка: найдены подряд функции.\n");
        return 1;
    }

    infix_to_postfix(infix, postfix);
    printf("Постфиксная нотация: %s\n", postfix);

    return 0;
}

