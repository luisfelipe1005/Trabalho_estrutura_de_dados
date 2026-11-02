#ifndef BST_ESTH
#define BST_ESTH

// Forward declaration
typedef struct NoEst NoEst;

// Nó da árvore de estoque
struct NoEst {
    int codigo;
    char item[50];
    int quantidade;

    NoEst *esquerda;
    NoEst *direita;
    NoEst *pai;
};

// Estrutura que guarda a raiz e a quantidade
typedef struct ListaEst {
    NoEst *primeiro;   // Raiz da BST
    int quantidade;
} ListaEst;

// Criação / destruição
ListaEst* criar_lista_estoque();
void liberar_fila_estoque(ListaEst *lista);  

// Inserção / busca
NoEst* inserir_estoque(ListaEst *lista, int codigo, char *item, int quantidade);
NoEst* Busca_estoque(ListaEst *lista, int valor);

// Mínimo / máximo
NoEst* maximo_estoque(ListaEst *lista);
NoEst* minimo_estoque(ListaEst *lista);

// Remoção de um item pelo código
void delecao_estoque(ListaEst *lista, int codigo);


void imprimir_estoque(ListaEst *lista);

#endif // BST_ESTH
