#include <stdio.h>
#define NMAX 10

int input(int *a);
void output(int *a);
void copy(int *a, int n, int *b);
void mergeSort(int *a, int l, int r);
void merge(int *arr, int l, int m, int r);
void heapify(int *arr, int n, int i);
void heapSort(int *arr, int n);

int main() {
    int data[NMAX], data1[NMAX];

    if (input(data) == 1 || getchar() != '\n') {
        printf("n/a");
        return 0;
    }

    copy(data, NMAX, data1);

    heapSort(data, NMAX);
    mergeSort(data1, 0, NMAX - 1);

    output(data);
    printf("\n");
    output(data1);

    return 0;
}

void copy(int *a, int n, int *b) {
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }
}

int input(int *a) {
    for (int i = 0; i < NMAX; i++) {
        if (scanf("%d", &a[i]) != 1) {
            return 1;
        }
    }
    return 0;
}

void output(int *a) {
    for (int i = 0; i < NMAX; i++) {
        if (i == NMAX - 1) {
            printf("%d", a[i]);
        } else {
            printf("%d ", a[i]);
        }
    }
}

void mergeSort(int *a, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void merge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void heapify(int *arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;

    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}
