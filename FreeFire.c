#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
#define MAX_ITENS 10
#define TAM_STRING 50

// Estrutura que representa um item da mochila
typedef struct {
    char nome[TAM_STRING];
    char tipo[TAM_STRING];
    int quantidade;
    int ativo; // 1 = existe / 0 = removido
} Item;

void adicionarItem(Item mochila[], int *contador);
void removerItem(Item mochila[], int *contador);
void listarItens(Item mochila[], int contador);
void buscarItem(Item mochila[], int contador);

int main() {
    Item mochila[MAX_ITENS] = {0};
    int contador = 0;
    int opcao;

    do {
        printf("\n=== MOCHILA - NIVEL AVENTUREIRO ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item por nome\n");
        printf("5. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1: adicionarItem(mochila, &contador); break;
            case 2: removerItem(mochila, &contador); break;
            case 3: listarItens(mochila, contador); break;
            case 4: buscarItem(mochila, contador); break;
            case 5: printf("\nSaindo...\n"); break;
            default: printf("\nOpcao invalida!\n");
        }

    } while (opcao != 5);

    return 0;
}

void adicionarItem(Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("\nA mochila está cheia!\n");
        return;
    }

    printf("\nNome do item: ");
    fgets(mochila[*contador].nome, TAM_STRING, stdin);
    mochila[*contador].nome[strcspn(mochila[*contador].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochila[*contador].tipo, TAM_STRING, stdin);
    mochila[*contador].tipo[strcspn(mochila[*contador].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*contador].quantidade);
    getchar();

    mochila[*contador].ativo = 1;

    (*contador)++;
    printf("\nItem adicionado com sucesso!\n");
}

void removerItem(Item mochila[], int *contador) {
    char nomeBusca[TAM_STRING];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeBusca, TAM_STRING, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;

    for (int i = 0; i < *contador; i++) {
        if (mochila[i].ativo && strcmp(mochila[i].nome, nomeBusca) == 0) {
            mochila[i].ativo = 0;
            printf("\nItem removido!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\nItem nao encontrado.\n");
}

void listarItens(Item mochila[], int contador) {
    printf("\n=== ITENS NA MOCHILA ===\n");
    printf("%-20s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("-----------------------------------------------\n");

    int existe = 0;

    for (int i = 0; i < contador; i++) {
        if (mochila[i].ativo) {
            printf("%-20s %-20s %-10d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
            existe = 1;
        }
    }

    if (!existe)
        printf("Nenhum item cadastrado.\n");
}

void buscarItem(Item mochila[], int contador) {
    char nomeBusca[TAM_STRING];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBusca, TAM_STRING, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;

    for (int i = 0; i < contador; i++) {
        if (mochila[i].ativo && strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n=== ITEM ENCONTRADO ===\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\nItem nao encontrado.\n");
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
