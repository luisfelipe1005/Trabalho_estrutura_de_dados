#include "bst_est.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListaEst* criar_lista_estoque(void) {
    ListaEst *lista = (ListaEst *) malloc(sizeof(ListaEst));
    if (!lista) return NULL;
    lista->primeiro = NULL;
    lista->quantidade = 0;
    return lista;
}

static NoEst* criar_no(int codigo, const char *item, int quantidade) {
    NoEst *novo = (NoEst *) malloc(sizeof(NoEst));
    if (!novo) return NULL;

    novo->codigo = codigo;
    novo->quantidade = quantidade;
    strncpy(novo->item, item, sizeof(novo->item) - 1);
    novo->item[sizeof(novo->item) - 1] = '\0';

    novo->esquerda = novo->direita = novo->pai = NULL;
    return novo;
}

NoEst* inserir_estoque(ListaEst *lista, int codigo,  char *item, int quantidade) {
    if (!lista) return NULL;

    NoEst *novo = criar_no(codigo, item, quantidade);
    if (!novo) return NULL;

    if (lista->primeiro == NULL) {
        lista->primeiro = novo;
        lista->quantidade = 1;
        return novo;
    }

    NoEst *atual = lista->primeiro;
    while (1) {
        if (codigo < atual->codigo) {
            if (!atual->esquerda) {
                atual->esquerda = novo;
                novo->pai = atual;
                break;
            }
            atual = atual->esquerda;
        } else if (codigo > atual->codigo) {
            if (!atual->direita) {
                atual->direita = novo;
                novo->pai = atual;
                break;
            }
            atual = atual->direita;
        } else {
            // Já existe esse código: atualiza quantidade e item, libera o novo
            atual->quantidade += quantidade;
            free(novo);
            return atual;
        }
    }

    lista->quantidade++;
    return novo;
}

NoEst* Busca_estoque(ListaEst *lista, int valor) {
    if (!lista || !lista->primeiro) return NULL;

    NoEst *atual = lista->primeiro;
    while (atual) {
        if (valor == atual->codigo) return atual;
        if (valor < atual->codigo)  atual = atual->esquerda;
        else                        atual = atual->direita;
    }
    return NULL;
}

NoEst* maximo_estoque(ListaEst *lista) {
    if (!lista || !lista->primeiro) return NULL;

    NoEst *atual = lista->primeiro;
    while (atual->direita) atual = atual->direita;
    return atual;
}

NoEst* minimo_estoque(ListaEst *lista) {
    if (!lista || !lista->primeiro) return NULL;

    NoEst *atual = lista->primeiro;
    while (atual->esquerda) atual = atual->esquerda;
    return atual;
}

static void liberar_nos(NoEst *no) {
    if (!no) return;
    liberar_nos(no->esquerda);
    liberar_nos(no->direita);
    free(no);
}

void liberar_fila_estoque(ListaEst *lista) {
    if (!lista) return;
    liberar_nos(lista->primeiro);
    free(lista);
}


static void imprimir_no_estoque(NoEst *no) {
    if (no == NULL) return;

    imprimir_no_estoque(no->esquerda);

    printf("Nome: %s  Codigo: %d  Quantidade: %d\n",
           no->item, no->codigo, no->quantidade);

    imprimir_no_estoque(no->direita);
}

void imprimir_estoque(ListaEst *lista) {
    if (lista == NULL || lista->primeiro == NULL) {
        printf("Estoque vazio.\n");
        return;
    }

    imprimir_no_estoque(lista->primeiro);
}

