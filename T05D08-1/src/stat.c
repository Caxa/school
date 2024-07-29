#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int const *a, int n);
int min(int const *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 1 || getchar() != '\n') {
        printf("n/a");
        return 0;
    }
    output(data, n);

    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 0;
}

int input(int *a, int *n) {
    if ((scanf("%d", n) == 1) && (*n <= NMAX) && (*n >= 1)) {
        for (int *p = a; p - a < *n; p++) {
            if (scanf("%d", p) != 1) {
                return 1;
            }
        }
        return 0;
    } else {
        return 1;
    }
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            printf("%d", a[i]);
        } else {
            printf("%d ", a[i]);
        }
    }
    printf("\n");
}
int max(int const *a, int n) {
    int max = -1000000;
    for (int p = 0; p < n; p++) {
        if (max < a[p]) {
            max = a[p];
        }
    }

    return max;
}
int min(int const *a, int n) {
    int min = 10093991;
    for (int p = 0; p < n; p++) {
        if (min > a[p]) {
            min = a[p];
        }
    }
    return min;
}
double mean(int *a, int n) {
    double res = 0;
    for (int p = 0; p < n; p++) {
        res += (double)a[p];
    }

    return (double)(res / n);
}
double variance(int *a, int n) {
    double mean_val = mean(a, n);
    double sum_sq_diff = 0;

    for (int p = 0; p < n; p++) {
        sum_sq_diff += (a[p] - mean_val) * (a[p] - mean_val);
    }

    return sum_sq_diff / n;
}
void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %0.6lf %0.6lf", max_v, min_v, mean_v, variance_v);
}
