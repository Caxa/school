#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef DELAT_H
#define DELAT_H
#define GOLDEN_RATIO 0.666
#define EPS 1E-6

double max(double *data, int n);
double min(double *data, int n);
double mean(double *data, int n);
void input(double *data, int n);
void output(double *data, int n);
void normalization(double *data, int n);
void sort(double *data, int n);
int make_decision(double *data, int n);
double variance(double *data, int n);

#endif
