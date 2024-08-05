#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

struct stack* init(int capacity) {
    struct stack* s = (struct stack*)malloc(sizeof(struct stack));
    if (s) {
        s->capacity = capacity;
        s->top = -1;
        s->data = (int*)malloc(capacity * sizeof(int));
        if (!s->data) {
            free(s);
            return NULL;
        }
    }
    return s;
}

int push(struct stack* s, int value) {
    if (s->top >= s->capacity - 1) {
        return 0;
    }
    s->data[++s->top] = value;
    return 1;
}

int pop(struct stack* s) {
    if (s->top < 0) {
        return -1;
    }
    return s->data[s->top--];
}

void destroy(struct stack* s) {
    if (s) {
        free(s->data);
        free(s);
    }
}
