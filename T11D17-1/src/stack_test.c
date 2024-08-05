#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1

int test_push() {
    struct stack* s = init(2);
    if (!s) return FAIL;

    if (!push(s, 10)) return FAIL;
    if (!push(s, 20)) return FAIL;
    if (push(s, 30)) return FAIL;

    destroy(s);
    return SUCCESS;
}

int test_pop() {
    struct stack* s = init(2);
    if (!s) return FAIL;

    push(s, 10);
    push(s, 20);

    if (pop(s) != 20) return FAIL;
    if (pop(s) != 10) return FAIL;
    if (pop(s) != -1) return FAIL;

    destroy(s);
    return SUCCESS;
}

int main() {
    if (test_push() == SUCCESS) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }

    if (test_pop() == SUCCESS) {
        printf("\nSUCCESS");
    } else {
        printf("\nFAIL");
    }

    return 0;
}
