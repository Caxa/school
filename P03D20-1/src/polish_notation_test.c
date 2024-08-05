#include "polish_notation.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    char *input = "~(12*22)-(~13+14)";
    stack *output_stack = to_polish_notation(input);
    printf("in: %s\n", input);
    printf("out: %s", output_stack->data);
    destroy(output_stack);
    return 0;
}