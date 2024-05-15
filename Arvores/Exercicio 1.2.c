#include <stdio.h>
#include <stdbool.h> // To use the bool type

struct no {
    char letra;
    int filhos[3];
};

// Function to perform depth-first search
void buscaProfundidade(struct no exemplo[], int noAtual, int profundidade) {
    // Display the current node with its depth
    printf("Visitando no (Profundidade %d): %c\n", profundidade, exemplo[noAtual].letra);

    // Recursively visit the children of the current node (if any)
    for (int i = 0; i < 3; i++) {
        int filho = exemplo[noAtual].filhos[i];
        if (filho != -1) {
            buscaProfundidade(exemplo, filho, profundidade + 1);
        }
    }
}

int main() {
    struct no exemplo1[8];
    int i, j;

    for (i = 0; i < 8; i++) {
        exemplo1[i].letra = '\0';
        for (j = 0; j < 3; j++) {
            exemplo1[i].filhos[j] = -1;
        }
    }

    int numNos;
    printf("Quantos nos voce deseja inserir? (maximo 8): ");
    scanf("%d", &numNos);

    for (i = 0; i < numNos; i++) {
        printf("Insira a letra do no %d: ", i);
        scanf(" %c", &exemplo1[i].letra);

        printf("Insira os filhos do no %c (separados por espaco, -1 para nenhum filho): ", exemplo1[i].letra);
        for (j = 0; j < 3; j++) {
            scanf("%d", &exemplo1[i].filhos[j]);
        }
    }

    // Display the modified tree
    printf("\nArvore modificada:\n");
    for (i = 0; i < numNos; i++) {
        printf("Pai: %c\n", exemplo1[i].letra);
        for (j = 0; j < 3; j++) {
            if (exemplo1[i].filhos[j] != -1) {
                printf("Filho %d: %c - ", j, exemplo1[exemplo1[i].filhos[j]].letra);
            }
        }
        printf("\n");
    }
    printf("\n Representacoes: 1=B; 2=C; 3=D; 4=E; 5=F; 6=G; 7=H");

    // Perform depth-first search starting from the root node (node 0)
    printf("\nBusca em profundidade:\n");
    buscaProfundidade(exemplo1, 0, 0);

    // Menu for inserting a new node or exiting
    int opcao;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Exibir arvore original\n");
        printf("2. Inserir novo no\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 2) {
            char novaLetra;
            int pai;

            printf("Insira a letra do novo no: ");
            scanf(" %c", &novaLetra);

            printf("Insira o no pai (1=B, 2=C, 3=D, ...): ");
            scanf("%d", &pai);

            // Check if the parent node has space for a new child
            int posicaoFilho = -1;
            for (i = 0; i < 3; i++) {
                if (exemplo1[pai].filhos[i] == -1) {
                    posicaoFilho = i;
                    break;
                }
            }

            if (posicaoFilho != -1) {
                // add novo filho
                exemplo1[pai].filhos[posicaoFilho] = numNos;
                exemplo1[numNos].letra = novaLetra;

                printf("Novo no %c adicionado como filho de %c.\n", novaLetra, exemplo1[pai].letra);
                numNos++;
            } else {
                printf("Nao e possível adicionar um novo filho ao no %c.\n", exemplo1[pai].letra);
            }
        } else if (opcao == 3) {
            printf("Saindo do programa.\n");
            break; // Saia do loop
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
