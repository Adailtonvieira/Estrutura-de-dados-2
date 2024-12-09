#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//ordenacao
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void selectionSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
void mergeSort(int arr[], int left, int right);

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;
    }
}

//ordenacao
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortWrapper(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

//tempo de execucao
void measureSortingTime(const char *algorithm_name, void (*sortFunc)(int[], int), int arr[], int n) {
    int *test_arr = (int *)malloc(n * sizeof(int));
    copyArray(arr, test_arr, n);

    clock_t start = clock();
    sortFunc(test_arr, n);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("| %-15s | %12d | %15.2f ms |\n", algorithm_name, n, time_taken);

    free(test_arr);
}

int main() {
    srand(time(NULL));

    int start = 10, end = 1000000, step = 100000;

    printf("\nComparacao de desempenho dos algoritmos de ordenacao\n");
    printf("-------------------------------------------------------------\n");
    printf("| Algoritmo       | Tamanho Array | Tempo (ms)               |\n");
    printf("-------------------------------------------------------------\n");

    for (int n = start; n <= end; n += step) {
        int *arr = (int *)malloc(n * sizeof(int));
        generateRandomArray(arr, n);

        measureSortingTime("Bubble Sort", bubbleSort, arr, n);
        measureSortingTime("Insertion Sort", insertionSort, arr, n);
        measureSortingTime("Selection Sort", selectionSort, arr, n);
        measureSortingTime("Quick Sort", quickSortWrapper, arr, n);
        measureSortingTime("Merge Sort", mergeSortWrapper, arr, n);

        printf("-------------------------------------------------------------\n");
        free(arr);
    }

    printf("\nFim da execucao. Resultados exibidos em tabela.\n");
    return 0;
}
