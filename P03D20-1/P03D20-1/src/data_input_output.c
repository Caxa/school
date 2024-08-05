#include "data_input_output.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "point_struct.h"

void display_graph(point *arr) {
    // Constants -----
    // double step_x = (4.0 * M_PI) / 80;
    double step_y = 2.0 / 24.0;
    // ---------------

    for (int y = 0; y < 25; y++) {  // Отрисовка 25 строк
        double current_y = (-1 + (y * step_y));
        for (int x = 0; x < 80; x++) {  // Каждая строка по 80 символов
            // Если не понимаете строку ниже - загуглите "Аппроксимация функции это"
            if (fabs(arr[x].y - current_y) < step_y / 1.8)  // Можно регулировать параметр
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}