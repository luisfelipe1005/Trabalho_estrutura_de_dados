#ifndef PILHA_H
#define PILHA_H

// Ponteiro para função de tela
typedef void (*FuncaoTela)(void);

// Nó da pilha
typedef struct NoPilha {
    FuncaoTela func;
    struct NoPilha *proximo;
} NoPilha;

// Estrutura da pilha
typedef struct Pilha {
    NoPilha *topo;   // Ponteiro para o topo da pilha
    int quantidade;
} Pilha;

// Criação / destruição
Pilha* criar_pilha();
void destruir_pilha(Pilha *pilha);

// Acesso
FuncaoTela topo_pilha(Pilha *pilha);
int verificar_pilhavaz(Pilha *pilha);   // 0 = vazia, 1 = tem algo

// Inserção (push)
NoPilha* inserir_inicio(Pilha *pilha, FuncaoTela func);

// Remoção (pop)
FuncaoTela remover_fim(Pilha *pilha);

#endif /* PILHA_H */
