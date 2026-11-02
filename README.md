# Sistema de Gerenciamento de Chamados e Estoque

Projeto desenvolvido para a disciplina de **Estrutura de Dados**, implementado na linguagem **C**. O sistema gerencia o fluxo completo de abertura, atendimento, suspensão, cancelamento e encerramento de chamados técnicos, integrando múltiplas estruturas de dados avançadas para otimizar a alocação de recursos, técnicos e controle de estoque.

---

## 🛠️ Estruturas de Dados Utilizadas

O projeto faz uso de diferentes TADs (Tipos Abstratos de Dados) para resolver problemas específicos do domínio:

1. **Fila de Prioridade Máxima (Max-Heap):** Utilizada para gerenciar os chamados urgentes. Garante que os pedidos de maior prioridade sejam atendidos primeiro.
2. **Fila Simples (FIFO):** Gerencia os chamados normais em ordem de chegada.
3. **Árvore Binária de Busca (BST):**
   * **Técnicos (`bst_tec`):** Armazena os técnicos cadastrados com base no número de registro. Cada técnico possui sua própria lista encadeada de serviços em andamento.
   * **Estoque (`bst_est`):** Organiza os itens do estoque por código, permitindo buscas, inserções e atualizações rápidas de quantidade.
4. **Pilha (Stack):** Utilizada para o controle de navegação entre as telas do sistema, permitindo voltar à tela anterior (`main.c`).
5. **Listas Duplamente Encadeadas:** Empregadas para gerenciar chamados suspensos por falta de material (`suspenso`), chamados em atendimento global (`em_at`) e o histórico de pedidos concluídos/cancelados (`historico`).

---

## 📂 Arquitetura do Projeto

O código é modularizado em vários arquivos de cabeçalho (`.h`) e implementação (`.c`):

* `main.c` / `main.h`: Arquivo principal contendo o fluxo do menu interativo e as telas do sistema.
* `Fifo.c` / `Fifo.h`: Implementação da Fila FIFO para chamados normais.
* `fila_prioridade_maxima.c` / `fila_prioridade_maxima.h`: Implementação do Max-Heap para chamados urgentes.
* `bst_tec.c` / `bst_tec.h`: Implementação da BST de técnicos e suas respectivas listas de serviços.
* `bst_est.c` / `bst_est.h`: Implementação da BST para o controle de estoque.
* `em_at.c` / `em_at.h`: Lista duplamente encadeada de chamados em atendimento.
* `suspenso.c` / `suspenso.h`: Gerenciamento de chamados suspensos por falta de estoque.
* `historico.c` / `historico.h`: Registro de chamados concluídos e cancelados.
* `pilha.c` / `pilha.h`: Pilha para controle do histórico de navegação de telas.

---

## 🚀 Como Compilar e Executar

Para compilar o projeto, certifique-se de ter um compilador C compatível instalado (como o `gcc`).

1. Clone o repositório ou baixe os arquivos fonte na mesma pasta.
2. Abra o terminal na pasta do projeto e execute o comando de compilação incluindo todos os arquivos `.c`:

```bash
gcc main.c Fifo.c fila_prioridade_maxima.c bst_tec.c bst_est.c em_at.c suspenso.c historico.c pilha.c -o sistema_chamados
