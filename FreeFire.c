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
#include <stdio.h>
#include <string.h>

#define TAM 10
#define STR 50

// Estrutura que define um item do inventário
typedef struct {
    char nome[STR];
    char tipo[STR];
    int quantidade;
    int ativo;  // 1 = item existe | 0 = slot vazio
} Item;

void adicionarItem(Item mochila[]);
void removerItem(Item mochila[]);
void listarItens(Item mochila[]);

int main() {
    Item mochila[TAM] = {0};
    int opcao;

    do {
        printf("\n===== MOCHILA - CODE DA ILHA (Nível Novato) =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar enter

        switch (opcao) {
            case 1:
                adicionarItem(mochila);
                break;
            case 2:
                removerItem(mochila);
                break;
            case 3:
                listarItens(mochila);
                break;
            case 0:
                printf("\nEncerrando...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// ----------------------------------------------------
// Adicionar item à mochila
// ----------------------------------------------------
void adicionarItem(Item mochila[]) {
    int i;

    // Procurar espaço livre
    for (i = 0; i < TAM; i++) {
        if (mochila[i].ativo == 0) {
            printf("\n=== Adicionar Item ===\n");
            printf("Nome: ");
            fgets(mochila[i].nome, STR, stdin);
            mochila[i].nome[strcspn(mochila[i].nome, "\n")] = '\0';

            printf("Tipo: ");
            fgets(mochila[i].tipo, STR, stdin);
            mochila[i].tipo[strcspn(mochila[i].tipo, "\n")] = '\0';

            printf("Quantidade: ");
            scanf("%d", &mochila[i].quantidade);
            getchar();

            mochila[i].ativo = 1;
            printf("\nItem adicionado com sucesso!\n");
            return;
        }
    }

    printf("\n⚠ Mochila cheia! Não é possível adicionar mais itens.\n");
}

// ----------------------------------------------------
// Remover item pelo nome
// ----------------------------------------------------
void removerItem(Item mochila[]) {
    char nomeBusca[STR];
    int encontrado = 0;

    printf("\n=== Remover Item ===\n");
    printf("Nome do item: ");
    fgets(nomeBusca, STR, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < TAM; i++) {
        if (mochila[i].ativo == 1 &&
            strcmp(mochila[i].nome, nomeBusca) == 0) {

            mochila[i].ativo = 0;
            printf("\nItem removido!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("\n⚠ Item não encontrado!\n");
}

// ----------------------------------------------------
// Listar todos os itens ativos
// ----------------------------------------------------
void listarItens(Item mochila[]) {
    printf("\n===== ITENS NA MOCHILA =====\n");
    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("-----------------------------------------------------\n");

    int vazio = 1;

    for (int i = 0; i < TAM; i++) {
        if (mochila[i].ativo == 1) {
            printf("%-20s %-15s %-10d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
            vazio = 0;
        }
    }

    if (vazio)
        printf("Nenhum item cadastrado.\n");
}
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
