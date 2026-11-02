#ifndef HISTORICO_H
#define HISTORICO_H

typedef struct NoHis {
    int *itens_cod;
    int *itens_quant;
    char *descricao;
    char *solicitante;
    char *status;
    int itens_ped;
    int codigo;   
    struct NoHis *proximo;
} NoHis;

typedef struct ListaHis {
    NoHis *primeiro; 
    NoHis *ultimo;   
    int quantidade;
} ListaHis;

// Criação / destruição
ListaHis* criar_lista_his();
void destruir_lista_his(ListaHis *lista);

// Acesso
NoHis *buscar_his(ListaHis *lista, int codigo);
void imprimir_lista_his(ListaHis *lista);

// Inserção (Atualizado para receber todos os dados)
NoHis *inserir_inicio_his(ListaHis *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, int qtd, int codigo, char *status);
NoHis *inserir_fim_his(ListaHis *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, int qtd, int codigo, char *status);

// Remoção (Retorna o ID do removido)
int remover_inicio_his(ListaHis *lista);
int remover_fim_his(ListaHis *lista);


#endif /* HISTORICO_H */