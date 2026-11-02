#ifndef BST_TEC_H
#define BST_TEC_H

// Declarações antecipadas
typedef struct NoSer NoSer;
typedef struct ListaSer ListaSer;
typedef struct NoTec NoTec;
typedef struct ListaTec ListaTec;

// ------------------- SERVIÇOS -------------------
struct NoSer {
    int *itens_cod;
    int *itens_quant;
    char *descricao;
    char *solicitante;
    int itens_ped;
    int codigo;
    struct NoSer *proximo;
};

struct ListaSer {
    NoSer *primeiro;
    NoSer *ultimo;
    int quantidade;
};

// ------------------- TÉCNICOS (BST) -------------------
struct NoTec {
    int registro;
    char nome[50];
    NoTec *esquerda;
    NoTec *direita;
    NoTec *pai;
    ListaSer *lista;   
};

struct ListaTec {
    NoTec *primeiro;
    int quantidade;
};

// Criação / destruição da BST de técnicos
ListaTec* criar_lista_tecnico(void);
void liberar_fila_tecnico(ListaTec *fila);

// Operações na BST de técnicos
NoTec* inserir_tecnico(ListaTec *lista, int registro,  char *nome);
NoTec* Busca_tecnico(ListaTec *lista, int valor);
NoTec* maximo_tecnico(ListaTec *lista);
NoTec* minimo_tecnico(ListaTec *lista);
NoTec* encontrar_tecnico_menos_servicos(ListaTec *lista);

// Lista de serviços de cada técnico
ListaSer* criar_lista_tecnico_servico(ListaTec *listaTec, int codigo);

NoSer* inserir_fim_tecnico(
    ListaTec *lista,
    int *itens_cod,
    int *itens_quant,
     char *descricao,
     char *solicitante,
    int itens_ped,
    int codigo
);

void listarServicos_tecnico(NoTec *tec);
NoSer* remover_servico_tecnico(NoTec *tec, int codigo_pedido);

#endif // BST_TEC_H
