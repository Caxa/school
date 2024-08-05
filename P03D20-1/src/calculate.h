#ifndef CALCULATE_H
#define CALCULATE_H

#include "point_struct.h"
#include "polish_notation.h"

double exec_binary(char operator, double operand1, double operand2);
double exec_unary(char operator, double operand);
int is_unary(char operator);
void execute(char operator, stack_d * stack);
int get_next_space_index(int* i, char* string);
double extract_number(char* string, int start, int end);
double process_string(char* string, double number);
point* create_points_array(char* function);
#endif