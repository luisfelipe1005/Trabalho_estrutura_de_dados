#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fifo.h"
#include "pilha.h"
#include "fila_prioridade_maxima.h"
#include "bst_tec.h"
#include "bst_est.h"
#include "suspenso.h"
#include "historico.h"
#include "em_at.h"


Fifo *fila_normal           = NULL;
FilaPrioridadeMaxima *fila_urgente = NULL;
ListaTec *tecnicos          = NULL;
ListaEst *estoque           = NULL;
ListaSus *suspensos         = NULL;
Listaatt *em_atendimento    = NULL;
ListaHis *historico         = NULL;

Pilha *telas = NULL;


int contador =0;

// Prototipos das telas

void tela_abertura(void);
void tela_atendimento(void);
void tela_estoque(void);
void tela_cancelamento(void);
void tela_encerramento(void);

// FunC'C#o de menu principal

int main(void) {
	 fila_normal = criar_fila_fifo();

	fila_urgente   = criar_fila_prioridade_maxima(10);
	 tecnicos = criar_lista_tecnico();
	estoque        = criar_lista_estoque();
	suspensos      = criar_lista_sus();
	em_atendimento = criar_lista_att();
	historico      = criar_lista_his();
	telas          = criar_pilha();

	if (!fila_normal || !fila_urgente || !tecnicos || !estoque ||
	        !suspensos || !em_atendimento || !historico || !telas) {
		printf("Erro ao inicializar estruturas.\n");
		return 1;
	}
	if (tecnicos) {
        inserir_tecnico(tecnicos, 1, "luis");
        inserir_tecnico(tecnicos, 2, "felipe");
        inserir_tecnico(tecnicos, 3, "jonas");
    }
	int escolha = -1;
//teste de ver se as estruturas existem, e a criação de 3 tecnicos
	while (1) {
		printf("\n===== MENU PRINCIPAL =====\n");
		printf("1: Processo de abertura de chamado\n");
		printf("2: Processo de atendimento de chamado\n");
		printf("3: Processo para adicionar itens no estoque\n");
		printf("4: Processo de cancelamento de chamado\n");
		printf("5: Processo de encerramento de chamado\n");
		printf("6: Voltar tela (pilha)\n");
		printf("0: Fechar sistema\n");
		printf("Escolha: ");
		scanf("%d", &escolha);

		if (escolha == 0) {
			printf("Fechando sistema...\n");
			break;
		}

		switch (escolha) {
		case 1:
			inserir_inicio(telas, tela_abertura);
			tela_abertura();
			break;
		case 2:
			inserir_inicio(telas, tela_atendimento);
			tela_atendimento();
			break;
		case 3:
			inserir_inicio(telas, tela_estoque);
			tela_estoque();
			break;
		case 4:
			inserir_inicio(telas, tela_cancelamento);
			tela_cancelamento();
			break;
			
					case 5:
			inserir_inicio(telas, tela_encerramento);
			tela_encerramento();
			break;
			
			
		case 6: {
			FuncaoTela anterior = remover_fim(telas);
			if (anterior != NULL) {
				anterior();
			} else {
				printf("Nenhuma tela anterior na pilha.\n");
			}
			break;
		}
		default:
			printf("Opcao invalida.\n");
			break;
		}
	}


//A pilha das funções é selecionada por um switch case que chama as funções 
	// LiberaC'C#o das estruturas
	liberar_fila_filamax(fila_urgente);
	destruir_fila_fifo(fila_normal);
	liberar_fila_tecnico(tecnicos);
	liberar_fila_estoque(estoque);
	destruir_lista_sus(suspensos);
	destruir_lista_att(em_atendimento);
	destruir_lista_his(historico);
	destruir_pilha(telas);
	
	return 0;
}


