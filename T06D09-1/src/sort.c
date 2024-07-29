#include <stdio.h>
#define NMAX 10

int input(int *a, int const *n);
void output(int *a, int n);
void sort(int *a, int n);

int main() {
    int n, data[NMAX];
    n = NMAX;
    if (input(data, &n) == 1 || getchar() != '\n') {
        printf("n/a");
        return 0;
    }
    sort(data, n);
    output(data, n);

    return 0;
}

int input(int *a, int const *n) {
    for (int *p = a; p - a < *n; p++) {
        if (scanf("%d", p) != 1) {
            return 1;
        }
    }
    return 0;
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
void sort(int *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (a[i] > a[j]) {
                int peremen = a[j];
                a[j] = a[i];
                a[i] = peremen;
            }
        }
    }
}
