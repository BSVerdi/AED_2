/*
    Atividade: Algoritmos em grafos
    Data: 07/07/2025 - UNIFESP
    Aluno: Breno Silveira Signorini Verdi

    Algoritmos implementados:
    - Busca em largura (BFS)
    - Busca em profundidade (DFS)
*/
#include<stdio.h>
#include<stdlib.h>

// estrutura para a grafo com lista de adjacencia
typedef struct Grafo {
    int vertice;
    struct Grafo *seg;
} Grafo;

// estrutura para fila em um array
typedef struct Queue {
    int *data;
    int size;
} Queue;


void push(Queue *fila, int data) {
    fila->data[fila->size++] = data;
}


int pop(Queue *fila) {
    int data = fila->data[0];

    for (int i = 0; i < fila->size; i++)
        fila->data[i] = fila->data[i + 1];

    fila->size--;

    return data;
}


Grafo **iniciarGrafo(int vertices) {
    Grafo **grafo = (Grafo**)malloc(sizeof(Grafo*) * vertices);
    
    for (int i = 0; i < vertices; i++) {
        grafo[i] = (Grafo*)malloc(sizeof(Grafo));
        grafo[i]->seg = NULL;
    }

    return grafo;
}


int *iniciarVisitado(int vertices) {
    int *visitado = (int*)malloc(sizeof(int) * vertices);

    for (int i = 0; i < vertices; i++)
        visitado[i] = 0;

    return visitado;
}


void append(Grafo **grafo, int origem, int destino) {
    Grafo *novo = (Grafo*)malloc(sizeof(Grafo));
    novo->vertice = destino;
    novo->seg = NULL;

    Grafo *temp = grafo[origem];

    while (temp->seg != NULL && temp->seg->vertice < destino)
        temp = temp->seg;
    
    novo->seg = temp->seg;
    temp->seg = novo;
}
    
// busca em largura
void bfs(Grafo **grafo, int vertices, int origem, int *visitado) {
    Queue fila;

    fila.size = 0;
    fila.data = (int*)malloc(sizeof(int) * vertices);

    visitado[origem] = 1;

    push(&fila, origem);

    while (fila.size > 0) {
        int i = pop(&fila);

        // imprime a ordem da busca em largura
        printf("%d ", i);

        for (Grafo *temp = grafo[i]->seg; temp != NULL; temp = temp->seg) {
            if (!visitado[temp->vertice]) {
                visitado[temp->vertice] = 1;
                push(&fila, temp->vertice);
            }
        }
    }
    printf("\n");

    free(fila.data);
}

// busca em profundidade
void dfs(Grafo **grafo, int vertices, int origem, int *visitado) {
    printf("%d ", origem);

    visitado[origem] = 1;

    for (Grafo *temp = grafo[origem]->seg; temp != NULL ; temp = temp->seg) {
        if (!visitado[temp->vertice]) {
            dfs(grafo, vertices, temp->vertice, visitado);
        }
    }
}


int main() {
    int vertices, arestas, inicio, *visitados;
    Grafo **grafo;

    scanf("%d %d %d", &inicio, &vertices, &arestas);
    
    // inicializa o grafo
    grafo = iniciarGrafo(vertices);
    
    // le o grafo
    for (int i = 0; i < arestas; i++) {
        int origem, destino;
        
        scanf("%d %d", &origem, &destino);
        
        append(grafo, origem, destino);
    }
    
    // inicializa o vetor de visitados 
    visitados = iniciarVisitado(vertices);
    
    // executa a busca em largura
    bfs(grafo, vertices, inicio, visitados);
    
    // libera o visitados
    free(visitados);
    
    // inicializa um novo vetor de visitados
    visitados = iniciarVisitado(vertices);

    // executa a busca em profundidade
    dfs(grafo, vertices, inicio, visitados);

    // libera o visitados
    free(visitados);

    // libera a memoria 
    for (int i = 0; i < vertices; i++) {
        Grafo *temp = grafo[i];

        while (temp != NULL) {
            Grafo *prox = temp->seg;
            free(temp);
            temp = prox;
        }
    }
    free(grafo);

    return 0;
}