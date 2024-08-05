#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "data_input_output.h"
#include "point_struct.h"

void TEST_display_sin_x();

int main() {
    TEST_display_sin_x();
    return 0;
}

void TEST_display_sin_x() {
    // Init ---
    point *arr = malloc(WIDTH * sizeof(point));
    double step_x = (4.0 * M_PI) / 80;
    // --------

    // Fill ---
    for (int i = 0; i < 80; i++) {
        arr[i].x = (double)i * step_x;
        arr[i].y = sin(arr[i].x);
    }
    // --------

    // Output
    printf("-------------------\nТочки графика функций y = sin(x)\n| x      | y      |\n");
    for (int i = 0; i < 80; i++) {
        printf("|%8.5lf|%8.5lf|\n", arr[i].x, arr[i].y);
    }
    printf("-------------------\nГрафик функции y = sin(x)\n");
    // --------

    // Display
    display_graph(arr);
    // --------

    // Free ---
    free(arr);
    // --------
}