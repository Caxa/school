#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int sum_numbers(int *a, int n);
int find_numbers(int *a, int n, int number, int *numbers);

int main() {
    int n, data[NMAX], data1[NMAX];

    if (input(data, &n) == 1 || getchar() != '\n') {
        printf("n/a");
        return 0;
    }

    int sum = sum_numbers(data, n);

    if (sum_numbers(data, n) == -1) {
        printf("n/a");
        return 0;
    }
    printf("%d\n", sum);
    int special_count = find_numbers(data, n, sum, data1);

    output(data1, special_count);

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

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            if (a[i] != 0) {
                printf("%d ", a[i]);
            }
        } else {
            if (a[i] != 0) {
                printf("%d", a[i]);
            }
        }
    }
    // printf("\n");
}

int sum_numbers(int *a, int n) {
    int sum = 0, count = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0 && a[i] != 0) {
            count++;
            sum = sum + a[i];
        }
    }
    if (count == 0) {
        sum = -1;
    }
    return sum;
}

int find_numbers(int *a, int n, int number, int *numbers) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            if (number % a[i] == 0) {
                numbers[count] = a[i];
                count++;
            }
        }
    }

    return count;
}
