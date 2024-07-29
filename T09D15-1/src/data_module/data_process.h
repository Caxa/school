#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef PROCESSING_H
#define PROCESSING_H

#define EPS 1E-6


double max(double *data, int n);
double min(double *data, int n);
double mean(double *data, int n);
double variance(double *data, int n);
void input(double *data, int n);
void output(double *data, int n);
int normalization(double *data, int n);


#endif




            
