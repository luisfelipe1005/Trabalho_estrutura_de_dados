#include "fila_prioridade_maxima.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




static void trocar(Pedido *a, Pedido *b) {
	Pedido temp = *a;
	*a = *b;
	*b = temp;
}


static void arrumar_acima_filamax(FilaPrioridadeMaxima *fila, int indice) {
if(indice==0){
    return;
}
	

	//pai

	if(fila->dados[indice].prioridade>fila->dados[(indice-1)/2].prioridade && indice > 0 ){

	

    	trocar(&fila->dados[indice],&fila->dados[(indice-1)/2]);

    	arrumar_acima_filamax( fila,  (indice-1)/2);

	}

}


static void arrumar_abaixo_filamax(FilaPrioridadeMaxima *fila, int indice) {
int maior=indice;

//esquerda
if(indice*2+1<fila->tamanho && fila->dados[maior].prioridade<fila->dados[(indice*2+1)].prioridade)
maior=(indice*2+1);

//direita
if(indice*2+2<fila->tamanho && fila->dados[maior].prioridade<fila->dados[(indice*2)+2].prioridade)
maior=(indice*2)+2;




if(maior!=indice){
    trocar(&fila->dados[indice], &fila->dados[maior]);
    arrumar_abaixo_filamax(fila, maior);
}

	

}

FilaPrioridadeMaxima* criar_fila_prioridade_maxima(int capacidade) {
	FilaPrioridadeMaxima *fila = (FilaPrioridadeMaxima*)malloc(sizeof(FilaPrioridadeMaxima));
	fila->dados = malloc(capacidade * sizeof(Pedido));
	fila->capacidade = capacidade;
	fila->tamanho = 0;
	return fila;
}

void inserir_prior_filamax(FilaPrioridadeMaxima *fila, 	int itens_cod[],int itens_quan[],char desc[],char solicitante[],int qtd, int codigo, int prioridade) {
	if (fila->tamanho == fila->capacidade) {
        fila->capacidade *= 2;
        fila->dados = realloc(fila->dados, fila->capacidade * sizeof(Pedido));
	}

	fila->tamanho++;
	int i = fila->tamanho - 1;
	fila->dados[i].qtd_tipos_itens= qtd;
	
memcpy(fila->dados[i].itens_cod, itens_cod, fila->dados[i].qtd_tipos_itens * sizeof(int));
    memcpy(fila->dados[i].itens_quan, itens_quan, fila->dados[i].qtd_tipos_itens * sizeof(int));
	
    

		strncpy(fila->dados[i].desc, desc,499);
    strncpy(fila->dados[i].solicitante, solicitante,99);
	fila->dados[i].codigo=codigo;
	fila->dados[i].prioridade=prioridade;
	printf("O codigo do seu pedido é: %d", codigo);
	arrumar_acima_filamax(fila, i);
}

Pedido extrair_maximo(FilaPrioridadeMaxima *fila) {
	if (fila->tamanho == 0) {
		printf("Underflow do heap\n");
		Pedido erro;
        erro.codigo = -1; 
        return erro;
	}

	Pedido maximo = fila->dados[0];
	fila->dados[0] = fila->dados[fila->tamanho - 1];
	fila->tamanho--;
	arrumar_abaixo_filamax(fila, 0);

	return maximo;
}
Pedido buscar_fila(FilaPrioridadeMaxima *fila, int codigo) {
    
int a=0;
	while(a<fila->tamanho && fila->dados[a].codigo != codigo ) a++;
	if (a == fila->tamanho) {
        printf("Item nao encontrado!\n");
        Pedido erro;
        erro.codigo = -1;
        return erro;
    }
	Pedido atual = fila->dados[a];
	return atual;
}

Pedido extrair_esp(FilaPrioridadeMaxima *fila, int codigo) {
	if (fila->tamanho == 0) {
		printf("Underflow do heap\n");
		Pedido erro;
        erro.codigo = -1; 
        return erro;
	}
int a=0;
	while(a<fila->tamanho && fila->dados[a].codigo != codigo ) a++;
	if (a == fila->tamanho) {
        printf("Item nao encontrado!\n");
        Pedido erro;
        erro.codigo = -1;
        return erro;
    }
	Pedido atual = fila->dados[a];
	fila->dados[a] = fila->dados[fila->tamanho - 1];
	fila->tamanho--;
	arrumar_abaixo_filamax(fila, a);
	arrumar_acima_filamax(fila, a);

	return atual;
}

void liberar_fila_filamax(FilaPrioridadeMaxima *fila) {
	free(fila->dados);
	free(fila);
}


void imprimir_fila_filamax(FilaPrioridadeMaxima *fila) {
	for(int i=0;i<fila->tamanho;i++){
	  printf("Solicitante do pedido: %s ", fila->dados[i].solicitante);
	  printf("Descrição do pedido: %s ", fila->dados[i].desc);
	   printf("Itens solicitados:");
	  for(int j=0;j<fila->dados[i].qtd_tipos_itens;j++){
	  printf("Item codigo %d ", fila->dados[i].itens_cod[j]);
	  printf("Quantidade desse item: %d \n", fila->dados[i].itens_quan[j]);
	  }
	} 
}


int fila_posui_valor_filamax(FilaPrioridadeMaxima *fila){
    return (fila->tamanho!=0);
}