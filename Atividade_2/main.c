#include<stdio.h>
#include<stdlib.h>

int *CopiarVetor(int *array, int size) {
    int *array_copia = (int*)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
        array_copia[i] = array[i];

    return array_copia;
}


void swap(int *array, int index_a, int index_b) {
    int temp = array[index_a];

    array[index_a] = array[index_b];
    array[index_b] = temp;
}


void SelectionSort(int *array, int size) {
    int *temp = CopiarVetor(array, size);
    int min, comparacoes = 0, trocas = 0;

    for (int i = 0; i < size - 1; i++) {
        min = i;
        
        for (int j = i + 1; j < size; j++) {
            if (temp[min] > temp[j]) {
                min = j;
            }
            comparacoes++;
        }
        if (min != i) {
            swap(temp, min, i);
            trocas++;
        } 
        // else {
        //     free(temp);
        //     break;
        // }
    }

    printf("%d %d\n", comparacoes, trocas);
}


int main() {
    int *array, *array2;
    int size;

    scanf("%d", &size);

    array = (int*)malloc(sizeof(int) * 1000);

    for (int i = 0; i < 1000; i++)
        array[i] = 1000 - i;
        //scanf("%d", &array[i]);

    SelectionSort(array, 1000);

    return 0;
}