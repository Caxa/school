#ifndef STACK_H
#define STACK_H

#define INIT_CAPACITY 10
#define INIT_INDEX -1
#define INCREMENT 1

typedef struct {
    char* data;
    int capacity;
    int current_index;
} stack;

typedef struct {
    double* data;
    int capacity;
    int current_index;
} stack_d;

stack* init();
void destroy(stack* stack);
void change_capacity(stack* stack, int term);
stack* push(stack* stack, char elem);
char pop(stack* stack);
int is_empty(stack* stack);
char last_elem(stack* stack);

stack_d* init_d();
void destroy_d(stack_d* stack);
void change_capacity_d(stack_d* stack, int term);
stack_d* push_d(stack_d* stack, double elem);
double pop_d(stack_d* stack);
double last_elem_d(stack_d* stack);
#endif