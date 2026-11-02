#include "Fifo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Fifo *criar_fila_fifo() {
	Fifo *fila = (Fifo *) malloc(sizeof(Fifo));
	if (fila == NULL) {
		return NULL; // Falha na alocaC'C#o de memC3ria
	}
	fila->primeiro = NULL;
	fila->ultimo = NULL;
	fila->quantidade=0;
	fila->codigo=0;
	return fila;
}

/*
No *inserir_inicio(Fifo *fila, int dado) {
	fila->quantidade=fila->quantidade+1;
	// Alocar memC3ria para o novo nC3
	No *novo = (No *) malloc(sizeof(No));
	if (novo == NULL) {
		return NULL; // Falha na alocaC'C#o de memC3ria
	}
	// Atribuir valor e inicializar ponteiro 'proximo'
	novo->dado = dado;
	novo->proximo = NULL;
	// Inserir o novo nC3 no inC-cio da fila
	if (fila->primeiro == NULL) {
		// Lista vazia: novo nC3 C) o primeiro e C:ltimo nC3
		fila->primeiro = novo;
		fila->ultimo = novo;
	} else {
		// Lista nC#o vazia: novo nC3 se torna o primeiro nC3
		novo->proximo = fila->primeiro;
		fila->primeiro = novo;
	}
	return novo; // Retornar o ponteiro para o nC3 inserido
}
*/

No *inserir_fim_fifo(Fifo *fila, 	int *itens_cod,	int *itens_quant,	char *descricao,char *solicitante,	int itens_ped, int codigo) {
    
    /*	if(fila->quantidade==0)
		return inserir_inicio(fila, dado);
		else{*/
	fila->quantidade=fila->quantidade+1;
	fila->codigo=fila->codigo+1;
	// Alocar memC3ria para o novo nC3
	No *novo = (No *) malloc(sizeof(No));
    novo->descricao = (char *)malloc(sizeof(char) * 100);
    novo->solicitante = (char *)malloc(sizeof(char) * 50);
	novo->proximo = NULL;
	novo->itens_ped= itens_ped;
	novo->codigo= fila->codigo;
	
	novo->itens_cod = (int *) malloc(itens_ped * sizeof(int));
    novo->itens_quant = (int *) malloc(itens_ped * sizeof(int));
	
	if (novo->itens_cod == NULL || novo->itens_quant == NULL ||
        novo->descricao == NULL || novo->solicitante == NULL ) {
            free(novo);
		return NULL; // Falha na alocaC'C#o de memC3ria
	}	
memcpy(novo->itens_cod, itens_cod, itens_ped * sizeof(int));
    memcpy(novo->itens_quant, itens_quant, itens_ped * sizeof(int));
	strcpy(novo->descricao, descricao);
    strcpy(novo->solicitante, solicitante);


	
    
	// Ino novo nC3 no inC-cio da fila
	if (fila->primeiro == NULL) {
		// Lista vazia: novo nC3 C) o primeiro e C:ltimo nC3
		fila->primeiro = novo;
		
	}
	else{
	// Lista nC#o vazia: novo nC3 se torna o primeiro nC3
	fila->ultimo->proximo = novo;
	}
	fila->ultimo = novo;
printf("Seu codigo de No e: %d\n", novo->codigo);
	return novo; // Retornar o ponteiro para o nC3 inserido
//}
}

/*
No *inserir_posicao(Fifo *fila, int dado, int posicao) {
	if(posicao==1)
		return inserir_inicio(fila, dado);
	else if(posicao==fila->quantidade+1)
		return inserir_fim(fila, dado);
	else {
		fila->quantidade=fila->quantidade+1;
		// Alocar memC3ria para o novo nC3
		No *novo = (No *) malloc(sizeof(No));
		if (novo == NULL) {
			return NULL; // Falha na alocaC'C#o de memC3ria
		}
		// Atribuir valor e inicializar ponteiro 'proximo'
		novo->dado = dado;
		No *atual = fila->primeiro;


		for(int i=1; i<posicao-1; i++) {


			atual = atual->proximo;
		}
		novo->proximo = atual->proximo;
		atual->proximo= novo;

		return novo; // Retornar o ponteiro para o nC3 inserido
	}
}




int remover_fim(Fifo *fila) {
	fila->quantidade=fila->quantidade-1;
	if (fila->primeiro == NULL) {
		return -1; // Lista vazia
	}
	No *removido = fila->ultimo;
	int valor_removido = removido->dado;
	if (fila->primeiro == fila->ultimo) {
		// Cnico nC3: fila fica vazia
		fila->primeiro = NULL;
		fila->ultimo = NULL;
	} else {
		// VC!rios nC3s: atualizar ponteiros
	No *atual = fila->primeiro;
				for(int i=1; i<fila->quantidade; i++) {


			atual = atual->proximo;
		}
		fila->ultimo = atual;
		atual->proximo=NULL;
	}
	free(removido);
	return valor_removido;
}
*/

