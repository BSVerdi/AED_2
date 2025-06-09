#include<stdio.h>
#include<stdlib.h>

typedef struct No {
    int data;
    int color;
    struct No *esquerda, *direita, *pai;
} No;


No *rotacaoEsquerda(No *raiz, No *novo) {
    No *temp = novo->direita;

    novo->direita = temp->esquerda;

    if (temp->esquerda != NULL)
        temp->esquerda->pai = novo;

    temp->pai = novo->pai;

    if (novo->pai == NULL)
        raiz = temp;
    else if (novo == novo->pai->esquerda)
        novo->pai->esquerda = temp;
    else
        novo->pai->direita = temp;

    temp->esquerda = novo;
    novo->pai = temp;

    return raiz;
}


No *rotacaoDireita(No *raiz, No *novo) {
    No *temp = novo->esquerda;

    novo->esquerda = temp->direita;

    if (temp->direita != NULL)
        temp->direita->pai = novo;

    temp->pai = novo->pai;

    if (novo->pai == NULL)
        raiz = temp;
    else if (novo == novo->pai->direita)
        novo->pai->direita = temp;
    else
        novo->pai->esquerda = temp;

    temp->direita = novo;
    novo->pai = temp;

    return raiz;
}

// função para corrigir após alguma inserção
No *corrigirI(No *raiz, No *novo) {
    while (novo->pai && novo->pai->color == 1) {
        No *avo = novo->pai->pai;

        if (novo->pai == avo->esquerda) {
            No *tio = avo->direita;

            if (tio && tio->color == 1) {
                novo->pai->color = 0; // troca a cor para preto
                tio->color = 0;
                avo->color = 1; // troca a cor para vermelho

                novo = avo;
            } else {
                if (novo == novo->pai->direita) {
                    novo = novo->pai;
                    raiz = rotacaoEsquerda(raiz, novo);
                }

                novo->pai->color = 0;
                avo->color = 1;
                raiz = rotacaoDireita(raiz, avo);
            }
        } else {
            No *tio = avo->esquerda;

            if (tio && tio->color == 1) {
                novo->pai->color = 0;
                tio->color = 0;
                avo->color = 1;

                novo = avo;
            } else {
                if (novo == novo->pai->esquerda) {
                    novo = novo->pai;
                    raiz = rotacaoDireita(raiz, novo);
                }

                novo->pai->color = 0;
                avo->color = 1;
                raiz = rotacaoEsquerda(raiz, avo);
            }
        }
    }

    raiz->color = 0;

    return raiz;
}


No *inserir(No *raiz, int data) {
    // criando o novo nó
    No *novo = (No*)malloc(sizeof(No));

    novo->data = data;
    novo->color = 1; //  novos nós sempre vermelhos
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->pai = NULL;

    No *temp = NULL;
    No *aux = raiz;

    // percorre a arvore iterativamente
    while (aux != NULL) {   
        temp = aux;

        if (novo->data < aux->data)
            aux = aux->esquerda;
        else
            aux = aux->direita;
    }

    novo->pai = temp;

    // inserção do novo nó na arvore
    if (temp == NULL)
        raiz = novo;
    else if (novo->data < temp->data)
        temp->esquerda = novo;
    else
        temp->direita = novo;

    raiz = corrigirI(raiz, novo); // corrige a arvore após a inserção de um novo elemento

    return raiz;
}


