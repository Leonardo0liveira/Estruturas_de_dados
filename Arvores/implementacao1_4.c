#include <stdio.h>
#include <stdlib.h>

#define MAX_NOS 100
#define MAX_FILHOS 3

struct no {
    char letra;
    int filhos[MAX_FILHOS];
};

struct no exemplo1[MAX_NOS];

void inicializaArvore() {
    for (int i = 0; i < MAX_NOS; i++) {
        exemplo1[i].letra = '\0';
        for (int j = 0; j < MAX_FILHOS; j++) {
            exemplo1[i].filhos[j] = -1;
        }
    }
}

void insereNo(char pai, char filho) {
    int indicePai = -1;
    int indiceFilho = -1;
    for (int i = 0; i < MAX_NOS; i++) {
        if (exemplo1[i].letra == pai) {
            indicePai = i;
        }
        if (exemplo1[i].letra == '\0' && indiceFilho == -1) {
            indiceFilho = i;
            break;
        }
    }
    if (indicePai != -1 && indiceFilho != -1) {
        exemplo1[indiceFilho].letra = filho;
        for (int i = 0; i < MAX_FILHOS; i++) {
            if (exemplo1[indicePai].filhos[i] == -1) {
                exemplo1[indicePai].filhos[i] = indiceFilho;
                break;
            }
        }
    }
}

void buscaEmProfundidade() {
    int fila[MAX_NOS], inicio = 0, fim = 0;
    fila[fim++] = 0; // Começando pela raiz
    while (inicio != fim) {
        int atual = fila[inicio++];
        printf("%c ", exemplo1[atual].letra);
        for (int i = 0; i < MAX_FILHOS; i++) {
            int filho = exemplo1[atual].filhos[i];
            if (filho != -1) {
                fila[fim++] = filho;
            }
        }
    }
    printf("\n");
}

void removeNoComFilhos(int indice) {
    for (int i = 0; i < MAX_FILHOS; i++) {
        int filho = exemplo1[indice].filhos[i];
        if (filho != -1) {
            removeNoComFilhos(filho);
        }
    }
    exemplo1[indice].letra = '\0';
    for (int i = 0; i < MAX_FILHOS; i++) {
        exemplo1[indice].filhos[i] = -1;
    }
}

void imprimeArvore(int indice, int nivel) {
    if (exemplo1[indice].letra != '\0') {
        for (int i = 0; i < nivel; i++) {
            printf("  ");
        }
        printf("%c\n", exemplo1[indice].letra);
        for (int i = 0; i < MAX_FILHOS; i++) {
            if (exemplo1[indice].filhos[i] != -1) {
                imprimeArvore(exemplo1[indice].filhos[i], nivel + 1);
            }
        }
    }
}

int main() {
    char pai, filho;
    int opcao, indiceNo;
    inicializaArvore();
    exemplo1[0].letra = 'A';
    insereNo('A', 'B');
    insereNo('A', 'C');
    insereNo('A', 'D');
    insereNo('B', 'E');
    insereNo('B', 'F');
    insereNo('D', 'G');
    insereNo('G', 'H');

    do {
        printf("\nMenu:\n");
        printf("1. Inserir nó\n");
        printf("2. Busca em profundidade\n");
        printf("3. Remover nó e seus filhos\n");
        printf("4. Imprimir árvore\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o nó pai e o nó filho para inserir (exemplo: A B): ");
                scanf(" %c %c", &pai, &filho);
                insereNo(pai, filho);
                break;
            case 2:
                printf("Busca em profundidade a partir da raiz:\n");
                buscaEmProfundidade();
                break;
            case 3:
                printf("Digite o índice do nó para remover ele e seus filhos: ");
                scanf("%d", &indiceNo);
                removeNoComFilhos(indiceNo);
                break;
            case 4:
                printf("Estrutura atual da árvore:\n");
                imprimeArvore(0, 0);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Por favor, tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}