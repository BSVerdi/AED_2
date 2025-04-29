/*
    Atividade: Algoritmos de Ordenação Quadráticos
    Data: 28/4/2025 - UNIFESP

    Algoritmos implementados:
    - Selection Sort
    - Bubble Sort
    - Insertion Sort

*/

#include<stdio.h>
#include<stdlib.h>

// função para copiar o vetor
int *CopiarVetor(int *array, int size) { 
    int *array_copia = (int*)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
        array_copia[i] = array[i];

    return array_copia; // retorna um endereço para a copia do vetor original
}

// função para trocar os valores de posição
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
        
        for (int j = i + 1; j < size; j++) { // em cada ciclo há uma comparação
            if (temp[min] > temp[j]) {
                min = j;
            }
            comparacoes++;
        }
        if (min != i) { // so haverá troca se os indices forem diferentes
            swap(temp, min, i);
            trocas++;
        } 
    }
    free(temp); // libera o vetor temporario

    printf("%d %d\n", comparacoes, trocas); // imprime os resultados
}


void BubbleSort(int *array, int size) {
    int *temp = CopiarVetor(array, size);
    int comparacoes = 0, trocas = 0, valid;

    for (int i = 0; i < size - 1; i++) {
        valid = 0;

        for (int j = 0; j < size - 1 - i; j++) { // a cada ciclo há uma comparação
            if (temp[j] > temp[j + 1]) { // em caso verdadeira haverá uma troca
                swap(temp, j, j + 1);
                trocas++;
                valid = 1; // confirma que houve pelo menos 1 troca
            }
            comparacoes++;
        }

        if (!valid) break; // checar se houve pelo menos 1 troca, se não houve, para o loop
    }
    free(temp); // libera o vetor temporario

    printf("%d %d\n", comparacoes, trocas); // imprime os resultados
}


void InsertionSort(int *array, int size) {
    int *temp = CopiarVetor(array, size);
    int comparacoes = 0, trocas = 0;

    for (int i = 1; i < size; i++) {
        int key = temp[i];
        int j = i - 1;
        
        while (j >= 0 && temp[j] > key) { // em cada ciclo do while ocorre uma comparação e uma troca
            temp[j + 1] = temp[j];
            
            comparacoes++;
            trocas++;

            j--;
        }

        if (j >= 0) comparacoes++; // garante a contagem da comparação em caso da condição no while ser falsa

        if (j + 1 != i) { //o j ser diferente de i implica que houve movimentação no vetor, logo a key precisa ser mudada
            temp[j + 1] = key;
            trocas++;
        }
    }
    free(temp); // libera o vetor temporario

    printf("%d %d\n", comparacoes, trocas); // imprime os resultados
}


int main() {
    int *array;
    int size;

    scanf("%d", &size); // recebe o tamanho do array

    array = (int*)malloc(sizeof(int) * size); // aloca um espaço na memória para o array

    for (int i = 0; i < size; i++)
        scanf("%d", &array[i]); // recebe os valores do array

    SelectionSort(array, size);

    BubbleSort(array, size);

    InsertionSort(array, size);

    free(array); // libera o array

    return 0;
}