/*
    Atividade: Algoritmos de Ordenação linear
    Data: 16/5/2025 - UNIFESP

    Algoritmos implementados:
    - Counting Sort
    - Radix Sort
*/
#include<stdio.h>
#include<stdlib.h>

// funcao para converter a letra em um indice para o "index"
int hash(char letra) {
    if (letra == 32) return 0;

    return ((letra - 97) % 26) + 1;
}


int *lerSequencia() {
    int *index = (int*)malloc(sizeof(int) * 27);
    int aux;
    char temp[26];

    scanf("%s", temp);

    // cada posição no index recebe o index da letra na sequencia para ser usado no vetor C
    index[0] = 0;
    for (int i = 1; i < 27; i++) {
        aux = hash(temp[i - 1]);
        index[aux] = i;
    }

    return index;
}


void MaiusculaParaMinuscula(char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i]  < 'a')
            string[i] += 32;
    }
}


char *copiarString(char *string, int size) {
    char *string2= (char*)malloc(sizeof(char) * size + 1);
    int j = 0;
    
    for (int i = 0; i < size; i++) {
        if (string[j] != '\0')
            string2[i] = string[j++];
        else
            string2[i] = 32;
    }
    string2[size] = '\0';

    return string2;
}


int stringSize(char *string) {
    int size;

    for (size = 0; string[size] != '\0'; size++);

    return size;
}


void countingSort(int *index, char **words, int palavras, int coluna) {
    int c[27], k;
    char **ordenado = (char**)malloc(sizeof(char*) * palavras);

    for(int i = 0; i < 27; i++)
        c[i] = 0;
    
    for (int i = 0; i < palavras; i++) {
        k = hash(words[i][coluna]);
        c[index[k]]++;
    }

    for (int i = 1; i < 27; i++)
        c[i] += c[i - 1];

    // impressao do vetor C
    for (int i = 0; i < 27; i++)
        printf("%d ", c[i]);
    printf("\n");

    // ordenação das palavras em um subarray temporario
    for (int i = palavras - 1; i >= 0; i--) {
        k = hash(words[i][coluna]);
        ordenado[c[index[k]] - 1] = words[i];
        c[index[k]]--;
    }

    // copiando a ordem para o array original
    for (int i = 0; i < palavras; i++)
        words[i] = ordenado[i];
        
    free(ordenado);
}


void radixSort(int *index, char **words, int palavras, int size) {
    for (int j = (size - 1); j >= 0; j--)
        countingSort(index, words, palavras, j);
}


int main() {
    int palavras, size, maior;
    char string[20];

    scanf("%d", &palavras);

    // pega a sequencia base para ordenação
    int *index = lerSequencia();

    // Aloca memória para o array temporário
    char **temp = (char**)malloc(sizeof(char*) * palavras);
    
    for (int i = 0; i < palavras; i++) {
        scanf("%s", string);
        
        size = stringSize(string);
        if (i == 0 || size > maior) 
        maior = size;
        
        MaiusculaParaMinuscula(string);
        
        temp[i] = copiarString(string, size);
        printf("%s.\n", temp[i]);
    }
    
    printf("%d\n", maior);
    // Aloca memória para o array definitivo com todas as string com mesmo tamanho
    char **words = (char**)malloc(sizeof(char*) * palavras);
    
    for (int i = 0; i < palavras; i++) { 
        words[i] = copiarString(temp[i], maior);  
        free(temp[i]);
        
    }
    free(temp); // libera temp

    radixSort(index, words, palavras, maior);
    
    for (int i = 0; i < palavras; i++) {
        puts(words[i]);
        free(words[i]);
    }
    free(words);

    return 0;
}