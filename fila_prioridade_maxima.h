#ifndef FILA_PRIORIDADE_MAXIMA_H
#define FILA_PRIORIDADE_MAXIMA_H

#define MAX_ITENS_PEDIDO 50

typedef struct {
    int itens_cod[MAX_ITENS_PEDIDO];   
    int itens_quan[MAX_ITENS_PEDIDO]; 
    int qtd_tipos_itens;             
    char desc[500];                   
    char solicitante[100];             
    int codigo;                      
    int prioridade;                       
} Pedido;

typedef struct {
    Pedido *dados;  
    int capacidade; 
    int tamanho;    
} FilaPrioridadeMaxima;

FilaPrioridadeMaxima* criar_fila_prioridade_maxima(int capacidade);

void inserir_prior_filamax(FilaPrioridadeMaxima *fila,
                           int itens_cod[],
                           int itens_quan[],
                           char desc[],
                           char solicitante[],
                           int qtd,
                           int codigo, int prioridade);

Pedido extrair_maximo(FilaPrioridadeMaxima *fila);

Pedido extrair_esp(FilaPrioridadeMaxima *fila, int codigo);

Pedido buscar_fila(FilaPrioridadeMaxima *fila, int codigo) ;

void liberar_fila_filamax(FilaPrioridadeMaxima *fila);

int fila_posui_valor_filamax(FilaPrioridadeMaxima *fila);

void imprimir_fila_filamax(FilaPrioridadeMaxima *fila);

#endif // FILA_PRIORIDADE_MAXIMA_H
