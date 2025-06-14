/*
    Atividade: Algoritmo de hashtable
    Data: 14/06/2025 - UNIFESP
    Aluno: Breno Silveira Signorini Verdi

    Algoritmos implementados:
    - hashtable com duplo mapeamento e aberto
    - Inserção em hashtable aberto
    - remoção em hashtable aberto (junto a pesquisa em hashtable aberto)
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Hashtable {
    int key;
    int situation; // 2 para removido, 1 para ocupado e 0 para livre
} Hashtable;



int hash1(int key, int size) {
    return key % size;
}


int hash2(int key, int size) {
    return 1 + (key % (size - 1));
}


int hash(int key, int size, int i) {
    return (hash1(key, size) + (i * hash2(key, size))) % size;
}


void inserir(Hashtable *table, int key, int size) {
    for (int i = 0; i < size; i++) {
        int index = hash(key, size, i);

        // verifica se a chave esta vazia ou com elemento removido
        if (table[index].situation == 0 || table[index].situation == 2) {
            table[index].key = key;
            table[index].situation = 1; // marca a chave como ocupada

            return;
        }
    }
}


int remover(Hashtable *table, int key, int size) {
    int removido = 0;

    for (int i = 0; i < size; i++) {
        int index = hash(key, size, i);

        if (table[index].situation == 0)
            break; // Se nao esta ocupado, nao tem mais chance de encontrar outro valor

        if (table[index].situation == 1 && table[index].key == key) {
            table[index].situation = 2; // removido
            removido = 1;   
        }
    }

    return removido; // se houve uma remoção retorna 1, caso contrario retorna 0
}


void printTable(Hashtable *table, int size) {   
    for (int i = 0; i < size; i++) {
        if (table[i].situation == 1)
            printf("%d ", table[i].key); // imprime o valor caso a chave esteja ocupada
        else if (table[i].situation == 0)
            printf("\\ "); // imprime "\" caso a chave esteja desocupada
        else 
            printf("D "); // imprime "D" caso a chave esteja com um elemento removido
    }
}


int main() {
    Hashtable *table;
    int size, num;

    scanf("%d", &size);

    // inicializa a hashtable
    table = (Hashtable*)malloc(sizeof(Hashtable) * size);
    for (int i = 0; i < size; i++)
        table[i].situation = 0; // marca todas a chaves como livres

    while (1) {
        scanf("%d", &num);

        if (num > 0)
            inserir(table, num, size);
        else break;
    }

    scanf("%d", &num);

    // verifica se houve remoção, se houve significa que o valor foi encontrado
    if (!remover(table, num, size))
        printf("Valor nao encontrado\n");

    // print da hashtable
    printTable(table, size);

    return 0;
}