void tela_abertura(void) {
    printf("\n=== Tela: Processo de abertura de chamado ===\n");
    contador++;
    int eh_urgente;
    printf("O chamado e urgente? (1 = sim, 0 = nao): ");
    scanf("%d", &eh_urgente);

    int n;
    printf("Deseja solicitar quantos tipos de itens? ");
    scanf("%d", &n);

    imprimir_estoque(estoque);

    // Aloca arrays para os códigos e quantidades
    int *itens_cod  = (int *) malloc(n * sizeof(int));
    int *itens_quan = (int *) malloc(n * sizeof(int));
    
    if (!itens_cod || !itens_quan) {
        printf("Falha ao alocar memoria para itens.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Codigo do item %d: ", i + 1);
        scanf("%d", &itens_cod[i]);
        printf("Quantidade do item %d: ", i + 1);
        scanf("%d", &itens_quan[i]);
    }
//scanf gera um erro que não permite dar espaço, mas preferi deixar assim 
    char temp_desc[500];
    char temp_sol[100];

    printf("Descricao do problema: ");
    scanf(" %s", temp_desc); 

    printf("Nome do solicitante: ");
    scanf(" %s", temp_sol);

    // Alocar strings na heap para persistir após o fim da função
    char *desc_final = (char *)malloc(strlen(temp_desc) + 1);
    char *sol_final  = (char *)malloc(strlen(temp_sol) + 1);
    strcpy(desc_final, temp_desc);
    strcpy(sol_final, temp_sol);

    if (eh_urgente) {
        int prioridade;
        printf("Grau de urgencia: ");
        scanf("%d", &prioridade);

        inserir_prior_filamax(fila_urgente, itens_cod, itens_quan, desc_final, sol_final, n, contador, prioridade);
        printf("O codigo do seu pedido e: %d\nChamado registrado com sucesso.\n", contador);
    } else {
        inserir_fim_fifo(fila_normal, itens_cod, itens_quan, desc_final, sol_final, n, contador);
        printf("Seu codigo de No e: %d\nChamado registrado com sucesso.\n", contador);
    }

  
}

