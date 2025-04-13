#include<stdio.h>
#include<stdlib.h>
#include<time.h>

const long int SIZE = 100000000;


int separa(long int *array, int left, int right) {
    long int pivo = left + rand() % (right - left + 1);
    int i = (left - 1);
    long int aux;
    
    for (int j = left; j < right; j++) {
        if (array[j] <= pivo) {
            i++;
            aux = array[i];
            array[i] = array[j];
            array[j] = aux;
        }
    }
    aux = array[i + 1];
    array[i + 1] = array[right];
    array[right] = aux;
    
    return (i + 1);
}


void quicksort(long int *array, int left, int right) {
    if (left < right) {
        int indice_pivo = separa(array, left, right);
        
        quicksort(array, left, indice_pivo - 1);
        quicksort(array, indice_pivo + 1, right);
    }
}


int main() {
    long int *array = (long int *)malloc(sizeof(long int) * SIZE);
    clock_t tempo;
    int i;

    srand((unsigned)time(NULL));
    
    printf("%ld", SIZE / 2);


    for (i = 0; i < (SIZE / 2); i++) {
        array[i] = rand() % SIZE;
        array[i + (SIZE / 2)] = rand() % SIZE;
    }

    printf("Valores Criados!\n");
    
    quicksort(array, 0, SIZE);
    
    printf("Valores Ordenados!\n");

    for (i = 0; i < SIZE; i++)
        printf(" %ld =>", array[i]);

    return 0;
}