No *corrigirR(No *raiz, No *aux, No *aux_pai) {
    while (aux != raiz && (aux == NULL || aux->color == 0)) {
        if (aux == aux_pai->esquerda) {
            No * temp = aux_pai->direita;

            if (temp->color == 1) {
                temp->color = 0;
                aux_pai->color = 1;

                raiz = rotacaoEsquerda(raiz, aux_pai);

                temp = aux_pai->direita;
            }

            if ((temp->esquerda == NULL || temp->esquerda->color == 0) && (temp->direita == NULL || temp->direita->color == 0)) {
                temp->color = 1;

                aux = aux_pai;
                aux_pai = aux->pai;
            } else {
                if (temp->direita == NULL || temp->direita->color == 0) {
                    if (temp->esquerda)
                        temp->esquerda->color = 0;

                    temp->color = 1;

                    raiz = rotacaoDireita(raiz, temp);

                    temp = aux_pai->direita;
                }

                temp->color = aux_pai->color;
                aux_pai->color = 0;

                if (temp->direita)
                    temp->direita->color = 0;

                raiz = rotacaoEsquerda(raiz, aux_pai);

                aux = raiz;
            }
        } else {
            No *temp = aux_pai->esquerda;

            if (temp->color == 1) {
                temp->color = 0;
                aux_pai->color = 1;

                raiz = rotacaoDireita(raiz, aux_pai);

                temp = aux_pai->esquerda;
            }

            if ((temp->direita == NULL || temp->direita->color == 0) && (temp->esquerda == NULL || temp->esquerda->color == 0)) {
                temp->color = 1;

                aux = aux_pai;
                aux_pai = aux->pai;
            } else {
                if (temp->esquerda == NULL || temp->esquerda->color == 0) {
                    if (temp->direita)
                        temp->direita->color = 0;

                    temp->color = 1;

                    raiz = rotacaoEsquerda(raiz, temp);

                    temp = aux_pai->esquerda;
                }

                temp->color = aux_pai->color;
                aux_pai->color = 0;

                if (temp->esquerda)
                    temp->esquerda->color = 0;

                raiz = rotacaoDireita(raiz, aux_pai);

                aux = raiz;
            }
        }
    }

    if (aux) 
        aux->color = 0;
    
    return raiz;
}


No *buscar(No *raiz, int data) {
    if (raiz != NULL) {
        if (data == raiz->data)
            return raiz;

        if (data < raiz->data)
            return buscar(raiz->esquerda, data);
        else
            return buscar(raiz->direita, data);
    }

    return NULL;
}


No *sucessor(No * raiz) {
    if (raiz->esquerda != NULL)
        return sucessor(raiz->esquerda);
    
    return raiz;
}


No *swap(No *raiz, No *no1, No *no2) {
    if (no1->pai == NULL)
        raiz = no2;
    else if (no1 == no1->pai->esquerda)
        no1->pai->esquerda = no2;
    else
        no1->pai->direita = no2;

    if (no2 != NULL)
        no2->pai = no1->pai;

    return raiz;
}


No *remover(No *raiz, int data) {
    No *lixo = buscar(raiz, data);

    if (!lixo) return raiz; // valor nao encontrado

    No *temp = lixo;
    int cor = temp->color;
    No *aux;
    No *aux_pai;

    if (lixo->esquerda == NULL) {
        aux = temp->direita;
        aux_pai = lixo->pai;

        raiz = swap(raiz, lixo, lixo->direita);
    } else if (lixo->direita == NULL) {
        aux = lixo->esquerda;
        aux_pai = lixo->pai;

        raiz = swap(raiz, lixo, lixo->esquerda);
    } else {
        temp = sucessor(raiz->direita);
        cor = temp->color;
        aux = temp->direita;

        if (temp->pai == lixo) {
            if (aux)
                aux->pai = temp;
            
            aux_pai = temp;
        } else {
            raiz = swap(raiz, temp, temp->direita);

            temp->direita = lixo->direita;

            if (temp->direita)
                temp->direita->pai = temp;
            
                aux_pai = temp->pai;
        }

        raiz = swap(raiz, lixo, temp);

        temp->esquerda = lixo->esquerda;

        if (temp->esquerda)
            temp->esquerda->pai = temp;

        temp->color = lixo->color;
    }

    free(lixo);

    if (cor == 0)
        raiz = corrigirR(raiz, aux, aux_pai);

    return raiz;
}


int main() {
    int num;
    No *raiz = NULL;

    while (1) {
        scanf("%d", &num);

        if (num >= 0)
            raiz = inserir(raiz ,num);
        else break;
    }

    printf("%d", raiz->data); //debug

    return 0;
}