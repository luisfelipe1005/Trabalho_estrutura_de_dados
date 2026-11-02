#include "em_at.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Listaatt *criar_lista_att() {
    Listaatt *lista = (Listaatt *) malloc(sizeof(Listaatt));
    if (lista == NULL) return NULL;
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->quantidade = 0;
    return lista;
}

static Noatt* criar_no_att(int *itens_cod, int *itens_quant, char *desc, char *solic, char *status, int qtd, int codigo) {
    Noatt *novo = (Noatt *) malloc(sizeof(Noatt));
    if (novo == NULL) return NULL;

    novo->itens_cod = (int *) malloc(qtd * sizeof(int));
    novo->itens_quant = (int *) malloc(qtd * sizeof(int));
    novo->descricao = (char *) malloc(500 * sizeof(char));
    novo->solicitante = (char *) malloc(100 * sizeof(char));
    novo->status = (char *) malloc(50 * sizeof(char));

    if (!novo->itens_cod || !novo->itens_quant || !novo->descricao || !novo->solicitante || !novo->status) {
        if(novo->itens_cod) free(novo->itens_cod);
        if(novo->itens_quant) free(novo->itens_quant);
        if(novo->descricao) free(novo->descricao);
        if(novo->solicitante) free(novo->solicitante);
        if(novo->status) free(novo->status);
        free(novo);
        return NULL;
    }

    memcpy(novo->itens_cod, itens_cod, qtd * sizeof(int));
    memcpy(novo->itens_quant, itens_quant, qtd * sizeof(int));
    
    strncpy(novo->descricao, desc, 499);
    novo->descricao[499] = '\0';
    
    strncpy(novo->solicitante, solic, 99);
    novo->solicitante[99] = '\0';

    strncpy(novo->status, status, 49);
    novo->status[49] = '\0';

    novo->itens_ped = qtd;
    novo->codigo = codigo;
    novo->anterior = NULL;
    novo->proximo = NULL;

    return novo;
}

Noatt *inserir_inicio_att(Listaatt *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, char *status, int qtd, int codigo) {
    Noatt *novo = criar_no_att(itens_cod, itens_quant, desc, solic, status, qtd, codigo);
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

Noatt *inserir_fim_att(Listaatt *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, char *status, int qtd, int codigo) {
    if (lista->primeiro == NULL) {
        return inserir_inicio_att(lista, itens_cod, itens_quant, desc, solic, status, qtd, codigo);
    }

    Noatt *novo = criar_no_att(itens_cod, itens_quant, desc, solic, status, qtd, codigo);
    if (novo == NULL) return NULL;

    novo->anterior = lista->ultimo;
    lista->ultimo->proximo = novo;
    lista->ultimo = novo;
    lista->quantidade++;

    return novo;
}

int remover_inicio_att(Listaatt *lista) {
    if (lista->primeiro == NULL) return -1;

    Noatt *removido = lista->primeiro;
    int codigo_salvo = removido->codigo;

    if (lista->primeiro == lista->ultimo) {
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    } else {
        lista->primeiro = lista->primeiro->proximo;
        lista->primeiro->anterior = NULL;
    }

    free(removido->itens_cod);
    free(removido->itens_quant);
    free(removido->descricao);
    free(removido->solicitante);
    free(removido->status);
    free(removido);

    lista->quantidade--;
    return codigo_salvo;
}

int remover_fim_att(Listaatt *lista) {
    if (lista->primeiro == NULL) return -1;

    Noatt *removido = lista->ultimo;
    int codigo_salvo = removido->codigo;

    if (lista->primeiro == lista->ultimo) {
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    } else {
        lista->ultimo = removido->anterior;
        lista->ultimo->proximo = NULL;
    }

    free(removido->itens_cod);
    free(removido->itens_quant);
    free(removido->descricao);
    free(removido->solicitante);
    free(removido->status);
    free(removido);

    lista->quantidade--;
    return codigo_salvo;
}

int remover_posicao_att(Listaatt *lista, int posicao) {
    if (lista->primeiro == NULL || posicao < 1 || posicao > lista->quantidade) {
        return -1;
    }

    if (posicao == 1) return remover_inicio_att(lista);
    if (posicao == lista->quantidade) return remover_fim_att(lista);

    Noatt *atual = lista->primeiro;
    for (int i = 1; i < posicao - 1; i++) {
        atual = atual->proximo;
    }

    Noatt *removido = atual->proximo;
    int codigo_salvo = removido->codigo;

    atual->proximo = removido->proximo;
    if (removido->proximo != NULL) {
        removido->proximo->anterior = atual;
    }

    free(removido->itens_cod);
    free(removido->itens_quant);
    free(removido->descricao);
    free(removido->solicitante);
    free(removido->status);
    free(removido);

    lista->quantidade--;
    return codigo_salvo;
}

void imprimir_lista_att(Listaatt *lista, Direcao_att dir) {
    if (lista->primeiro == NULL) {
        printf("Lista de atendimento vazia!\n");
        return;
    }

    if (dir == INICIO_ATT) {
        Noatt *atual = lista->primeiro;
        while (atual != NULL) {
            printf("[ID: %d | Status: %s | Solicitante: %s] -> ", atual->codigo, atual->status, atual->solicitante);
            atual = atual->proximo;
        }
    } else {
        Noatt *atual = lista->ultimo;
        while (atual != NULL) {
            printf("[ID: %d | Status: %s] -> ", atual->codigo, atual->status);
            atual = atual->anterior;
        }
    }
    printf("NULL\n");
}

Noatt *buscar_att(Listaatt *lista, int codigo) {
    Noatt *atual = lista->primeiro;
    while (atual != NULL) {
        if (atual->codigo == codigo) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void destruir_lista_att(Listaatt *lista) {
    if (lista == NULL) return;

    Noatt *atual = lista->primeiro;
    while (atual != NULL) {
        Noatt *proximo = atual->proximo;
        
        free(atual->itens_cod);
        free(atual->itens_quant);
        free(atual->descricao);
        free(atual->solicitante);
        free(atual->status);
        free(atual);

        atual = proximo;
    }
    free(lista);
}



void remover_att_por_no(Listaatt *lista, Noatt *no) {
    if (lista == NULL || no == NULL) return;

    if (no == lista->primeiro) {
        lista->primeiro = no->proximo;
    }
    if (no == lista->ultimo) {
        lista->ultimo = no->anterior;
    }
    if (no->anterior != NULL) {
        no->anterior->proximo = no->proximo;
    }
    if (no->proximo != NULL) {
        no->proximo->anterior = no->anterior;
    }

    lista->quantidade--;

    free(no->itens_cod);
    free(no->itens_quant);
    free(no->descricao);
    free(no->solicitante);
    free(no->status);
    free(no);
}
