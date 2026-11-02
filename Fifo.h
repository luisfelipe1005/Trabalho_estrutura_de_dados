#ifndef FIFO_H
#define FIFO_H


typedef struct No {
	int *itens_cod;
	int *itens_quant;
	char *descricao;
	char *solicitante;
	int itens_ped;
	int codigo;
	struct No *proximo;
	
} No;

typedef struct Fifo {
	No *primeiro; // Ponteiro para o primeiro nC3 (excluindo o cabeC'alho)
	No *ultimo; // Ponteiro para o primeiro nC3 (excluindo o cabeC'alho)
	int quantidade;
	int codigo;
} Fifo;





// Função para criar uma nova Lista Simplesmente encadeada
Fifo* criar_fila_fifo();

// Outras operações disponibilizadas pelo nosso TAD
void destruir_fila_fifo(Fifo *fila);

// Acesso
//No *buscar(Fifo *fila, int dado);
//void imprimir_fila(Fifo *fila);
void imprimir_fila_front(Fifo *fila);
int verificar_filavaz_fifo(Fifo *fila);

// Inserção
No *inserir_fim_fifo(Fifo *fila, 	int *itens_cod,	int *itens_quant,	char *descricao,char *solicitante,	int itens_ped, int codigo);

/*No *inserir_inicio(Fifo *fila, int dado);
No *inserir_posicao(Fifo *fila, int dado, int posicao);*/

// Remoção
No remover_inicio_fifo(Fifo *fila);
/*
int remover_fim(Fifo *fila);*/
No remover_esp_fifo(Fifo *fila, int codigo);


//Fusão
/*
void fundir(Fifo *fila1, Fifo *fila2, Fifo *filaf);*/




#endif /* Fifo */
