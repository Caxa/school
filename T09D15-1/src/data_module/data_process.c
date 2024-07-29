#include "data_process.h"

double max(double *data, int n) {
    double max_val = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] > max_val) {
            max_val = data[i];
        }
    }
    return max_val;
}

double min(double *data, int n) {
    double min_val = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] < min_val) {
            min_val = data[i];
        }
    }
    return min_val;
}

int normalization(double *data, int n) {
    int result = 1;
    double max_value = max(data, n);
    double min_value = min(data, n);
    double size = max_value - min_value;

    if (fabs(size) > EPS) {
        for (int i = 0; i < n; i++) {
            data[i] = (data[i] - min_value) / size;
        }
    } else {
        result = 0;
    }

    return result;
}

void input(double *data, int n) {
    printf("Enter %d data points:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &data[i]);
    }
}

void output(double *data, int n) {
    printf("Normalized data:\n");
    for (int i = 0; i < n; i++) {
        printf("%lf ", data[i]);
    }
    printf("\n");
}
