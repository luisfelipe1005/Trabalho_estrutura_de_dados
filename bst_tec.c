#include "bst_tec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void trocar(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}



ListaTec* criar_lista_tecnico() {
  ListaTec *lista = (ListaTec *) malloc(sizeof(ListaTec));
  if (lista == NULL) {
    return NULL; // Memory allocation failure
  }
  lista->primeiro = NULL;
  lista->quantidade=0;
  return lista;
}


NoTec *inserir_tecnico(ListaTec *lista, int registro, char *nome) {
  NoTec *novo = (NoTec *) malloc(sizeof(NoTec));
  if (novo == NULL) {
    return NULL; // Memory allocation failure
  }
  novo->registro = registro;
		strcpy(novo->nome, nome);
  novo->pai = NULL;
  novo->esquerda = NULL;
  novo->direita = NULL;
if(lista->primeiro==NULL) lista->primeiro=novo;

else{
   
       	NoTec *atual = lista->primeiro;
   while(1){
       if(atual->registro>novo->registro){
           if(atual->esquerda==NULL){
               atual->esquerda=novo;
               novo->pai=atual;
               break;
           }
           
           atual=atual->esquerda;
       }
       else if(atual->registro<novo->registro){
                      if(atual->direita==NULL){
               atual->direita=novo;
               novo->pai=atual;
               break;
           }
           atual=atual->direita;
       }
       else{
           
        free(novo);
                return atual;
                //Impede que tenham registros iguais

       }
       
   }
}
  

    lista->quantidade++;
  return novo;
}



NoTec* Busca_tecnico(ListaTec *lista, int valor){
    if(lista->primeiro==NULL) return NULL;
    
       	NoTec *atual = lista->primeiro;
       	while(atual!= NULL){
       	if(atual->registro==valor) return atual;
       	
       else if(atual->registro>valor) atual=atual->esquerda;
       
       else atual=atual->direita;
       	}
       	
       	return NULL;
       	
}


NoTec* maximo_tecnico(ListaTec *lista){
    if(lista->primeiro==NULL) return NULL;
    
       	NoTec *atual = lista->primeiro;
       	while(atual->direita!= NULL) atual=atual->direita;
       	
       	return atual;
       	
}


NoTec* minimo_tecnico(ListaTec *lista){
    if(lista->primeiro==NULL) return NULL;
    
       	NoTec *atual = lista->primeiro;
       	while(atual->esquerda!= NULL) atual=atual->esquerda;
       	
       	return atual;
       	
}


//funções envolvendo a lista de serviços:
ListaSer *criar_lista_tecnico_servico(ListaTec *listaTec, int codigo) {
    
	NoTec *tecnico = Busca_tecnico(listaTec, codigo);
 if (tecnico == NULL) {
     printf("Não achado tecnico");
    return NULL; // Memory allocation failure
  }
    
    
  if(tecnico->lista==NULL){
           tecnico->lista = malloc(sizeof(ListaSer));
        tecnico->lista->primeiro = NULL;
        tecnico->lista->ultimo = NULL;
        tecnico->lista->quantidade = 0;
  }
  return tecnico->lista;
}


