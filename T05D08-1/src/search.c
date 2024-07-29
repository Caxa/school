#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
void itog(int *data, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 1 || getchar() != '\n') {
        printf("n/a\n");
        return 0;
    }

    itog(data, n);

    return 0;
}

int input(int *a, int *n) {
    if ((scanf("%d", n) == 1) && (*n <= NMAX) && (*n >= 1)) {
        for (int i = 0; i < *n; i++) {
            if (scanf("%d", &a[i]) != 1) {
                return 1;
            }
        }
        return 0;
    } else {
        return 1;
    }
}

double mean(int *a, int n) {
    double res = 0;
    for (int i = 0; i < n; i++) {
        res += (double)a[i];
    }

    return res / n;
}

double variance(int *a, int n) {
    double mean_val = mean(a, n);
    double sum_sq_diff = 0;

    for (int i = 0; i < n; i++) {
        sum_sq_diff += (a[i] - mean_val) * (a[i] - mean_val);
    }

    return sum_sq_diff / n;
}

void itog(int *data, int n) {
    double mean_val = mean(data, n);
    double variance_val = variance(data, n);

    for (int i = 0; i < n; i++) {
        if ((data[i] % 2 == 0) && (data[i] >= mean_val) && (data[i] != 0) &&
            (data[i] >= mean_val - 3 * variance_val) && (data[i] <= mean_val + 3 * variance_val)) {
            printf("%d", data[i]);
            return;
        }
    }

    printf("0");
}
