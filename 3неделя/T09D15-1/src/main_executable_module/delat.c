#include "delat.h"

// Пример реализации функции input
void input(double *data, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%lf", &data[i]);
    }
}

void output(double *data, int n) {
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            printf("%0.2lf", data[i]);
        } else {
            printf("%0.2lf ", data[i]);
        }
    }
}
double mean(double *data, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

// Пример реализации функции normalization
void normalization(double *data, int n) {
    double max = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    for (int i = 0; i < n; i++) {
        data[i] /= max;  // Нормализация
    }
}

// Пример реализации функции sort
void sort(double *data, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                double temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

// Пример реализации функции make_decision
int make_decision(double *data, int n) {
    int decision = 1;

    double m = mean(data, n);
    double sigma = sqrt(variance(data, n));
    double max_value = max(data, n);
    double min_value = min(data, n);

    decision = (min_value <= m + 3 * sigma) && (max_value >= m - 3 * sigma) && (m >= GOLDEN_RATIO);

    return decision;
}
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
double variance(double *data, int n) {
    double mean_val = mean(data, n);
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (data[i] - mean_val) * (data[i] - mean_val);
    }
    return sum / (n);
}