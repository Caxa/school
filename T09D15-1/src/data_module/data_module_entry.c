#include "data_process.h"

int main() {
    int n;
    printf("Enter the number of data points: ");
    scanf("%d", &n);

    double *data = (double*)malloc(n * sizeof(double));
    if (data == NULL) {
        printf("Memory allocation failed.");
        return 1;
    }

    input(data, n);

    if (normalization(data, n)) {
        output(data, n);
    } else {
        printf("ERROR: Division by zero.");
    }

    free(data);
    return 0;
}
