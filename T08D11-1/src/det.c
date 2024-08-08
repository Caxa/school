#include <stdio.h>
#include <stdlib.h>

int input(double*** MATRIX, int* n, int* m);
void output(double** MATRIX, int n, int m);
double** alloc(int* flag, int height, int w);
int inputMATRIX(double** MATRIX, int height, int w);
double determinant(double** MATRIX, int n);

int main() {
    double** MATRIX;
    int n, m;

    if (!input(&MATRIX, &n, &m) || getchar() != '\n') {
        printf("n/a");
        for (int i = 0; i < n; i++) {
            free(MATRIX[i]);
        }
        free(MATRIX);
        return 0;
    }
    printf("%0.6lf", determinant(MATRIX, n));

    for (int i = 0; i < n; i++) {
        free(MATRIX[i]);
    }
    free(MATRIX);
    return 0;
}

int inputMATRIX(double** MATRIX, int height, int w) {
    int flag = 1;
    for (int i = 0; i < height; i++) {
        if (flag == 0) break;
        for (int j = 0; j < w; j++) {
            if (!scanf("%lf", &MATRIX[i][j])) {
                flag = 0;
                break;
            }
        }
    }
    return flag;
}

double** alloc(int* flag, int height, int w) {
    double** MATRIX;
    MATRIX = (double**)malloc(height * sizeof(double*));
    if (!MATRIX) *flag = 0;
    if (*flag == 1) {
        for (int i = 0; i < height; i++) {
            MATRIX[i] = (double*)malloc(w * sizeof(double));
            if (!MATRIX[i]) *flag = 0;
        }
    }
    return MATRIX;
}

int input(double*** MATRIX, int* height, int* w) {
    int flag = 1;
    if (!scanf("%d", height) || (*height < 1)) flag = 0;
    if (!scanf("%d", w) || (*w < 1) || getchar() != '\n') flag = 0;
    if (*height != *w) {
        flag = 0;
    }
    if (flag == 1) {
        *MATRIX = alloc(&flag, *height, *w);
        if (flag == 1) {
            flag = inputMATRIX(*MATRIX, *height, *w);
        }
    }
    return flag;
}

void output(double** MATRIX, int height, int w) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < w; j++) {
            printf("%lf", MATRIX[i][j]);
            if (j != w - 1) printf(" ");
        }
        if (i != height - 1) printf("\n");
    }
}

double determinant(double** MATRIX, int n) {
    if (n == 1) {
        return MATRIX[0][0];
    }
    if (n == 2) {
        return MATRIX[0][0] * MATRIX[1][1] - MATRIX[0][1] * MATRIX[1][0];
    }

    double det = 0;
    double** subMATRIX = (double**)malloc((n - 1) * sizeof(double*));
    for (int i = 0; i < n - 1; i++) {
        subMATRIX[i] = (double*)malloc((n - 1) * sizeof(double));
    }

    for (int x = 0; x < n; x++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x) continue;
                subMATRIX[subi][subj] = MATRIX[i][j];
                subj++;
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * MATRIX[0][x] * determinant(subMATRIX, n - 1);
    }

    for (int i = 0; i < n - 1; i++) {
        free(subMATRIX[i]);
    }
    free(subMATRIX);
    return det;
}