void tela_atendimento(void) {
    printf("\n=== Tela: Processo de atendimento de chamado ===\n");

    int tem_urgente = fila_posui_valor_filamax(fila_urgente);
    int tem_normal  = verificar_filavaz_fifo(fila_normal);

    if (!tem_urgente && !tem_normal) {
        printf("Nao ha chamados para atendimento.\n");
        return;
    }

//Aqui processa o pedido urgente    
    if (tem_urgente) {
        Pedido p = extrair_maximo(fila_urgente);
        if (p.codigo == -1) return;

        printf("Atendendo chamado URGENTE de %s (codigo %d)\n", p.solicitante, p.codigo);

        int tem_material = 1;
        for (int i = 0; i < p.qtd_tipos_itens; i++) {
            NoEst *no = Busca_estoque(estoque, p.itens_cod[i]);
            if (no == NULL || no->quantidade < p.itens_quan[i]) {
                tem_material = 0; break;
            }
        }

        if (!tem_material) {
            inserir_fim_sus(suspensos, p.itens_cod, p.itens_quan, p.desc, p.solicitante, p.qtd_tipos_itens, p.codigo);
            printf("Chamado %d movido para LISTA DE SUSPENSOS.\n", p.codigo);
            return;
        }

        // Decrementa estoque
        for (int i = 0; i < p.qtd_tipos_itens; i++) {
            NoEst *no = Busca_estoque(estoque, p.itens_cod[i]);
            if (no) no->quantidade -= p.itens_quan[i];
        }

        inserir_fim_att(em_atendimento, p.itens_cod, p.itens_quan, p.desc, p.solicitante, "em atendimento", p.qtd_tipos_itens, p.codigo);

        NoTec *tec = encontrar_tecnico_menos_servicos(tecnicos);
        if (tec) {
            if (!tec->lista) {
                tec->lista = (ListaSer *)malloc(sizeof(ListaSer));
                tec->lista->primeiro = NULL; tec->lista->ultimo = NULL; tec->lista->quantidade = 0;
            }
            NoSer *novo = (NoSer *)malloc(sizeof(NoSer));
            novo->codigo = p.codigo;
            novo->itens_ped = p.qtd_tipos_itens;
            novo->proximo = NULL;

            novo->itens_cod = (int*)malloc(p.qtd_tipos_itens * sizeof(int));
            novo->itens_quant = (int*)malloc(p.qtd_tipos_itens * sizeof(int));
            memcpy(novo->itens_cod, p.itens_cod, p.qtd_tipos_itens * sizeof(int));
            memcpy(novo->itens_quant, p.itens_quan, p.qtd_tipos_itens * sizeof(int));
            
            novo->descricao = (char*)malloc(strlen(p.desc)+1);
            strcpy(novo->descricao, p.desc);
            novo->solicitante = (char*)malloc(strlen(p.solicitante)+1);
            strcpy(novo->solicitante, p.solicitante);

            if (tec->lista->primeiro == NULL) { tec->lista->primeiro = novo; tec->lista->ultimo = novo; }
            else { tec->lista->ultimo->proximo = novo; tec->lista->ultimo = novo; }
            tec->lista->quantidade++;
            printf("Chamado %d atribuido ao tecnico %s.\n", p.codigo, tec->nome);
        }
        
    } 
    
//Aqui processa o pedido normal   
    else {
        No n = remover_inicio_fifo(fila_normal);
        if (n.codigo == -1) return;
        
        printf("Atendendo chamado NORMAL de %s (codigo %d)\n", n.solicitante, n.codigo);

        int tem_material = 1;
        for (int i = 0; i < n.itens_ped; i++) {
            NoEst *no = Busca_estoque(estoque, n.itens_cod[i]);
            if (no == NULL || no->quantidade < n.itens_quant[i]) {
                tem_material = 0; break;
            }
        }

        if (!tem_material) {
            inserir_fim_sus(suspensos, n.itens_cod, n.itens_quant, n.descricao, n.solicitante, n.itens_ped, n.codigo);
            printf("Chamado %d movido para LISTA DE SUSPENSOS.\n", n.codigo);
            return;
        }

        for (int i = 0; i < n.itens_ped; i++) {
            NoEst *no = Busca_estoque(estoque, n.itens_cod[i]);
            if (no) no->quantidade -= n.itens_quant[i];
        }

        inserir_fim_att(em_atendimento, n.itens_cod, n.itens_quant, n.descricao, n.solicitante, "em atendimento", n.itens_ped, n.codigo);

        NoTec *tec = encontrar_tecnico_menos_servicos(tecnicos);
        if (tec) {
             if (!tec->lista) {
                tec->lista = (ListaSer *)malloc(sizeof(ListaSer));
                tec->lista->primeiro = NULL; tec->lista->ultimo = NULL; tec->lista->quantidade = 0;
            }
            NoSer *novo = (NoSer *)malloc(sizeof(NoSer));
            novo->codigo = n.codigo;
            novo->itens_ped = n.itens_ped;
            novo->proximo = NULL;

            novo->itens_cod = (int*)malloc(n.itens_ped * sizeof(int));
            novo->itens_quant = (int*)malloc(n.itens_ped * sizeof(int));
            memcpy(novo->itens_cod, n.itens_cod, n.itens_ped * sizeof(int));
            memcpy(novo->itens_quant, n.itens_quant, n.itens_ped * sizeof(int));
            
            novo->descricao = (char*)malloc(strlen(n.descricao)+1);
            strcpy(novo->descricao, n.descricao);
            novo->solicitante = (char*)malloc(strlen(n.solicitante)+1);
            strcpy(novo->solicitante, n.solicitante);

            if (tec->lista->primeiro == NULL) { tec->lista->primeiro = novo; tec->lista->ultimo = novo; }
            else { tec->lista->ultimo->proximo = novo; tec->lista->ultimo = novo; }
            tec->lista->quantidade++;
            printf("Chamado %d atribuido ao tecnico %s.\n", n.codigo, tec->nome);
        }
        
        free(n.itens_cod); free(n.itens_quant); free(n.descricao); free(n.solicitante);
    }
}



