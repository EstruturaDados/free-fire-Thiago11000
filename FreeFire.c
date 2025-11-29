#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Enum para critérios de ordenação
enum Criterio {
    NOME,
    TIPO,
    PRIORIDADE
};

// Struct para representar um item
typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// Vetor estático para a mochila (capacidade máxima de 10 itens)
Item mochila[10];
int numItens = 0;
bool ordenadoPorNome = false; // Flag para verificar se está ordenado por nome

// Função para adicionar item
void adicionarItem() {
    if (numItens >= 10) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    Item novoItem;
    printf("Digite o nome do item: ");
    scanf("%s", novoItem.nome);
    printf("Digite o tipo do item: ");
    scanf("%s", novoItem.tipo);
    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    printf("Digite a prioridade (1-5): ");
    scanf("%d", &novoItem.prioridade);
    if (novoItem.prioridade < 1 || novoItem.prioridade > 5) {
        printf("Prioridade inválida! Deve ser entre 1 e 5.\n");
        return;
    }
    mochila[numItens] = novoItem;
    numItens++;
    ordenadoPorNome = false; // Invalida a ordenação por nome
    printf("Item adicionado com sucesso!\n");
}

// Função para remover item pelo nome
void removerItem() {
    char nome[50];
    printf("Digite o nome do item a remover: ");
    scanf("%s", nome);
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            ordenadoPorNome = false; // Invalida a ordenação por nome
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

// Função para listar itens
void listarItens() {
    if (numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    printf("Itens na mochila:\n");
    printf("%-20s %-20s %-10s %-10s\n", "Nome", "Tipo", "Quantidade", "Prioridade");
    for (int i = 0; i < numItens; i++) {
        printf("%-20s %-20s %-10d %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

// Função para busca sequencial por nome
void buscarSequencial() {
    char nome[50];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nome);
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
            return;
        }
    }
    printf("Item não encontrado!\n");
}

// Função para ordenar usando Insertion Sort
void ordenar(int criterio, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        bool continuar = true;
        while (j >= 0 && continuar) {
            (*comparacoes)++;
            switch (criterio) {
                case NOME:
                    if (strcmp(mochila[j].nome, chave.nome) > 0) {
                        mochila[j + 1] = mochila[j];
                        j--;
                    } else {
                        continuar = false;
                    }
                    break;
                case TIPO:
                    if (strcmp(mochila[j].tipo, chave.tipo) > 0) {
                        mochila[j + 1] = mochila[j];
                        j--;
                    } else {
                        continuar = false;
                    }
                    break;
                case PRIORIDADE:
                    if (mochila[j].prioridade > chave.prioridade) {
                        mochila[j + 1] = mochila[j];
                        j--;
                    } else {
                        continuar = false;
                    }
                    break;
            }
        }
        mochila[j + 1] = chave;
    }
    if (criterio == NOME) {
        ordenadoPorNome = true;
    } else {
        ordenadoPorNome = false;
    }
    printf("Ordenação concluída! Comparações realizadas: %d\n", *comparacoes);
}

// Função para busca binária por nome (requer ordenação por nome)
void buscarBinaria() {
    if (!ordenadoPorNome) {
        printf("A mochila deve estar ordenada por nome para realizar busca binária. Ordene primeiro.\n");
        return;
    }
    char nome[50];
    printf("Digite o nome do item a buscar: ");
    scanf("%s", nome);
    int esquerda = 0, direita = numItens - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\nPrioridade: %d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    printf("Item não encontrado!\n");
}

// Função principal
int main() {
    int opcao;
    do {
        printf("\n--- Menu da Mochila Virtual ---\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (sequencial)\n");
        printf("5. Ordenar mochila\n");
        printf("6. Buscar item (binária por nome)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarSequencial();
                break;
            case 5: {
                int criterio, comparacoes;
                printf("Escolha o critério de ordenação:\n");
                printf("0. Nome\n1. Tipo\n2. Prioridade\n");
                scanf("%d", &criterio);
                if (criterio < 0 || criterio > 2) {
                    printf("Critério inválido!\n");
                    break;
                }
                ordenar(criterio, &comparacoes);
                break;
            }
            case 6:
                buscarBinaria();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    return 0;
}
