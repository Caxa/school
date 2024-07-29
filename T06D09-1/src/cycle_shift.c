#include <stdio.h>
#define NMAX 10

void output(int *a, int n);
int input(int *a, int *n, int *c);
int positiv_move(int *a, int n, int c, int *res);
int negativ_move(int *a, int n, int c, int *res);
int main() {
    int n, data[NMAX], c, data1[NMAX];
    if (input(data, &n, &c) == 1 || getchar() != '\n') {
        printf("n/a");
    } else {
        if (c >= 0) {
            output(data1, positiv_move(data, n, c, data1));
        } else
            output(data1, negativ_move(data, n, c, data1));
    }
}

int input(int *a, int *n, int *c) {
    if (scanf("%d", n) == 1 && *n <= 10 && *n >= 1) {
        for (int *p = a; p - a < *n; p++) {
            if (scanf("%d", p) != 1) {
                return 1;
            }
        }
        if (scanf("%d", c) != 1) {
            return 1;
        }
        return 0;
    } else
        return 1;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i == (n - 1)) {
            printf("%d", a[i]);
        } else
            printf("%d ", a[i]);
    }
}

int positiv_move(int *a, int n, int c, int *res) {
    if (c > n) c = c % n;
    int *p = res;
    int A[NMAX], B[NMAX];
    for (int i = 0; i < c; i++) {
        A[(n - c - 1) + i] = a[i];
    }
    for (int i = c, j = 0; i < n; i++, j++) {
        B[j] = a[i];
    }
    for (int i = 0; i < n; i++) {
        if (i < (n - c)) {
            *p = B[i];
            p++;
        }
        if (i >= (n - c - 1)) {
            *p = A[i];
            p++;
        }
    }
    return n;
}

int negativ_move(int *a, int n, int c, int *res) {
    c = -c;
    if (c > n) c = c % n;
    int *p = res;
    int A[NMAX], B[NMAX];
    for (int i = 0; i < n - c; i++) {
        A[c + i] = a[i];
    }
    for (int i = n - c, j = 0; i < n; i++, j++) {
        B[j] = a[i];
    }
    for (int i = 0; i < n; i++) {
        if (i < c) {
            *p = B[i];
            p++;
        }
        if (i >= c) {
            *p = A[i];
            p++;
        }
    }
    return n;
}