void tela_estoque(void) {
    printf("\n=== Tela: Processo para adicionar itens no estoque ===\n");

    int continuar = 1;
    while (continuar) {
        int codigo, quantidade;
        char nome_item[50];

        printf("Codigo do item: ");
        scanf("%d", &codigo);
        printf("Nome do item: ");
        scanf("%s", nome_item);
        printf("Quantidade a adicionar: ");
        scanf("%d", &quantidade);

        NoEst *no = Busca_estoque(estoque, codigo);
        if (no) {
            no->quantidade += quantidade;
            printf("Quantidade atualizada. Novo estoque de %s (cod %d) = %d\n", no->item, no->codigo, no->quantidade);
        } else {
            inserir_estoque(estoque, codigo, nome_item, quantidade);
            printf("Item adicionado ao estoque.\n");
        }
        printf("Adicionar outro item? (1 = sim, 0 = nao): ");
        scanf("%d", &continuar);
    }

    if (suspensos == NULL || suspensos->primeiro == NULL) {
        printf("Nao ha chamados suspensos para verificar.\n");
        return;
    }

    printf("\nVerificando chamados SUSPENSOS...\n");

    Nosus *atual    = suspensos->primeiro;
    Nosus *anterior = NULL;

    while (atual != NULL) {
        Nosus *proximo = atual->proximo;
        int codigo_pedido = atual->codigo;
        int pode_ser = 1;

        if (atual->itens_cod == NULL || atual->itens_quant == NULL) {
             printf("Erro: Chamado %d corrompido (ponteiros nulos). Removendo.\n", codigo_pedido);
             pode_ser = 0; 
             
             anterior = atual;
             atual = proximo;
             continue;
        }

        for (int i = 0; i < atual->itens_ped; i++) {
            NoEst *no = Busca_estoque(estoque, atual->itens_cod[i]);
            if (no == NULL || no->quantidade < atual->itens_quant[i]) {
                pode_ser = 0;
                break;
            }
        }

        if (pode_ser) {
            for (int i = 0; i < atual->itens_ped; i++) {
                NoEst *no_est = Busca_estoque(estoque, atual->itens_cod[i]);
                if (no_est != NULL) no_est->quantidade -= atual->itens_quant[i];
            }

            if (anterior == NULL) {
                suspensos->primeiro = proximo;
            } else {
                anterior->proximo = proximo;
            }
            if (suspensos->ultimo == atual) {
                suspensos->ultimo = anterior;
            }
            suspensos->quantidade--;

            inserir_prior_filamax(
                fila_urgente,
                atual->itens_cod,
                atual->itens_quant,
                atual->descricao,
                atual->solicitante,
                atual->itens_ped,
                atual->codigo,
                5 //entra como a maior prioridade(5) 
            );

            printf("Pedido suspenso %d reativado para fila URGENTE.\n", codigo_pedido);

            free(atual); 
            
        } else {
            anterior = atual;
        }
        atual = proximo;
    }
    printf("Verificacao de suspensos concluida.\n");
}






