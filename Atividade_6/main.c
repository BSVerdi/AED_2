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


No *rotacaoLL(No *raiz) {
    No *aux = raiz->esquerda;
    
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    
    // atualizando as alturas
    atualizarAltura(raiz);
    atualizarAltura(aux);
    
    return aux;
}


No *rotacaoRR(No *raiz) {
    No *aux = raiz->direita;
    
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    
    atualizarAltura(raiz);
    atualizarAltura(aux);
    
    return aux;
}


No *rotacaoLR(No *raiz) {
    raiz->esquerda = rotacaoRR(raiz->esquerda);
    return rotacaoLL(raiz);
}


No *rotacaoRL(No *raiz) {
    raiz->direita = rotacaoLL(raiz->direita);
    return rotacaoRR(raiz);
}


No *inserirAVL(No *raiz, int data) {
    if (raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        
        novo->data = data;
        novo->altura = 1;
        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    }
    
    if (data < raiz->data)
        raiz->esquerda = inserirAVL(raiz->esquerda, data);
    else
        raiz->direita = inserirAVL(raiz->direita, data);

    // atualiza a altura da raiz
    atualizarAltura(raiz);

    // calcula o fator de balanceamento
    int fator = fatorBalanceamento(raiz);

    if (fator > 1 && data < (raiz->esquerda)->data)
        return rotacaoLL(raiz);

    if (fator > 1 && data > (raiz->esquerda)->data)
        return rotacaoLR(raiz);

    if (fator < -1 && data > (raiz->direita)->data)
        return rotacaoRR(raiz);

    if (fator < -1 && data < (raiz->direita)->data)
        return rotacaoRL(raiz);
        
    return raiz;
}


No *rotacaoARNLL(No *raiz) {
    No *aux = raiz->direita;

    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;

    aux->cor = raiz->cor;
    raiz->cor = 1;

    atualizarAltura(raiz);
    atualizarAltura(aux);
    
    return aux;
}


No *rotacaoARNRR(No *raiz) {
    No *aux = raiz->esquerda;
    
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    
    aux->cor = raiz->cor;
    raiz->cor = 1;
    
    atualizarAltura(raiz);
    atualizarAltura(aux);

    return aux;
}


int isVermelho(No *raiz) {
    if (raiz == NULL)
        return 0;

    return raiz->cor == 1;
}


No *inserirARN(No *raiz, int data) {
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
        raiz->esquerda = inserirARN(raiz->esquerda, data);
    else
        raiz->direita = inserirARN(raiz->direita, data);
    
    if (isVermelho(raiz->direita) && !isVermelho(raiz->esquerda))
        raiz = rotacaoARNLL(raiz);
    
    if (isVermelho(raiz->esquerda) && raiz->esquerda != NULL && isVermelho(raiz->esquerda->esquerda))
        raiz = rotacaoARNRR(raiz);
    
    if (isVermelho(raiz->esquerda) && isVermelho(raiz->direita)) {
        raiz->cor = 1;
        
        raiz->esquerda->cor = 0;
        raiz->direita->cor = 0;
    }
    
    atualizarAltura(raiz);
    return raiz;
}


void liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}


void imprimirPreOrdem(No *raiz) {
    if (raiz != NULL) {
        printf("No %d | Altura: %d | Cor: %s\n", raiz->data, raiz->altura, raiz->cor ? "Vermelho" : "Preto");
        imprimirPreOrdem(raiz->esquerda);
        imprimirPreOrdem(raiz->direita);
    }
}


int main() {
    int num;
    No *avl = NULL;
    No *arn = NULL;

    while(1) {
        scanf("%d", &num);

        if (num >= 0) {
            avl = inserirAVL(avl, num);

            arn = inserirARN(arn, num);
            if (arn != NULL)
                arn->cor = 0;
        } else break;
    }

    // imprime a altura maxima a partir da raiz e a altura da subarvore da esquerda e direita
    printf("%d, %d, %d\n", alturaMax(altura(avl->esquerda), altura(avl->direita)), altura(avl->esquerda), altura(avl->direita));

    printf("%d, %d, %d\n", alturaMax(altura(arn->esquerda), altura(arn->direita)), altura(arn->esquerda), altura(arn->direita));

    printf("\n--- Arvore ARN ---\n");
    imprimirPreOrdem(arn);

    printf("%d", arn->data);

    liberarArvore(avl);
    liberarArvore(arn);

    return 0;
}