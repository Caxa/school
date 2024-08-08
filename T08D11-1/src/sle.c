#include <stdio.h>
#include <stdlib.h>

double determinant(double** matrix, int n);
double* cramer(double** matrix, int n);
void solveSystem(double** matrix, int n);

int input(double*** matrix, int* n, int* m);
void output(double* solutions, int n);
double** alloc(int* flag, int height, int width);
int inputMatrix(double** matrix, int height, int width);
void arrCreate(double** matrix, int height, int width, double** arr);

int main() {
    double** matrix;
    int n, m;

    if (!input(&matrix, &n, &m) || getchar() != '\n') {
        printf("n/a");
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 0;
    }

    if (n + 1 != m) {
        printf("n/a");
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 0;
    }

    solveSystem(matrix, n);

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

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
    if (flag == 1) {
        *matrix = alloc(&flag, *height, *width);
        if (flag == 1) {
            flag = inputMatrix(*matrix, *height, *width);
        }
    }
    return flag;
}

void output(double* solutions, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lf", solutions[i]);
        if (i != n - 1) {
            printf(" ");
        }
    }
    // printf("\n");
}

void arrCreate(double** matrix, int height, int width, double** inArr) {
    int len = 0;
    double* arr = (double*)malloc(height * width * sizeof(double));
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) arr[len++] = matrix[i][j];
    *inArr = arr;
}

double determinant(double** matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    double det = 0;
    double** submatrix = (double**)malloc((n - 1) * sizeof(double*));
    for (int i = 0; i < n - 1; i++) {
        submatrix[i] = (double*)malloc((n - 1) * sizeof(double));
    }

    for (int x = 0; x < n; x++) {
        int subi = 0;  // индекс для submatrix
        for (int i = 1; i < n; i++) {
            int subj = 0;  // индекс для submatrix
            for (int j = 0; j < n; j++) {
                if (j == x) continue;  // пропускаем текущий столбец
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * matrix[0][x] * determinant(submatrix, n - 1);
    }

    for (int i = 0; i < n - 1; i++) {
        free(submatrix[i]);
    }
    free(submatrix);
    return det;
}

double* cramer(double** matrix, int n) {
    double det = determinant(matrix, n);
    if (det == 0) {
        printf("n/a");
        return NULL;
    }

    double* solutions = (double*)malloc(n * sizeof(double));
    double** tempMatrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        tempMatrix[i] = (double*)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                tempMatrix[k][j] = (j == i) ? matrix[k][n] : matrix[k][j];
            }
        }

        solutions[i] = determinant(tempMatrix, n) / det;
    }

    for (int i = 0; i < n; i++) {
        free(tempMatrix[i]);
    }
    free(tempMatrix);
    return solutions;
}

void solveSystem(double** matrix, int n) {
    double* solutions = cramer(matrix, n);
    if (solutions != NULL) {
        output(solutions, n);
        free(solutions);
    }
}
