#include<stdio.h>
#include<stdlib.h>
#include<time.h>

const long int SIZE = 100000000;


int separa(long int *array, int left, int right) {
    long int pivo = array[right];
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


int buscaLinear(long int *array, long int data) {
    for (int i = 0; i < SIZE; i++) {
        if (array[i] == data)
            return i;
    }
    return -1;
}


int buscaBinaria(long int *array, long int data) {
    int left = 0;
    int right = SIZE -1;
    int mid;
    
    while (left <= right) {
        mid = (left + right) / 2;
        if (array[mid] == data)
            return mid;
        else if (array[mid] < data)
            left = mid + 1;
        else 
            right = mid - 1;
    }

    return -1;
}


int buscaBinariaRecursiva(long int *array, long int data, int left, int right) {
    int mid = (left + right) / 2;

    if (array[mid] == data)
        return mid;
    else if (array[mid] < data)
        buscaBinariaRecursiva(array, data, mid + 1, right);
    else
        buscaBinariaRecursiva(array, data, left, mid - 1);

    return -1;
}


int main() {
    long int *array = (long int *)malloc(sizeof(long int) * SIZE);
    long int num;
    clock_t tempo;
    int i, index;

    srand((unsigned)time(NULL));

    for (i = 0; i < SIZE; i++)
        array[i] = rand() % SIZE;

    printf("Valores Criados!\n");
    printf("Iniciando ordenacao\n");

    tempo = clock();
    quicksort(array, 0, SIZE - 1);
    tempo = clock() - tempo;
    
    printf("Valores Ordenados!\nTempo de execucao: %.0lf ms\n", ((double)tempo)/(CLOCKS_PER_SEC/1000));

    for (i = 0; i < 20; i++) {
        num = rand() % SIZE;

        printf("Ciclo %d\n", i + 1);
        printf("num = %ld\n", num);

        tempo = clock();
        index = buscaLinear(array, num);
        tempo = clock() - tempo;

        printf("indice = %d\n", index);
        printf("Tempo de execucao busca linear: %.0lf ms\n",  ((double)tempo)/(CLOCKS_PER_SEC/1000));
        
        tempo = clock();
        buscaBinaria(array, num);
        tempo = clock() - tempo;

        printf("indice = %d\n", index);
        printf("Tempo de execucao busca binaria: %.0lf ms\n",  ((double)tempo)/(CLOCKS_PER_SEC/1000));
        
        tempo = clock();
        buscaBinariaRecursiva(array, num, 0, SIZE - 1);
        tempo = clock() - tempo;

        printf("indice = %d\n", index);
        printf("Tempo de execucao busca binaria recursiva: %.0lf ms\n",  ((double)tempo)/(CLOCKS_PER_SEC/1000));
    }

    return 0;
}