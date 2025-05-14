#include<stdio.h>
#include<stdlib.h>


typedef struct {
    char *string;
    struct Celula *seg;
} Celula;


typedef struct {
    char *string;
    int str_size;
} Array;


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


Celula *push(Celula *pilha, char *string, int size) {
    Celula *nova = (Celula*)malloc(sizeof(Celula));

    nova->string = copiarString(string, size);  
    nova->seg = pilha;

    return nova;
}


Celula *pop(Celula *pilha, char **string, int size) {
    Celula *lixo = (Celula*)malloc(sizeof(Celula));

    lixo = pilha;
    (*string) = copiarString(lixo->string, size);

    pilha = lixo->seg;
    free(lixo);

    return pilha;
}


void printPilha(Celula *pilha) {
    printf("Pilha: ");
    for (Celula *temp = pilha; temp != NULL; temp = temp->seg)
        printf("%s ", temp->string);
    printf("\n");
}


int main() {
    Array *array;
    Celula *pilha = NULL;
    char string[20];
    int palavras, size, maior;

    scanf("%d", &palavras);

    
    for (int i = 0; i < palavras; i++) {
        scanf("%s", string);
        
        size = stringSize(string);
        if (i == 0) 
        maior = size;
        else if (size > maior)
        maior = size;
        
        MaiusculaParaMinuscula(string);
        
        pilha = push(pilha, string, size);
        
        puts(pilha->string);
    }

    array = (Array*)malloc(sizeof(Array) * palavras);
    
    for (int i = 0; i < palavras; i++) {
        pilha = pop(pilha, &(array[i].string), maior);
        
        puts(array[i].string);
    }

    return 0;
}