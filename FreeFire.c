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

// Struct Item
typedef struct {
    char nome[TAM];
    char tipo[TAM];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// Enum de critérios
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// Vetor mochila
Item mochila[MAX_ITENS];
int numItens = 0;
bool ordenadaPorNome = false;

// ------------------ Funções ---------------------

void limparTela() {
    for (int i = 0; i < 40; i++)
        printf("\n");
}

void exibirMenu() {
    printf("=========== CODIGO DA ILHA – NIVEL MESTRE ===========\n");
    printf("Itens na mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("Ordenada por nome: %s\n", ordenadaPorNome ? "SIM" : "NAO");
    printf("------------------------------------------------------\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar mochila\n");
    printf("5. Buscar item (binaria por nome)\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    Item novo;

    printf("\nNome do item: ");
    fgets(novo.nome, TAM, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo.tipo, TAM, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    do {
        printf("Prioridade (1 a 5): ");
        scanf("%d", &novo.prioridade);
        getchar();
    } while (novo.prioridade < 1 || novo.prioridade > 5);

    mochila[numItens++] = novo;
    ordenadaPorNome = false;

    printf("\nItem adicionado!\n");
}

void removerItem() {
    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nomeBusca[TAM];
    printf("\nNome do item a remover: ");
    fgets(nomeBusca, TAM, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {

            for (int j = i; j < numItens - 1; j++)
                mochila[j] = mochila[j + 1];

            numItens--;
            ordenadaPorNome = false;

            printf("\nItem removido!\n");
            return;
        }
    }

    printf("\nItem nao encontrado.\n");
}

void listarItens() {
    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n========== ITENS DA MOCHILA ==========\n");
    printf("%-15s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("%-15s %-15s %-10d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

void insertionSort(CriterioOrdenacao criterio, int *comparacoes) {
    *comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;

            bool cond = false;

            if (criterio == ORDENAR_NOME)
                cond = strcmp(mochila[j].nome, chave.nome) > 0;
            else if (criterio == ORDENAR_TIPO)
                cond = strcmp(mochila[j].tipo, chave.tipo) > 0;
            else if (criterio == ORDENAR_PRIORIDADE)
                cond = mochila[j].prioridade > chave.prioridade;

            if (!cond) break;

            mochila[j + 1] = mochila[j];
            j--;
        }

        mochila[j + 1] = chave;
    }
}

void menuDeOrdenacao() {
    if (numItens == 0) {
        printf("\nNao ha itens para ordenar.\n");
        return;
    }

    int opc, comparacoes;

    printf("\n=== Ordenar por ===\n");
    printf("1. Nome\n");
    printf("2. Tipo\n");
    printf("3. Prioridade\n");
    printf("Escolha: ");
    scanf("%d", &opc);
    getchar();

    if (opc < 1 || opc > 3) {
        printf("\nOpcao invalida!\n");
        return;
    }

    insertionSort(opc, &comparacoes);

    ordenadaPorNome = (opc == ORDENAR_NOME);

    printf("\nMochila ordenada!\n");
    printf("Comparacoes realizadas: %d\n", comparacoes);
}

int buscarBinariaPorNome(char nome[]) {
    int inicio = 0, fim = numItens - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(nome, mochila[meio].nome);

        if (cmp == 0)
            return meio;
        else if (cmp > 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

void buscarItem() {
    if (!ordenadaPorNome) {
        printf("\nA mochila deve estar ordenada por NOME para usar busca binaria!\n");
        return;
    }

    char nomeBusca[TAM];
    printf("\nNome do item que deseja buscar: ");
    fgets(nomeBusca, TAM, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int pos = buscarBinariaPorNome(nomeBusca);

    if (pos == -1) {
        printf("\nItem nao encontrado!\n");
        return;
    }

    printf("\n===== ITEM ENCONTRADO =====\n");
    printf("Nome: %s\n", mochila[pos].nome);
    printf("Tipo: %s\n", mochila[pos].tipo);
    printf("Quantidade: %d\n", mochila[pos].quantidade);
    printf("Prioridade: %d\n", mochila[pos].prioridade);
}

// ------------------ MAIN -----------------------

int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscarItem(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpcao invalida!\n");
        }

        printf("\nPressione ENTER para continuar...");
        getchar();
        limparTela();

    } while (opcao != 0);

    return 0;
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
