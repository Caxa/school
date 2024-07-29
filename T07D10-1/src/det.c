#include <stdio.h>
#include <stdlib.h>


int input(int*** matrix, int* n, int* m);
void output(int** matrix, int n, int m);
int** alloc(int* flag, int height, int width);
int inputMatrix(int** matrix, int height, int width);
void swap(int* a, int* b);
int determinant(int** matrix,int n);

int main() {
    int** matrix, ** result, * arr;
    int n, m;

    if (!input(&matrix, &n, &m)) {
        printf("n/a");
        return 0;
    }
    printf("%d",determinant(matrix,n));
    
    
    
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(arr);
    return 0;
}

int inputMatrix(int** matrix, int height, int width) {
    int flag = 1;
    for (int i = 0; i < height; i++) {
        if (flag == 0) break;
        for (int j = 0; j < width; j++) {
            if (!scanf("%d", &matrix[i][j])) {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}

int** alloc(int* flag, int height, int width) {
    int** matrix;
    matrix = (int**)malloc(height * sizeof(int*));
    if (!matrix) *flag = 0;
    if (*flag == 1) {
        for (int i = 0; i < height; i++) {
            matrix[i] = (int*)malloc(width * sizeof(int));
            if (!matrix[i]) *flag = 0;
        }
    }
    return matrix;
}

int input(int*** matrix, int* height, int* width) {
    int flag = 1;
    if (!scanf("%d", height) || (*height < 1)) flag = 0;
    if (!scanf("%d", width) || (*width < 1)) flag = 0;
    if (height != width) {
            printf("n/a");
            flag = 0;
            return 1;
        }
    if (flag == 1) {
        *matrix = alloc(&flag, *height, *width);
        if (flag == 1) {
            flag = inputMatrix(*matrix, *height, *width);
        }
    }
    return flag;
}

void output(int** matrix, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d", matrix[i][j]);
            if (j != width - 1) printf(" ");
        }
        if (i != height - 1) printf("\n");
    }
}

int determinant(int** matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    int det = 0;
    int** submatrix = (int**)malloc((n - 1) * sizeof(int*));
    for (int i = 0; i < n - 1; i++) {
        submatrix[i] = (int*)malloc((n - 1) * sizeof(int));
    }

    for (int x = 0; x < n; x++) {
        int subi = 0; // индекс для submatrix
        for (int i = 1; i < n; i++) {
            int subj = 0; // индекс для submatrix
            for (int j = 0; j < n; j++) {
                if (j == x) continue; // пропускаем текущий столбец
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
