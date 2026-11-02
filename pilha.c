#include "pilha.h"
#include <stdlib.h>

Pilha *criar_pilha() {
    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    if (pilha == NULL) {
        return NULL; // Falha na alocação
    }
    pilha->topo = NULL;
    pilha->quantidade = 0;
    return pilha;
}

// PUSH: empilha uma função de tela
NoPilha *inserir_inicio(Pilha *pilha, FuncaoTela func) {
    if (pilha == NULL) return NULL;

    NoPilha *novo = (NoPilha *) malloc(sizeof(NoPilha));
    if (novo == NULL) {
        return NULL; // Falha na alocação
    }

    novo->func = func;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->quantidade++;

    return novo;
}

// POP: remove o topo e retorna a função
FuncaoTela remover_fim(Pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        return NULL; // Pilha vazia
    }

    NoPilha *removido = pilha->topo;
    FuncaoTela func_removida = removido->func;

    pilha->topo = removido->proximo;
    pilha->quantidade--;

    free(removido);
    return func_removida;
}

// Retorna a função no topo, sem desempilhar
FuncaoTela topo_pilha(Pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        return NULL;
    }
    return pilha->topo->func;
}

// 0 = vazia, 1 = tem algo
int verificar_pilhavaz(Pilha *pilha) {
    if (pilha == NULL) return 0;
    return (pilha->topo != NULL);
}

void destruir_pilha(Pilha *pilha) {
    if (pilha == NULL) return;

    NoPilha *atual = pilha->topo;
    while (atual != NULL) {
        NoPilha *prox = atual->proximo;
        free(atual);
        atual = prox;
    }

    free(pilha);
}
