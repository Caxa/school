#include <stdio.h>
#include <stdlib.h>

int input(double*** matrix, int* n, int* m);
void output(double** matrix, int n, int m);
double** alloc(int* flag, int height, int width);
int inputMatrix(double** matrix, int height, int width);
void arrCreate(double** matrix, int height, int width, double** arr);
void inverseMatrix(double** matrix, int n);

int main() {
    double **matrix, *arr;
    int n, m;

    if (!input(&matrix, &n, &m) || getchar() != '\n') {
        printf("n/a");
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 0;
    }

    arrCreate(matrix, n, m, &arr);
    inverseMatrix(matrix, n);
    output(matrix, n, n);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(arr);
    return 0;
}

int inputMatrix(double** matrix, int height, int width) {
    int flag = 1;
    for (int i = 0; i < height; i++) {
        if (flag == 0) break;
        for (int j = 0; j < width; j++) {
            if (scanf("%lf", &matrix[i][j]) != 1) {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}

double** alloc(int* flag, int height, int width) {
    double** matrix;
    matrix = (double**)malloc(height * sizeof(double*));
    if (!matrix) *flag = 0;
    if (*flag == 1) {
        for (int i = 0; i < height; i++) {
            matrix[i] = (double*)malloc(width * sizeof(double));
            if (!matrix[i]) *flag = 0;
        }
    }
    return matrix;
}

int input(double*** matrix, int* height, int* width) {
    int flag = 1;
    if (scanf("%d", height) != 1 || (*height < 1)) flag = 0;
    if (scanf("%d", width) != 1 || (*width < 1) || getchar() != '\n') flag = 0;
    if (*height != *width) {
        flag = 0;
    }
    if (flag == 1) {
        *matrix = alloc(&flag, *height, *width);
        if (flag == 1) {
            flag = inputMatrix(*matrix, *height, *width);
        }
    }
    return flag;
}

void output(double** matrix, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%lf", matrix[i][j]);
            if (j != width - 1) printf(" ");
        }
        if (i != height - 1) printf("\n");
    }
}

void arrCreate(double** matrix, int height, int width, double** inArr) {
    int len = 0;
    double* arr = (double*)malloc(height * width * sizeof(double));
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) arr[len++] = matrix[i][j];
    // bubbleSort(arr, len); // bubbleSort function is missing
    *inArr = arr;
}

void inverseMatrix(double** matrix, int n) {
    double** augmentedMatrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        augmentedMatrix[i] = (double*)malloc(2 * n * sizeof(double));
        for (int j = 0; j < n; j++) {
            augmentedMatrix[i][j] = matrix[i][j];
            augmentedMatrix[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < n; i++) {
        double divisor = augmentedMatrix[i][i];
        for (int j = 0; j < 2 * n; j++) {
            augmentedMatrix[i][j] /= divisor;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = augmentedMatrix[k][i];
                for (int j = 0; j < 2 * n; j++) {
                    augmentedMatrix[k][j] -= factor * augmentedMatrix[i][j];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = augmentedMatrix[i][j + n];
        }
    }

    for (int i = 0; i < n; i++) {
        free(augmentedMatrix[i]);
    }
    free(augmentedMatrix);
}
