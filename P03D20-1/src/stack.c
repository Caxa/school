#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

stack* init() {
    stack* init_stack = malloc(sizeof(stack));
    init_stack->capacity = INIT_CAPACITY;
    init_stack->current_index = INIT_INDEX;
    init_stack->data = malloc(INIT_CAPACITY * sizeof(char));
    return init_stack;
}

void destroy(stack* stack) {
    free(stack->data);
    free(stack);
}

void change_capacity(stack* stack, int term) {
    stack->capacity += term;
    stack->data = realloc(stack->data, stack->capacity * sizeof(char));
}

stack* push(stack* stack, char elem) {
    stack->current_index += 1;
    if (stack->capacity <= stack->current_index) {
        change_capacity(stack, INCREMENT);
    }
    stack->data[stack->current_index] = elem;
    return stack;
}

char pop(stack* stack) {
    char result = stack->data[stack->current_index];
    stack->current_index -= 1;
    return result;
}

int is_empty(stack* stack) { return stack->current_index == -1; }

char last_elem(stack* stack) { return stack->data[stack->current_index]; }

stack_d* init_d() {
    stack_d* init_stack = malloc(sizeof(stack));
    init_stack->capacity = INIT_CAPACITY;
    init_stack->current_index = INIT_INDEX;
    init_stack->data = malloc(INIT_CAPACITY * sizeof(double));
    return init_stack;
}

void destroy_d(stack_d* stack) {
    free(stack->data);
    free(stack);
}

void change_capacity_d(stack_d* stack, int term) {
    stack->capacity += term;
    stack->data = realloc(stack->data, stack->capacity * sizeof(double));
}

stack_d* push_d(stack_d* stack, double elem) {
    stack->current_index += 1;
    if (stack->capacity <= stack->current_index) {
        change_capacity_d(stack, INCREMENT);
    }
    stack->data[stack->current_index] = elem;
    return stack;
}

double pop_d(stack_d* stack) {
    double result = stack->data[stack->current_index];
    stack->current_index -= 1;
    return result;
}

double last_elem_d(stack_d* stack) { return stack->data[stack->current_index]; }