NoSer *inserir_fim_tecnico(ListaTec *lista, 	int *itens_cod,	int *itens_quant,	char *descricao,char *solicitante,	int itens_ped, int codigo) {
    	NoTec *tecnico = Busca_tecnico(lista, codigo);
    	if (tecnico == NULL) {
     printf("Não achado tecnico");
    return NULL; // Memory allocation failure
  }
  
  if (tecnico->lista == NULL) {
     printf("Não achado tecnico");
    return NULL; // Memory allocation failure
  }
    /*	if(lista->quantidade==0)
		return inserir_inicio(lista, dado);
		else{*/
		
		NoSer *novo = malloc(sizeof(NoSer));
if (!novo) return NULL;
	tecnico->lista->quantidade++;
	// Alocar memC3ria para o novo nC3
	novo->proximo = NULL;
	novo->itens_ped= itens_ped;
	novo->codigo= codigo;

	
	
	novo->itens_cod = (int *) malloc(itens_ped * sizeof(int));
    novo->itens_quant = (int *) malloc(itens_ped * sizeof(int));
    
    
    novo->descricao = (char *) malloc((strlen(descricao) + 1) * sizeof(char));
    novo->solicitante = (char *) malloc((strlen(solicitante) + 1) * sizeof(char));
    
    
    	
	if (novo->itens_cod == NULL || novo->itens_quant == NULL ||
        novo->descricao == NULL || novo->solicitante == NULL) {
		return NULL; // Falha na alocaC'C#o de memC3ria
	}
	
	memcpy(novo->itens_cod, itens_cod, itens_ped * sizeof(int));
    memcpy(novo->itens_quant, itens_quant, itens_ped * sizeof(int));
	strcpy(novo->descricao, descricao);
    strcpy(novo->solicitante, solicitante);
	if (tecnico->lista->primeiro == NULL) {
		tecnico->lista->primeiro = novo;
		
	}
	else{
	tecnico->lista->ultimo->proximo = novo;
	}
	tecnico->lista->ultimo = novo;

	return novo; // Retornar o ponteiro para o nC3 inserido
//}
}



void listarServicos_tecnico(NoTec *tec) {
    ListaSer *lista = tec->lista;
      if (lista == NULL || lista->primeiro == NULL) {
        printf("Nenhum serviço encontrado para o técnico\n");
        return;
    }
NoSer *s = lista->primeiro;
    printf("Serviços do técnico %s:\n", tec->nome);

    while (s != NULL) {
               printf(" - Código: %d, Descrição: %s, Solicitante: %s, Itens pedidos: %d\n", 
               s->codigo, s->descricao, s->solicitante, s->itens_ped);

        if (s->itens_cod != NULL && s->itens_quant != NULL) {
            for (int i = 0; i < s->itens_ped; i++) {
                printf("    Item %d - Código: %d, Quantidade: %d\n", 
                       i + 1, s->itens_cod[i], s->itens_quant[i]);
            }
        }
        s = s->proximo;
    }
}

void liberar_fila_tecnico(ListaTec *fila) {
    NoTec *atual = fila->primeiro;
    while (atual != NULL) {
        NoTec *temp = atual;
        atual = atual->direita;
        free(temp);
    }
    free(fila);
}

NoSer* remover_servico_tecnico(NoTec *tec, int codigo_pedido) {
    if (tec == NULL) {
        return NULL;
    }

    NoSer *rem = remover_servico_tecnico(tec->esquerda, codigo_pedido);
    if (rem != NULL) return rem;

    if (tec->lista != NULL) {
        ListaSer *lista = tec->lista;
        NoSer *anterior = NULL;
        NoSer *atual = lista->primeiro;

        while (atual != NULL && atual->codigo != codigo_pedido) {
            anterior = atual;
            atual = atual->proximo;
        }

        if (atual != NULL) {
            if (anterior == NULL) {
                lista->primeiro = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            if (lista->ultimo == atual) {
                lista->ultimo = anterior;
            }

            lista->quantidade--;

            atual->proximo = NULL;
            return atual;
        }
    }

    return remover_servico_tecnico(tec->direita, codigo_pedido);
}




static void encontrar_tecnico_menos_servicos_rec(NoTec *no, NoTec **melhor, int *menor) {
    if (no == NULL) return;

    int qtd = 0;
    if (no->lista != NULL) {
        qtd = no->lista->quantidade;
    }

    if (*melhor == NULL || qtd < *menor) {
        *melhor = no;
        *menor = qtd;
    }

    encontrar_tecnico_menos_servicos_rec(no->esquerda, melhor, menor);
    encontrar_tecnico_menos_servicos_rec(no->direita, melhor, menor);
}

NoTec* encontrar_tecnico_menos_servicos(ListaTec *lista) {
    if (lista == NULL || lista->primeiro == NULL) {
        return NULL;
    }

    NoTec *melhor = NULL;
    int menor = 0;
    encontrar_tecnico_menos_servicos_rec(lista->primeiro, &melhor, &menor);
    return melhor;
}

