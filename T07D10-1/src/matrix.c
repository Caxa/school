#include <stdio.h>
#include <stdlib.h>

void staticAllocation();
void dynamicAllocation2();
void dynamicAllocation1();
void dynamicAllocation3();
void outputMatrix(int **matrix, int rows, int cols);
int inputMatrix(int **matrix, int rows, int cols);

int main() {
    int choice;
    int flag = 0;
    do {
        if (scanf("%d", &choice)!=1){
            printf("n/a");
            return 0;
        }
        switch(choice) {
            case 1:
                staticAllocation();
                flag = 1;
                break;
            case 2:
                dynamicAllocation1();
                flag = 1;
                break;
            case 3:
                dynamicAllocation2();
                flag = 1;
                break;
            case 4:
                dynamicAllocation3();
                flag = 1;
                break;
            default:
                printf("n/a");
                flag = 1;
                break;
        }
    } while(choice != 0 && flag != 1);
    
    return 0;
}

int inputMatrix(int **matrix, int rows, int cols) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j])!=1){
                printf("n/a");
                return 1;
            }
        }
    }
    return 0;
}

void outputMatrix(int** array, int rowsNumber, int columnsNumber) {
    for (int i = 0; i < rowsNumber; ++i) {
        for (int j = 0; j < columnsNumber; j++) {
            if (j!=columnsNumber-1){
                printf("%d ", array[i][j]);
            }else{
                printf("%d", array[i][j]);
            }
        }
        
        printf("\n");
    }
    
}

void staticAllocation() {
    int matrix[100][100];
    int rows, cols;
    if(scanf("%d %d", &rows, &cols)!=2 || getchar() != '\n'){
        printf("n/a");
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &matrix[i][j])!=1){
                printf("n/a");
                return;
            }
        }
    }
    if(getchar() != '\n'){
        printf("n/a");
        return;
    }else{
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; j++) {
                if (j!=cols-1){
                    printf("%d ", matrix[i][j]);
                }else{
                    printf("%d", matrix[i][j]);
                }
            }
            
            printf("\n");
        }
    }
}

void dynamicAllocation1() {
    int **matrix;
    int rows, cols;
    
    
    if(scanf("%d %d", &rows, &cols)!=2 || getchar() != '\n'){
        printf("n/a");
        
    }
    matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    
    if(inputMatrix(matrix, rows, cols) == 1 || getchar() != '\n'){
        printf("n/a");
        return;
    }else {
        outputMatrix(matrix, rows, cols);
    }
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void dynamicAllocation2() {
    int **matrix;
    int rows, cols;

    if(scanf("%d %d", &rows, &cols)!=2 || getchar() != '\n'){
        printf("n/a");
            
    }
    matrix = (int **)malloc(rows * sizeof(int *));
    matrix[0] = (int *)malloc(rows * cols * sizeof(int));
    for (int i = 1; i < rows; i++) {
        matrix[i] = matrix[0] + i * cols;
    }
    if(inputMatrix(matrix, rows, cols) == 1 || getchar() != '\n'){
        printf("n/a");
        return;
    }else {
        outputMatrix(matrix, rows, cols);
    }
    free(matrix[0]);
    free(matrix);
}

void dynamicAllocation3() {
    int **matrix;
    int rows, cols;

    if(scanf("%d %d", &rows, &cols)!=2 || getchar() != '\n'){
        printf("n/a");
            
    }
    matrix = (int **)malloc(rows * sizeof(int *));
    int *data = (int *)malloc(rows * cols * sizeof(int));

    for (int i = 0; i < rows; i++) {
        matrix[i] = data + i * cols;
    }

    if(inputMatrix(matrix, rows, cols) == 1 || getchar() != '\n'){
        printf("n/a");
        return;
    }else {
        outputMatrix(matrix, rows, cols);
    }
    free(data);
    free(matrix);
}