No remover_inicio_fifo(Fifo *fila) {
    No retorno;

    retorno.codigo = -1;
    retorno.itens_cod = NULL;
    retorno.itens_quant = NULL;
    retorno.descricao = NULL;
    retorno.solicitante = NULL;
    retorno.itens_ped = 0;
    retorno.proximo = NULL;

    if (fila == NULL || fila->primeiro == NULL) {
        return retorno;
    }

    No *no_removido = fila->primeiro;

    retorno.codigo = no_removido->codigo;
    retorno.itens_ped = no_removido->itens_ped;
    retorno.itens_cod = no_removido->itens_cod;
    retorno.itens_quant = no_removido->itens_quant;
    retorno.descricao = no_removido->descricao;
    retorno.solicitante = no_removido->solicitante;

    fila->primeiro = no_removido->proximo;

    if (fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }

    fila->quantidade--;

    free(no_removido);

    return retorno;
}


No remover_esp_fifo(Fifo *fila, int codigo) {
    No retorno;

    retorno.itens_cod    = NULL;
    retorno.itens_quant  = NULL;
    retorno.descricao    = NULL;
    retorno.solicitante  = NULL;
    retorno.itens_ped    = 0;
    retorno.codigo       = -1;
    retorno.proximo      = NULL;

    if (fila == NULL || fila->primeiro == NULL) return retorno;

    No *anterior = NULL;
    No *atual = fila->primeiro;

    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return retorno; // Não achou

    retorno.itens_cod   = atual->itens_cod;
    retorno.itens_quant = atual->itens_quant;
    retorno.itens_ped   = atual->itens_ped;
    retorno.codigo      = atual->codigo;
    retorno.descricao   = atual->descricao;
    retorno.solicitante = atual->solicitante;

    if (atual == fila->primeiro) {
        fila->primeiro = atual->proximo;
        if (fila->primeiro == NULL) fila->ultimo = NULL;
    } else {
        anterior->proximo = atual->proximo;
        if (atual == fila->ultimo) fila->ultimo = anterior;
    }
    fila->quantidade--;

    free(atual);

    return retorno;
}

/*
void imprimir_fila(Fifo *fila) {
	if (fila->primeiro == NULL) {
		printf("Lista vazia!\n");
		return;
	}
	No *atual = fila->primeiro;
	while (atual != NULL) {
		printf("%d ", atual->dado);
		atual = atual->proximo;
	}
	printf("\n");
}*/
void imprimir_fila_front(Fifo *fila) {
	if (fila->primeiro == NULL) {
		printf("Lista vazia!\n");
		return;
	}
	printf ("front: %d",fila->primeiro->codigo);
		
	
	printf("\n");
}

int verificar_filavaz_fifo(Fifo *fila){
    	return ! (fila->primeiro == NULL);
}

void destruir_fila_fifo(Fifo *fila) {
	if (fila->primeiro == NULL) {
		return;
	}
	No *atual = fila->primeiro;
	No *anterior;
	while (atual != NULL) {
		anterior = atual;
		atual = atual->proximo;
	free(anterior->itens_cod);
free(anterior->itens_quant);
free(anterior->descricao);
free(anterior->solicitante);
		free(anterior);
	}
		free(fila);
}


/*
void fundir(Fifo *fila1, Fifo *fila2, Fifo *filaf){
    
    No *atual1 = fila1->primeiro;
    
    
    No *atual2 = fila2->primeiro;
    
    while(atual2!=NULL&&atual1!=NULL){
      
  inserir_fim(filaf, atual1->dado);
  inserir_fim(filaf, atual2->dado);
  atual1=atual1->proximo;
  atual2=atual2->proximo;
    }
    
    while(atual1!=NULL){
      
  inserir_fim(filaf, atual1->dado);
  atual1=atual1->proximo;
    }
    while(atual2!=NULL){
      
  inserir_fim(filaf, atual2->dado);
  atual2=atual2->proximo;
    }
    
    
}
*/