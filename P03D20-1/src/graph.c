#include <stdio.h>
#include <stdlib.h>

#include "calculate.h"
#include "data_input_output.h"
#include "point_struct.h"
#include "validation.h"

int main() {
    char string[1024];
    input(string);
    replace_math_function(string);
    int is_valid = check_valid_str(string);
    if (!is_valid)
        printf("n/a");
    else {
        stack* polish_notation_stack = to_polish_notation(string);
        point* points = create_points_array(polish_notation_stack->data);
        display_graph(points);
        destroy(polish_notation_stack);
        free(points);
    }
    return 0;
}