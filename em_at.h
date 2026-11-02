#ifndef EM_AT_H
#define EM_AT_H

typedef struct Noatt {
    int *itens_cod;
    int *itens_quant;
    char *descricao;
    char *solicitante;
    char *status;      
    int itens_ped;
    int cod_tecnico;      
    int codigo;         
    struct Noatt *anterior; 
    struct Noatt *proximo;  
} Noatt;

typedef struct Listaatt {
    Noatt *primeiro; 
    Noatt *ultimo;   
    int quantidade;
} Listaatt;

typedef enum {
    INICIO_ATT,
    FIM_ATT
} Direcao_att;

// Criação / destruição
Listaatt* criar_lista_att();
void destruir_lista_att(Listaatt *lista);

// Acesso
Noatt *buscar_att(Listaatt *lista, int codigo);
void imprimir_lista_att(Listaatt *lista, Direcao_att dir);

// Inserção (Atualizado com todos os campos)
Noatt *inserir_inicio_att(Listaatt *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, char *status, int qtd, int codigo);
Noatt *inserir_fim_att(Listaatt *lista, int *itens_cod, int *itens_quant, char *desc, char *solic, char *status, int qtd, int codigo);

// Remoção (Retorna o ID do removido)
int remover_inicio_att(Listaatt *lista);
int remover_fim_att(Listaatt *lista);
int remover_posicao_att(Listaatt *lista, int posicao); 
void remover_att_por_no(Listaatt *lista, Noatt *no);

#endif /* EM_AT_H */