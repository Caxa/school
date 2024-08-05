#include "data_input_output.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "point_struct.h"
#include "validation.h"

void display_graph(point *arr) {
    double step_y = 2.0 / (double)(HEIGHT - 1);

    for (int y = 0; y < HEIGHT; y++) {
        double current_y = (-1 + (y * step_y));
        for (int x = 0; x < WIDTH; x++) {
            if (fabs(arr[x].y - current_y) < step_y / 1.8)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}

void input(char *str) {
    char ch = ' ';
    for (int i = 0; ch != '\n'; i++) {
        str[i] = ch;
        ch = getchar();
    }
}