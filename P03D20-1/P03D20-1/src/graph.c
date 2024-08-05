#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    if (op == 's' || op == 'c' || op == 't' || op == 'g' || op == 'l' || op == 'n' || op == 'q') return 4;
    return 0;
}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

void infix_to_postfix(char* infix, char* postfix) {
    char stack[MAX_SIZE];
    int top = -1;
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (token == ' ') continue;
        if (is_digit(token) || token == '.') {
            postfix[j++] = token;
        } else if (token >= 'a' && token <= 'z') {
            postfix[j++] = token; // Function identifiers
        } else if (token == '(') {
            stack[++top] = token;
        } else if (token == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
                postfix[j++] = ' '; // Add space between operators
            }
            top--; // Remove '('
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(token)) {
                postfix[j++] = stack[top--];
                postfix[j++] = ' '; // Add space between operators
            }
            stack[++top] = token;
        }
    }

    while (top != -1) {
        postfix[j++] = stack[top--];
        postfix[j++] = ' '; // Add space between operators
    }

    postfix[j] = '\0';
}

double apply_operation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

double apply_function(double a, char func) {
    switch (func) {
        case 's': return sin(a);
        case 'c': return cos(a);
        case 't': return tan(a);
        case 'g': return 1 / tan(a); // cotangent
        case 'l': return log10(a); // log base 10
        case 'n': return log(a); // natural log
        case 'q': return sqrt(a); // square root
        default: return 0;
    }
}

void parser(char *infix) {
    for (int i = 0; infix[i] != '\0'; i++) {
        if (strncmp(&infix[i], "sin", 3) == 0) {
            infix[i] = 's'; infix[i + 1] = ' '; infix[i + 2] = ' '; i += 2;
        } else if (strncmp(&infix[i], "cos", 3) == 0) {
            infix[i] = 'c'; infix[i + 1] = ' '; infix[i + 2] = ' '; i += 2;
        } else if (strncmp(&infix[i], "tan", 3) == 0) {
            infix[i] = 't'; infix[i + 1] = ' '; infix[i + 2] = ' '; i += 2;
        } else if (strncmp(&infix[i], "cot", 3) == 0) {
            infix[i] = 'g'; infix[i + 1] = ' '; infix[i + 2] = ' '; i += 2;
        } else if (strncmp(&infix[i], "log", 3) == 0) {
            infix[i] = 'l'; infix[i + 1] = ' '; i += 2;
        } else if (strncmp(&infix[i], "ln", 2) == 0) {
            infix[i] = 'n'; infix[i + 1] = ' '; i += 1;
        } else if (strncmp(&infix[i], "sqrt", 4) == 0) {
            infix[i] = 'q'; infix[i + 1] = ' '; infix[i + 2] = ' '; infix[i + 3] = ' '; i += 3;
        }
    }
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Введите инфиксное выражение: ");
    fgets(infix, MAX_SIZE, stdin);
    parser(infix); // Call parser to handle function names
    infix_to_postfix(infix, postfix);

    // Remove trailing space from postfix
    size_t len = strlen(postfix);
    if (len > 0 && postfix[len - 1] == ' ') {
        postfix[len - 1] = '\0';
    }

    printf("Постфиксная нотация: %s\n", postfix);

    return 0;
}
