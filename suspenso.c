#include "suspenso.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ListaSus *criar_lista_sus() {
    ListaSus *lista = (ListaSus *) malloc(sizeof(ListaSus));
    if (lista == NULL) return NULL;
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->quantidade = 0;
    return lista;
}

static Nosus* criar_no_sus(int *itens_cod, int *itens_quant, char *desc, char *solic, int qtd, int codigo) {
    Nosus *novo = (Nosus *) malloc(sizeof(Nosus));
    if (novo == NULL) return NULL;

    novo->itens_cod = (int *) malloc(qtd * sizeof(int));
    novo->itens_quant = (int *) malloc(qtd * sizeof(int));
    novo->descricao = (char *) malloc(500 * sizeof(char));
    novo->solicitante = (char *) malloc(100 * sizeof(char));

    if (!novo->itens_cod || !novo->itens_quant || !novo->descricao || !novo->solicitante) {
        if(novo->itens_cod) free(novo->itens_cod);
        if(novo->itens_quant) free(novo->itens_quant);
        if(novo->descricao) free(novo->descricao);
        if(novo->solicitante) free(novo->solicitante);
        free(novo);
        return NULL;
    }

    memcpy(novo->itens_cod, itens_cod, qtd * sizeof(int));
    memcpy(novo->itens_quant, itens_quant, qtd * sizeof(int));
    strncpy(novo->descricao, desc, 499);
    novo->descricao[499] = '\0';
    strncpy(novo->solicitante, solic, 99);
    novo->solicitante[99] = '\0';

    novo->itens_ped = qtd;
    novo->codigo = codigo;
    novo->anterior = NULL;
    novo->proximo = NULL;

    return novo;
}

Nosus *inserir_inicio_sus(ListaSus *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, int qtd, int codigo) {
    Nosus *novo = criar_no_sus(itens_cod, itens_quant, desc, solic, qtd, codigo);
    if (novo == NULL) return NULL;

    novo->proximo = lista->primeiro;
    
    if (lista->primeiro == NULL) {
        lista->ultimo = novo;
    } else {
        lista->primeiro->anterior = novo;
    }

    lista->primeiro = novo;
    lista->quantidade++;
    return novo;
}

Nosus *inserir_fim_sus(ListaSus *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, int qtd, int codigo) {
    Nosus *novo = criar_no_sus(itens_cod, itens_quant, desc, solic, qtd, codigo);
    if (novo == NULL) return NULL;

    novo->anterior = lista->ultimo;

    if (lista->primeiro == NULL) {
        lista->primeiro = novo;
    } else {
        lista->ultimo->proximo = novo;
    }

    lista->ultimo = novo;
    lista->quantidade++;
    return novo;
}

Nosus *remover_posicao_sus(ListaSus *lista, int codigo) {
    if (lista->primeiro == NULL) return NULL;

    Nosus *atual = lista->primeiro;

    while (atual != NULL && atual->codigo != codigo) {
        atual = atual->proximo;
    }

    if (atual == NULL) return NULL;

    if (atual == lista->primeiro) {
        lista->primeiro = atual->proximo;
        if (lista->primeiro) {
            lista->primeiro->anterior = NULL;
        } else {
            lista->ultimo = NULL; // Lista ficou vazia
        }
    } else if (atual == lista->ultimo) {
        lista->ultimo = atual->anterior;
        lista->ultimo->proximo = NULL;
    } else {
        // Nó no meio
        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;
    }

    lista->quantidade--;
    
    atual->proximo = NULL;
    atual->anterior = NULL;

    return atual; // Retorna o nó inteiro
}

Nosus *buscar_sus(ListaSus *lista, int codigo) {
    if (lista->primeiro == NULL) return NULL;
    
    Nosus *atual = lista->primeiro;
    while (atual != NULL) {
        if (atual->codigo == codigo) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void imprimir_lista_sus(ListaSus *lista, Direcao dir) {
    if (lista->primeiro == NULL) {
        printf("Lista de suspensos vazia!\n");
        return;
    }

    if (dir == INICIO_SUS) {
        Nosus *atual = lista->primeiro;
        while (atual != NULL) {
            printf("[ID: %d | %s] -> ", atual->codigo, atual->solicitante);
            atual = atual->proximo;
        }
    } else {
        Nosus *atual = lista->ultimo;
        while (atual != NULL) {
            printf("[ID: %d | %s] -> ", atual->codigo, atual->solicitante);
            atual = atual->anterior;
        }
    }
    printf("NULL\n");
}

void destruir_lista_sus(ListaSus *lista) {
    if (lista == NULL) return;

    Nosus *atual = lista->primeiro;
    while (atual != NULL) {
        Nosus *proximo = atual->proximo;
        
        // Libera memória interna
        free(atual->itens_cod);
        free(atual->itens_quant);
        free(atual->descricao);
        free(atual->solicitante);
        free(atual); // Libera o nó

        atual = proximo;
    }
    free(lista);
}