void tela_cancelamento(void) {
    printf("\n=== Tela: Processo de cancelamento de chamado ===\n");

    int escolha;
    printf("Cancelar chamado de onde?\n");
    printf("1 - Fila (normal ou urgente)\n");
    printf("2 - Suspenso\n");
    printf("3 - Em atendimento\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    switch (escolha) {

    case 1: { // Fila (normal ou urgente)
        int tipo, codigo;
        printf("1 - Urgente\n2 - Normal\nEscolha: ");
        scanf("%d", &tipo);

        printf("Digite o codigo de seu pedido: ");
        scanf("%d", &codigo);

        if (tipo == 1) {
            Pedido p = extrair_esp(fila_urgente, codigo);

            if (p.codigo != -1) {
                inserir_fim_his(historico,
                                p.itens_cod,
                                p.itens_quan,
                                p.desc,
                                p.solicitante,
                                p.qtd_tipos_itens,
                                p.codigo,
                                "cancelado");

                printf("Pedido %d cancelado e movido para lista de removidos.\n", codigo);
            } else {
                printf("Pedido nao encontrado na fila urgente.\n");
            }

        } else if (tipo == 2) {
            No p = remover_esp_fifo(fila_normal, codigo);

            if (p.codigo == -1) {
                printf("Pedido nao encontrado na fila normal.\n");
            } else {
                inserir_fim_his(historico,
                                p.itens_cod,
                                p.itens_quant,
                                p.descricao,
                                p.solicitante,
                                p.itens_ped,
                                p.codigo,
                                "cancelado");

                printf("Pedido %d cancelado e movido para lista de removidos.\n", codigo);

                free(p.itens_cod);
                free(p.itens_quant);
                free(p.descricao);
                free(p.solicitante);
            }

        } else {
            printf("Opcao invalida.\n");
        }
        break;
    }

    case 2: { // Suspensos
        int codigo;
        printf("Digite o codigo de seu pedido: ");
        scanf("%d", &codigo);

        Nosus *nosus = remover_posicao_sus(suspensos, codigo);

        if (nosus == NULL) {
            printf("Pedido %d nao encontrado na lista de suspensos.\n", codigo);
        } else {
            inserir_fim_his(historico,
                            nosus->itens_cod,
                            nosus->itens_quant,
                            nosus->descricao,
                            nosus->solicitante,
                            nosus->itens_ped,
                            nosus->codigo,
                            "cancelado");

            printf("Pedido %d cancelado e movido para lista de removidos.\n", codigo);

            free(nosus->itens_cod);
            free(nosus->itens_quant);
            free(nosus->descricao);
            free(nosus->solicitante);
            free(nosus);
        }
        break;
    }

    case 3: { // Em atendimento (técnico + lista de atendimento)
        int reg_tecnico;
        int codigo_pedido;

        printf("Digite o registro do tecnico responsavel pelo chamado: ");
        scanf("%d", &reg_tecnico);

        NoTec *tec = Busca_tecnico(tecnicos, reg_tecnico);
        if (tec == NULL) {
            printf("Tecnico nao encontrado.\n");
            break;
        }

        if (tec->lista == NULL || tec->lista->primeiro == NULL) {
            printf("Esse tecnico nao possui chamados em atendimento.\n");
            break;
        }

        printf("Digite o codigo do pedido que deseja cancelar: ");
        scanf("%d", &codigo_pedido);

        NoSer *serv = remover_servico_tecnico(tec, codigo_pedido);
        if (serv == NULL) {
            printf("Pedido %d nao encontrado na lista do tecnico %s.\n",
                   codigo_pedido, tec->nome);
            break;
        }

        int r = remover_posicao_att(em_atendimento, codigo_pedido);
        if (r == -1) {
            printf("Aviso: pedido %d nao foi encontrado na lista de atendimento.\n",
                   codigo_pedido);
        }

        inserir_fim_his(historico,
                        serv->itens_cod,
                        serv->itens_quant,
                        serv->descricao,
                        serv->solicitante,
                        serv->itens_ped,
                        serv->codigo,
                        "cancelado");

        printf("Pedido %d do tecnico %s cancelado e movido para o historico.\n",
               codigo_pedido, tec->nome);

        free(serv->itens_cod);
        free(serv->itens_quant);
        free(serv->descricao);
        free(serv->solicitante);
        free(serv);

        break;
    }

    default:
        printf("Opcao invalida.\n");
        break;
    }
}


void tela_encerramento(void) {
    printf("\n=== Tela: Processo de encerramento de chamado ===\n");

    int reg_tecnico;
    int codigo_pedido;

    printf("Digite o registro do tecnico responsavel pelo chamado: ");
    scanf("%d", &reg_tecnico);

    NoTec *tec = Busca_tecnico(tecnicos, reg_tecnico);
    if (tec == NULL) {
        printf("Tecnico nao encontrado.\n");
        return;
    }

    if (tec->lista == NULL || tec->lista->primeiro == NULL) {
        printf("Esse tecnico nao possui chamados em atendimento.\n");
        return;
    }

    printf("Digite o codigo do chamado que deseja encerrar: ");
    scanf("%d", &codigo_pedido);

    NoSer *serv = remover_servico_tecnico(tec, codigo_pedido);
    if (serv == NULL) {
        printf("Chamado %d nao encontrado na lista do tecnico %s.\n", codigo_pedido, tec->nome);
        return;
    }

    int r = remover_posicao_att(em_atendimento, codigo_pedido);
    if (r == -1) {
        printf("Aviso: chamado %d nao estava na lista global de atendimento.\n", codigo_pedido);
    }

    inserir_fim_his(historico,
                    serv->itens_cod,
                    serv->itens_quant,
                    serv->descricao,
                    serv->solicitante,
                    serv->itens_ped,
                    serv->codigo,
                    "concluido"); 

    printf("Chamado %d concluido com sucesso pelo tecnico %s.\n", codigo_pedido, tec->nome);

    free(serv->itens_cod);
    free(serv->itens_quant);
    free(serv->descricao);
    free(serv->solicitante);
    free(serv);
}

