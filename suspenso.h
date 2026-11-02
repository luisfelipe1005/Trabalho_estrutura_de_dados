#ifndef SUSPENSO_H
#define SUSPENSO_H

typedef struct Nosus {
    int *itens_cod;
    int *itens_quant;
    char *descricao;
    char *solicitante;
    int itens_ped;   
    int codigo;     
    struct Nosus *anterior;
    struct Nosus *proximo;
} Nosus;

typedef struct ListaSus {
    Nosus *primeiro;
    Nosus *ultimo;
    int quantidade;
} ListaSus;

typedef enum {
    INICIO_SUS, FIM_SUS
} Direcao;

// Criação e Destruição
ListaSus* criar_lista_sus();
void destruir_lista_sus(ListaSus *lista);

// Acesso
Nosus *buscar_sus(ListaSus *lista, int codigo);
void imprimir_lista_sus(ListaSus *lista, Direcao dir);

// Inserção (Copia os dados para dentro da lista)
Nosus *inserir_inicio_sus(ListaSus *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, int qtd, int codigo);
Nosus *inserir_fim_sus(ListaSus *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, int qtd, int codigo);

// Remoção
Nosus *remover_posicao_sus(ListaSus *lista, int codigo); 

#endif /* SUSPENSO_H */