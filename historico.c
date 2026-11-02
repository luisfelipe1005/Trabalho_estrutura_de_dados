#include "historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

ListaHis *criar_lista_his() {
    ListaHis *lista = (ListaHis *) malloc(sizeof(ListaHis));
    if (lista == NULL) return NULL;
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->quantidade = 0;
    return lista;
}



NoHis *inserir_inicio_his(ListaHis *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, int qtd, int codigo, char *status) {
       NoHis *novo = (NoHis *) malloc(sizeof(NoHis));
    if (novo == NULL) return NULL;

    novo->itens_cod = (int *) malloc(qtd * sizeof(int));
    novo->itens_quant = (int *) malloc(qtd * sizeof(int));
    novo->descricao = (char *) malloc(500 * sizeof(char));
    novo->solicitante = (char *) malloc(100 * sizeof(char));
    novo->status = (char *) malloc(100 * sizeof(char));

    if (!novo->itens_cod || !novo->itens_quant || !novo->descricao || !novo->solicitante|| !novo->status) {
        if(novo->itens_cod) free(novo->itens_cod);
        if(novo->itens_quant) free(novo->itens_quant);
        if(novo->descricao) free(novo->descricao);
        if(novo->solicitante) free(novo->solicitante);
        if(novo->status) free(novo->status);
        free(novo);
        return NULL;
    }

    novo->itens_ped = qtd;
    novo->codigo = codigo;
    
    memcpy(novo->itens_cod, itens_cod, qtd * sizeof(int));
    memcpy(novo->itens_quant, itens_quant, qtd * sizeof(int));
    
    strncpy(novo->descricao, desc, 499);
    strncpy(novo->status, status, 499);
    
    strncpy(novo->solicitante, solic, 99);
    

    novo->proximo = NULL;

    novo->proximo = lista->primeiro;

    if (lista->primeiro == NULL) {
        lista->ultimo = novo;
    }
    lista->primeiro = novo;
    lista->quantidade++;

    return novo;
}

NoHis *inserir_fim_his(ListaHis *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, int qtd, int codigo, char *status) {
        NoHis *novo = (NoHis *) malloc(sizeof(NoHis));
    if (novo == NULL) return NULL;

    novo->itens_cod = (int *) malloc(qtd * sizeof(int));
    novo->itens_quant = (int *) malloc(qtd * sizeof(int));
    novo->descricao = (char *) malloc(500 * sizeof(char));
    novo->solicitante = (char *) malloc(100 * sizeof(char));
    novo->status = (char *) malloc(100 * sizeof(char));

    if (!novo->itens_cod || !novo->itens_quant || !novo->descricao || !novo->solicitante|| !novo->status) {
        if(novo->itens_cod) free(novo->itens_cod);
        if(novo->itens_quant) free(novo->itens_quant);
        if(novo->descricao) free(novo->descricao);
        if(novo->solicitante) free(novo->solicitante);
        if(novo->status) free(novo->status);
        free(novo);
        return NULL;
    }

    novo->itens_ped = qtd;
    novo->codigo = codigo;
    
    memcpy(novo->itens_cod, itens_cod, qtd * sizeof(int));
    memcpy(novo->itens_quant, itens_quant, qtd * sizeof(int));
    
    strncpy(novo->descricao, desc, 499);
    strncpy(novo->status, status, 499);
    
    strncpy(novo->solicitante, solic, 99);
    

    novo->proximo = NULL;
    if (novo == NULL) return NULL;

    if (lista->primeiro == NULL) {
        lista->primeiro = novo;
        lista->ultimo = novo;
    } else {
        lista->ultimo->proximo = novo;
        lista->ultimo = novo;
    }
    lista->quantidade++;

    return novo;
}

int remover_inicio_his(ListaHis *lista) {
    if (lista->primeiro == NULL) return -1;

    NoHis *removido = lista->primeiro;
    int codigo_salvo = removido->codigo;

    if (lista->primeiro == lista->ultimo) {
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    } else {
        lista->primeiro = lista->primeiro->proximo;
    }

    // Libera memória interna antes de liberar o nó
    free(removido->itens_cod);
    free(removido->itens_quant);
    free(removido->descricao);
    free(removido->solicitante);
    free(removido);

    lista->quantidade--;
    return codigo_salvo;
}

int remover_fim_his(ListaHis *lista) {
    if (lista->primeiro == NULL) return -1;

    NoHis *removido = lista->ultimo;
    int codigo_salvo = removido->codigo;

    if (lista->primeiro == lista->ultimo) {
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    } else {
        NoHis *atual = lista->primeiro;
        while (atual->proximo != lista->ultimo) {
            atual = atual->proximo;
        }
        lista->ultimo = atual;
        atual->proximo = NULL;
    }

    // Libera memória interna
    free(removido->itens_cod);
    free(removido->itens_quant);
    free(removido->descricao);
    free(removido->solicitante);
    free(removido);

    lista->quantidade--;
    return codigo_salvo;
}

void imprimir_lista_his(ListaHis *lista) {
    if (lista->primeiro == NULL) {
        printf("Historico vazio!\n");
        return;
    }
    NoHis *atual = lista->primeiro;
    printf("\n--- HISTORICO DE PEDIDOS ---\n");
    while (atual != NULL) {
        printf("ID: %d | Solicitante: %s | Desc: %s\n", atual->codigo, atual->solicitante, atual->descricao);
       
        printf("   Itens:\n");
        for(int i=0; i<atual->itens_ped; i++){
             printf("   - Cod %d: %d un.\n", atual->itens_cod[i], atual->itens_quant[i]);
        }
        
        atual = atual->proximo;
    }
    printf("----------------------------\n");
}

NoHis *buscar_his(ListaHis *lista, int codigo) {
    NoHis *atual = lista->primeiro;
    while (atual != NULL) {
        if (atual->codigo == codigo) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void destruir_lista_his(ListaHis *lista) {
    if (lista == NULL) return;

    NoHis *atual = lista->primeiro;
    while (atual != NULL) {
        NoHis *anterior = atual;
        atual = atual->proximo;
        
        // Libera tudo recursivamente
        free(anterior->itens_cod);
        free(anterior->itens_quant);
        free(anterior->descricao);
        free(anterior->solicitante);
        free(anterior);
    }
    free(lista);
}