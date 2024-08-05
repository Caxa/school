#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H

#include "stack.h"

int get_sign_priority(char sign);
int is_sign(char n);
int is_digit(char n);
void push_to_bracket(stack* source, stack* dest);
void process_sign(stack* signs_stack, stack* output_stack, char current_symbol);
void process_char(char* input, stack* output_stack, int* i, char current_symbol);
stack* to_polish_notation(char* input);
void push_lower_prior(stack* source, stack* dest, char current_symbol);
void push_all(stack* source, stack* dest);

#endif