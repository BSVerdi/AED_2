/*
    Atividade: Algoritmos de balanceamento de arvores binarias de busca
    Data: 25/5/2025 - UNIFESP
    Aluno: Breno Silveira Signorini Verdi

    Algoritmos implementados:
    - Arvores AVL
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct No {
    int data;
    int altura;
    int cor; // somente para Arvore RN. 1 para vermelho 0 para preto
    struct No *esquerda;
    struct No *direita;
} No;


int alturaMax(int a, int b) {
    if (a > b) return a;
    return b;
}


int altura(No *raiz) {
    if (raiz != NULL)
        return raiz->altura;

    return 0;
}


void atualizarAltura(No *raiz) {
    if (raiz != NULL)
        raiz->altura = 1 + alturaMax(altura(raiz->esquerda), altura(raiz->direita));
}


int fatorBalanceamento(No *raiz) {
    if (raiz != NULL)
        return altura(raiz->esquerda) - altura(raiz->direita);
    
    return 0;
}


No *rotacaoLL(No *raiz, int *rotations) {
    No *aux = raiz->esquerda;
    
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    
    // atualizando as alturas
    atualizarAltura(raiz);
    atualizarAltura(aux);
    
    (*rotations)++;

    return aux;
}


No *rotacaoRR(No *raiz, int *rotations) {
    No *aux = raiz->direita;
    
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    
    atualizarAltura(raiz);
    atualizarAltura(aux);

    (*rotations)++;
    
    return aux;
}


No *rotacaoLR(No *raiz, int *rotations) {
    raiz->esquerda = rotacaoRR(raiz->esquerda, rotations);
    return rotacaoLL(raiz, rotations);
}


No *rotacaoRL(No *raiz, int *rotations) {
    raiz->direita = rotacaoLL(raiz->direita, rotations);
    return rotacaoRR(raiz, rotations);
}


No *inserirAVL(No *raiz, int data, int *rotations) {
    if (raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        
        novo->data = data;
        novo->altura = 1;
        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    }
    
    if (data < raiz->data)
        raiz->esquerda = inserirAVL(raiz->esquerda, data, rotations);
    else
        raiz->direita = inserirAVL(raiz->direita, data, rotations);

    // atualiza a altura da raiz
    atualizarAltura(raiz);

    // calcula o fator de balanceamento
    int fator = fatorBalanceamento(raiz);

    if (fator > 1 && data < (raiz->esquerda)->data)
        return rotacaoLL(raiz, rotations);

    if (fator > 1 && data > (raiz->esquerda)->data)
        return rotacaoLR(raiz, rotations);

    if (fator < -1 && data > (raiz->direita)->data)
        return rotacaoRR(raiz, rotations);

    if (fator < -1 && data < (raiz->direita)->data)
        return rotacaoRL(raiz, rotations);
        
    return raiz;
}


No *rotacaoARNRR(No *raiz, int *changes, int *rotations) {
    No *aux = raiz->esquerda;

    raiz->esquerda = aux->direita;
    aux->direita = raiz;

    aux->cor = raiz->cor;
    raiz->cor = 1;
    
    atualizarAltura(raiz);
    atualizarAltura(aux);
    
    (*changes) += (aux->cor != raiz->cor) + (raiz->cor != 1);
    
    (*rotations)++;

    return aux;
}


No *rotacaoARNLL(No *raiz, int *changes, int *rotations) {
    No *aux = raiz->direita;

    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    
    aux->cor = raiz->cor;
    raiz->cor = 1;
    
    atualizarAltura(raiz);
    atualizarAltura(aux);

    (*changes) += (aux->cor != raiz->cor) + (raiz->cor != 1);

    (*rotations)++;
    
    return aux;
}


int isVermelho(No *raiz) {
    if (raiz == NULL)
        return 0;

    return raiz->cor == 1;
}


No *inserirARN(No *raiz, int data, int *changes, int *rotations) {
    if (raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        
        novo->data = data;
        novo->altura = 1;
        novo->cor = 1;
        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    }
    
    if (data < raiz->data)
        raiz->esquerda = inserirARN(raiz->esquerda, data, changes, rotations);
    else
        raiz->direita = inserirARN(raiz->direita, data, changes, rotations);
    
    if (isVermelho(raiz->direita) && !isVermelho(raiz->esquerda))
        raiz = rotacaoARNLL(raiz, changes, rotations);
    
    if (isVermelho(raiz->esquerda) && isVermelho(raiz->esquerda->esquerda))
        raiz = rotacaoARNRR(raiz, changes, rotations);
    
    if (isVermelho(raiz->esquerda) && isVermelho(raiz->direita)) {
        raiz->cor = 1;
        
        raiz->esquerda->cor = 0;
        raiz->direita->cor = 0;
        (*changes) += 3;
    }
    
    atualizarAltura(raiz);
    return raiz;
}


int alturaNegra(No *raiz) {
    int count = 0;
    No *atual = raiz;
    
    while (atual != NULL) {
        if (atual->cor == 0) // Se o nó é preto
            count++;
        atual = atual->esquerda;
    }
    return count;
}


void liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}


int main() {
    int num, changes = 0, rotationsAVL = 0, rotationsARN = 0;
    No *avl = NULL;
    No *arn = NULL;

    while(1) {
        scanf("%d", &num);

        if (num >= 0) {
            avl = inserirAVL(avl, num, &rotationsAVL);

            arn = inserirARN(arn, num, &changes, &rotationsARN);

            if (arn != NULL && arn->cor == 1) {
                arn->cor = 0;
                changes++;
            }
        } else break;
    }

    // imprime a altura maxima a partir da raiz e a altura da subarvore da esquerda e direita
    printf("%d, %d, %d\n", alturaMax(altura(avl->esquerda), altura(avl->direita)), altura(avl->esquerda), altura(avl->direita));

    printf("%d, %d, %d\n", alturaMax(altura(arn->esquerda), altura(arn->direita)), altura(arn->esquerda), altura(arn->direita));

    // print da altura negra
    printf("%d\n", alturaNegra(arn));

    // print das mudanças de cores e rotações
    printf("%d, %d, %d", changes, rotationsARN, rotationsAVL);

    liberarArvore(avl);
    liberarArvore(arn);

    return 0;
}