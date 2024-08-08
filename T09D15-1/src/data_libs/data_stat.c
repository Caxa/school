#include "data_stat.h"

double max(double *data, int n) {
    double maximum = 0;
    for (int i = 0; i < n; i++) {
        if (maximum < data[i]) maximum = data[i];
    }
    return maximum;
}
double min(double *data, int n) {
    double mininmum = 0;
    for (int i = 0; i < n; i++) {
        if (mininmum > data[i]) mininmum = data[i];
    }
    return mininmum;
}
double mean(double *data, int n) {
    double mean_ = 0;
    for (int i = 0; i < n; i++) mean_ += data[i];
    return mean_ / n;
}
double variance(double *data, int n) {
    double mean_1 = mean(data, n), variance_1 = 0;
    for (int i = 0; i < n; i++) variance_1 += ((data[i] - mean_1) * (data[i] - mean_1));
    return variance_1 / n;
}

void sort(double *data, int n) {
    int tmp;
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (data[j] < data[j - 1]) {
                tmp = data[j - 1];
                data[j - 1] = data[j];
                data[j] = tmp;
            }
        }
    }
}
