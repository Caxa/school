#include "calculate.h"

#include <stdio.h>

int main() {
    char data[] = ",(,(,(,(1/>(12*22)))))";
    char* polish_notation = to_polish_notation(data)->data;
    printf("%s\n", polish_notation);
    double result = process_string(polish_notation);
    printf("%lf", result);
    return 0;
}