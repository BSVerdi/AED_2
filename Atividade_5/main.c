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


No *inserir(No *raiz, int data) {
    if (raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        
        novo->data = data;
        novo->altura = 1;
        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    }
    
    if (data < raiz->data)
        raiz->esquerda = inserir(raiz->esquerda, data);
    else
        raiz->direita = inserir(raiz->direita, data);

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
    
    
No *remover(No *raiz, int key) {
    if (raiz == NULL)
    return NULL;
    
    if (key < raiz->data)
    raiz->esquerda = remover(raiz->esquerda, key);
    else if (key > raiz->data)
    raiz->direita = remover(raiz->direita, key);
    else {
        No *temp;
        if (raiz->esquerda == NULL) {
            temp =  raiz->direita;
            free(raiz);

            return temp;
        } else if (raiz->direita == NULL) {
            temp =  raiz->esquerda;
            free(raiz);

            return temp;
        }
        
        No *sucessor = raiz->direita;
        
        // acha o menor valor da direita
        while (sucessor->esquerda != NULL)
        sucessor = sucessor->esquerda;
        
        raiz->data = sucessor->data;
        raiz->direita = remover(raiz->direita, sucessor->data);
    }

    if (raiz == NULL)
        return raiz;
    
    atualizarAltura(raiz);
    
    int fator_raiz = fatorBalanceamento(raiz);
    int fator_esquerda = fatorBalanceamento(raiz->esquerda);
    int fator_direita = fatorBalanceamento(raiz->direita);

    if (fator_raiz > 1 && fator_esquerda >= 0)
        return rotacaoLL(raiz);

    if (fator_raiz > 1 && fator_esquerda < 0)
        return rotacaoLR(raiz);

    if (fator_raiz < -1 && fator_direita <= 0)
        return rotacaoRR(raiz);
    
    if (fator_raiz < -1 && fator_direita > 0)
        return rotacaoRL(raiz);

    return raiz;
}


void liberarArvore(No *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}


int buscar(No *raiz, int data) {
    if (raiz != NULL) {
        if (data == raiz->data)
            return 1;

        if (data < raiz->data)
            return buscar(raiz->esquerda, data);
        else
            return buscar(raiz->direita, data);
    }

    return 0;
}

void printArvore(No *raiz, int start, int end, int maior) {
    if (raiz != NULL) {
        printArvore(raiz->esquerda, start, end, maior);
 
        if (raiz->data >= start && raiz->data <= end) {
            printf("%d", raiz->data);
            
            // garante a posição correta das virgulas
            if (raiz->data < maior)
                printf(", ");
        }
 
        printArvore(raiz->direita, start, end, maior);
    }
}
 
 
void printAlturas(No * raiz, int start, int end) {
    if (raiz != NULL) {
        printAlturas(raiz->esquerda, start, end);
        
        if (raiz->data >= start && raiz->data <= end)
            printf("%d, %d, %d\n", alturaMax(altura(raiz->esquerda), altura(raiz->direita)), altura(raiz->esquerda), altura(raiz->direita));
 
        printAlturas(raiz->direita, start, end);
    }
}


int main() {
    int num, start, end, maior = -1;
    No *raiz = NULL;

    while(1) {
        scanf("%d", &num);

        if (num >= 0)
            raiz = inserir(raiz, num);
        else break;
    }

    // imprime a altura maxima a partir da raiz e a altura da subarvore da esquerda e direita
    printf("%d, %d, %d\n", alturaMax(altura(raiz->esquerda), altura(raiz->direita)), altura(raiz->esquerda), altura(raiz->direita));
    
    while (1) {
        scanf("%d", &num);
        
        if (num >= 0) {
            // verifica se a arvore ja contem o valor inserido
            if (buscar(raiz, num))
            raiz = remover(raiz, num);
            else
            raiz = inserir(raiz, num);
        } else break;
    }
    
    // verifica se a arvore nao esta vazia
    if (raiz != NULL)
        printf("%d, %d, %d\n", alturaMax(altura(raiz->esquerda), altura(raiz->direita)), altura(raiz->esquerda), altura(raiz->direita));
    else
        printf("ARVORE VAZIA\n");

    // coleta o intervalo a ser impresso
    scanf("%d %d", &start, &end);

    // verifica se  elementos do intervalo na arvore e coleto o maior dentro do intervalo
    for (int i = start; i <= end; i++) {
        if (buscar(raiz, i)) {
            if (maior == -1)
                maior = i;
            else if (i > maior)
                maior = i;
        }
    }

    if (maior > 0) {
        // imprime a sequencia numerica dentro do intervalo
        printArvore(raiz, start, end, maior);
        printf("\n");

        // imprime as alturas de cada nó;
        printAlturas(raiz, start, end);
        printf("\n");
    } else
        printf("NADA A EXIBIR\n");

    liberarArvore(raiz);

    return 0;
}