#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


int *copiarVetor(int *array, int size) {
    int *copia = (int*)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
        copia[i] = array[i];

    return copia;
}


void swap(int *array, int index_a, int index_b) {
    int temp = array[index_b];

    array[index_b] = array[index_a];
    array[index_a] = temp;
}


int mediana(int value_1, int value_2, int value_3) {
    if ((value_1 >= value_2 && value_1 <= value_3) || (value_1 <= value_2 && value_1 >= value_3))
        return value_1;
    else if ((value_2 >= value_1 && value_2 <= value_3) || (value_2 <= value_1 && value_2 >= value_3))
        return value_2;
    else
        return value_3;
}


void merge(int *array, int start, int mid, int end) {
    int size_1 = mid - start + 1;
    int size_2 = end - mid;
    int i, j;

    int *left = (int*)malloc(sizeof(int) * (size_1 + 1));
    int *right = (int*)malloc(sizeof(int) * (size_2 + 1));

    for (i = 0; i < size_1; i++)
        left[i] = array[start + i];

    for (i = 0; i < size_2; i++)
        right[i] = array[mid + i];

    left[size_1] = INT_MAX;
    right[size_2] = INT_MAX;

    i = j = 0;

    for (int k = start; k <= end; k++) {
        if (left[i] <= right[j])
            array[k] = left[i++];
        else
            array[k] = right[j++];
    }

    free(left);
    free(right);
}


void mergeSort(int *array, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;

        mergeSort(array, start, mid);
        mergeSort(array, mid + 1, end);
        merge(array, start, mid, end);
    }
}


void printArray(int *array, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}


int main() {
    int *array = (int*)malloc(sizeof(int) * 3);

    for (int i = 0; i < 3; i++)
        scanf("%d", &array[i]);

    mergeSort(array, 0, 2);

    printArray(array, 3);

    return 0;
}