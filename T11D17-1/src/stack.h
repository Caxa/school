#ifndef STACK_H
#define STACK_H

struct stack {
    int* data;
    int top;
    int capacity;
};

struct stack* init(int capacity);
int push(struct stack* s, int value);
int pop(struct stack* s);
void destroy(struct stack* s);

#endif  // STACK_H
