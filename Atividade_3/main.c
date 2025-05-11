#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


int *copiarArray(int *array, int size) {
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


int mediana(int *array, int index_1, int index_2, int index_3) {
    int value_1 = array[index_1];
    int value_2 = array[index_2];
    int value_3 = array[index_3];

    if ((value_1 >= value_2 && value_1 <= value_3) || (value_1 <= value_2 && value_1 >= value_3))
        return index_1;
    else if ((value_2 >= value_1 && value_2 <= value_3) || (value_2 <= value_1 && value_2 >= value_3))
        return index_2;
    else
        return index_3;
}


void merge(int *array, int start, int mid, int end, int *comparacoes) {
    int size_1 = (mid - start + 1);
    int size_2 = (end - mid);
    int i, j;

    int *left = (int*)malloc(sizeof(int) * (size_1 + 1));
    int *right = (int*)malloc(sizeof(int) * (size_2 + 1));

    for (i = 0; i < size_1; i++)
        left[i] = array[start + i];
    for (j = 0; j < size_2; j++)
        right[j] = array[mid + 1 + j];

    left[size_1] = INT_MAX;
    right[size_2] = INT_MAX;

    i = 0;
    j = 0;

    for (int k = start; k <= end; k++) {
        (*comparacoes)++;

        if (left[i] <= right[j])
            array[k] = left[i++];
        else
            array[k] = right[j++];
    }

    free(left);
    free(right);
}


void mergeSort(int *array, int start, int end, int *comparacoes) {
    if (start < end) {
        int mid = (start + end) / 2;

        mergeSort(array, start, mid, comparacoes);
        mergeSort(array, mid + 1, end, comparacoes);
        merge(array, start, mid, end, comparacoes);
    }
}


int particionar(int *array, int start, int end, int *comparacoes) {
    int mid = start + (end - start) / 2;

    int index_pivo = mediana(array, start, mid, end);
    swap(array, index_pivo, end);
    int pivo = array[end];

    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (array[j] < pivo) {
            i++;
            swap(array, i, j);
        }
        (*comparacoes)++;
    }

    swap(array, i + 1, end);

    return i + 1;
}


void quickSort(int *array, int start, int end, int *comparacoes) {
    if (start < end) {
        int pivo = particionar(array, start, end, comparacoes);

        quickSort(array, start, pivo - 1, comparacoes);
        quickSort(array, pivo + 1, end, comparacoes);
    }
}



void printArray(int *array, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}


int main() {
    int *array, size;
    int comparacoes = 0;

    scanf("%d", &size);
    
    array = (int*)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
        scanf("%d", &array[i]);

    int *array_copia = copiarArray(array, size);
    
    //mergeSort(array_copia, 0, (size - 1), &comparacoes);
    quickSort(array_copia, 0, (size - 1), &comparacoes);

    printArray(array_copia, size);
    printf("%d\n", comparacoes);

    free(array_copia);
    free(array);

    return 0;
}