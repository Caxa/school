#include "calculate.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_input_output.h"

double exec_binary(char operator, double operand1, double operand2) {
    double result;
    switch (operator) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
        case '^':
            result = pow(operand1, operand2);
            break;
        default:
            result = 0;
            break;
    }
    return result;
}

double exec_unary(char operator, double operand) {
    double result;
    switch (operator) {
        case '~':
            result = -operand;
            break;
        case ',':
            result = sin(operand);
            break;
        case '?':
            result = cos(operand);
            break;
        case '{':
            result = tan(operand);
            break;
        case '}':
            result = 1.0 / tan(operand);
            break;
        case '<':
            result = sqrt(operand);
            break;
        case '>':
            result = log(operand);
            break;
        default:
            result = 0;
            break;
    }
    return result;
}

int is_unary(char operator) { return get_sign_priority(operator) >= 3 && operator!= '^'; }

void execute(char operator, stack_d * stack) {
    double result;
    if (is_unary(operator)) {
        double operand = pop_d(stack);
        result = exec_unary(operator, operand);
    } else {
        double operand2 = pop_d(stack);
        double operand1 = pop_d(stack);
        result = exec_binary(operator, operand1, operand2);
    }
    push_d(stack, result);
}

int move_to_next_obj(int* i, char* string) {
    int result = -1;
    for (; result == -1 && string[*i]; *i += 1) {
        if (string[*i] == ' ' || is_sign(string[*i]) || string[*i] == 'x' || !string[*i + 1]) result = *i;
    }
    *i -= 2;
    return result;
}

double extract_number(char* string, int start, int end) {
    char temp[512];
    strncpy(temp, &string[start], end - start);
    temp[end - start] = '\0';
    double result;
    sscanf(temp, "%lf", &result);
    return result;
}

void process_number(int* i, char* string, stack_d* stack) {
    int number_start = *i;
    int number_end = move_to_next_obj(i, string);
    if (number_end == -1) {
        number_end = strlen(string);
    }
    double parsed_number = extract_number(string, number_start, number_end);
    push_d(stack, parsed_number);
}

double process_string(char* string, double number) {
    stack_d* stack = init_d();
    for (int i = 0; string[i]; i++) {
        char current_symbol = string[i];
        if (is_digit(current_symbol)) {
            process_number(&i, string, stack);
        } else if (current_symbol == 'x') {
            push_d(stack, number);
        } else {
            if (current_symbol != ' ') execute(current_symbol, stack);
        }
    }
    double result = last_elem_d(stack);
    destroy_d(stack);
    return result;
}

point* create_points_array(char* function) {
    point* arr = malloc(WIDTH * sizeof(point));
    double step_x = (4.0 * M_PI) / (double)WIDTH;
    for (int i = 0; i < WIDTH; i++) {
        arr[i].x = i * step_x;
        arr[i].y = process_string(function, arr[i].x);
    }
    return arr;
}