/*
    Atividade: Algoritmos de Ordenação N * logN
    Data: 12/5/2025 - UNIFESP

    Algoritmos implementados:
    - MergeSort
    - QuickSort
    - QuickSort híbrido

*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


int *copiarArray(int *array, int size) {
    int *copia = (int*)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
        copia[i] = array[i];

    return copia;
}


void swap(int *num_1, int *num_2) {
    int temp = *num_1;

    (*num_1) = (*num_2);
    (*num_2) = temp;
}


int mediana(int *array, int start, int end, int *comparacoes) {
    int mid = start + (end - start) / 2;

    int a = array[start];
    int b = array[mid];
    int c = array[end];
    
    (*comparacoes) += 3; // conta a comparação entre 3 valores

    if ((a > b && a < c) || (a > c && a < b))
        return start;
    else if ((b > a && b < c) || (b > c && b < a))
        return mid;
    else
        return end;
}


void insertionSort(int *array, int start, int end, int *comparacoes) {

    for (int i = start + 1; i <= end; i++) {
        int key = array[i];
        int j = i - 1;

        // em cada ciclo há uma comparacao
        while (j >= start && array[j] > key) {
            array[j + 1] = array[j];

            (*comparacoes)++;
            j--;
        }
        
        // conta quando a comparacao no while é falsa
        if (j >= start) (*comparacoes)++;

        if (j + 1 != i)
            array[j + 1] = key;
    }
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
    int index_pivo = mediana(array, start, end, comparacoes);
    swap(&array[index_pivo], &array[end]);
    int pivo = array[end];

    // move o pivo para o final do array

    int i = start - 1;

    for (int j = start; j < end; j++) {
        (*comparacoes)++;

        if (array[j] <= pivo) {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[end]);
    return i + 1;
}


void quickSort(int *array, int start, int end, int *comparacoes) {
    if (start < end) {
        int pivo = particionar(array, start, end, comparacoes);

        quickSort(array, start, pivo - 1, comparacoes);
        quickSort(array, pivo + 1, end, comparacoes);
    }
}


void hybridQuickSort(int *array, int start, int end, int *comparacoes) {
    if (start < end) {
        // verifica se o array tem tamanho menor ou igual a 5
        if ((end - start + 1) <= 5)
            // passa o subarray correto (array[start] = array + start)
            insertionSort(array, start, end, comparacoes);
        else {
            int pivo = particionar(array, start, end ,comparacoes);
    
            hybridQuickSort(array, start, pivo - 1, comparacoes);
            hybridQuickSort(array, pivo + 1, end, comparacoes);
        }
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

    // faz uma cópia do array para o mergeSort
    int *array_copia = copiarArray(array, size);
    
    mergeSort(array_copia, 0, (size - 1), &comparacoes);
    
    // imprime os resultados
    printArray(array_copia, size);
    printf("%d\n", comparacoes);
    
    free(array_copia); // libera a memoria alocada para a cópia
    
    // faz uma cópia do array para o quickSort
    array_copia = copiarArray(array, size);
    comparacoes = 0; // restaura o numero de comparações iniciais.

    quickSort(array_copia, 0, (size - 1), &comparacoes);
    
    printArray(array_copia, size);
    printf("%d\n", comparacoes);

    free(array_copia);

    array_copia = copiarArray(array, size);
    comparacoes = 0; 

    hybridQuickSort(array_copia, 0, (size - 1), &comparacoes);
    
    printArray(array_copia, size);
    printf("%d\n", comparacoes);

    free(array_copia);

    free(array); // libera o array principal

    return 0;
}