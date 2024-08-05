#include "polish_notation.h"

/*
sin: ,
cos: ?
tan: {
ctg: }
sqrt: <
ln: >
unary -: ~
*/
int get_sign_priority(char sign) {
    int result;
    if (sign == '(' || sign == ')') {
        result = 0;
    } else if (sign == '+' || sign == '-') {
        result = 1;
    } else if (sign == '*' || sign == '/') {
        result = 2;
    } else if (sign == '^' || sign == ',' || sign == '?' || sign == '{' || sign == '}' || sign == '<' ||
               sign == '>') {
        result = 3;
    } else if (sign == '~') {
        result = 4;
    } else {
        result = -1;
    }
    return result;
}

int is_sign(char n) { return get_sign_priority(n) > -1; }

int is_digit(char n) { return n >= '0' && n <= '9'; }

void push_to_bracket(stack* source, stack* dest) {
    while (!is_empty(source) && last_elem(source) != '(') {
        push(dest, pop(source));
    }
    pop(source);
}

void process_sign(stack* signs_stack, stack* output_stack, char current_symbol) {
    if (current_symbol == ')')
        push_to_bracket(signs_stack, output_stack);
    else if (current_symbol == '(')
        push(signs_stack, current_symbol);
    else
        push_lower_prior(signs_stack, output_stack, current_symbol);
}

void push_lower_prior(stack* source, stack* dest, char current_symbol) {
    while (!is_empty(source) && get_sign_priority(current_symbol) <= get_sign_priority(last_elem(source))) {
        push(dest, pop(source));
    }
    push(source, current_symbol);
}

void push_all(stack* source, stack* dest) {
    while (!is_empty(source)) {
        push(dest, pop(source));
    }
}

void process_char(char* input, stack* output_stack, int* i, char current_symbol) {
    if (is_digit(current_symbol)) {
        for (; is_digit(input[*i]) || (input[*i] == '.'); *i += 1) {
            push(output_stack, input[*i]);
        }
        if (is_digit(input[*i + 1]) || is_sign(input[*i + 1])) push(output_stack, ' ');
        if (!is_digit(input[*i])) *i -= 1;
    } else {
        if (current_symbol != ' ') push(output_stack, current_symbol);
    }
}

stack* to_polish_notation(char* input) {
    stack* signs_stack = init();
    stack* output_stack = init();
    for (int i = 0; input[i]; i++) {
        char current_symbol = input[i];
        if (is_sign(current_symbol)) {
            process_sign(signs_stack, output_stack, current_symbol);
        } else {
            process_char(input, output_stack, &i, current_symbol);
        }
    }
    push_all(signs_stack, output_stack);
    destroy(signs_stack);
    return output_stack;
}