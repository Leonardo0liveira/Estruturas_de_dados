#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTOS 100 // Defina o tamanho máximo do vetor

// Define a estrutura Fila
struct Fila {
    char elementos[MAX_ELEMENTOS][100]; // Vetor para armazenar os elementos
    int frente, tras; // Índices da frente e do final da fila
};

// Função para criar uma nova fila
struct Fila criarFila() {
    struct Fila fila;
    fila.frente = -1; // Inicializa a frente como -1
    fila.tras = -1; // Inicializa o final como -1
    return fila;
}

// Função para verificar se a fila está vazia
int filaVazia(struct Fila fila) {
    return fila.frente == -1; // Retorna 1 se a frente for -1 (fila vazia)
}

// Função para verificar se a fila está cheia
int filaCheia(struct Fila fila) {
    return fila.tras == MAX_ELEMENTOS - 1; // Retorna 1 se o final for igual ao tamanho máximo - 1
}

// Função para inserir um elemento na fila
void inserirElemento(struct Fila *fila, char elemento[]) {
    if (!filaCheia(*fila)) {
        if (filaVazia(*fila)) {
            fila->frente = 0; // Se a fila estiver vazia, define a frente como 0
        }
        fila->tras++; // Atualiza o final
        strcpy(fila->elementos[fila->tras], elemento); // Insere o elemento no final
        printf("Elemento '%s' inserido na fila.\n", elemento);
    } else {
        printf("A fila está cheia. Elemento '%s' não foi inserido.\n", elemento);
    }
}

// Função para remover um elemento da fila
void removerElemento(struct Fila *fila) {
    if (!filaVazia(*fila)) {
        printf("Elemento '%s' removido da fila.\n", fila->elementos[fila->frente]); // Remove o elemento da frente
        if (fila->frente == fila->tras) {
            fila->frente = fila->tras = -1; // Se a fila tinha apenas um elemento, define frente e final como -1
        } else {
            fila->frente++; // Atualiza a frente
        }
    } else {
        printf("A fila está vazia. Nenhum elemento para remover.\n");
    }
}

// Função para exibir os elementos da fila
void exibirElementos(struct Fila fila) {
    if (!filaVazia(fila)) {
        printf("\nElementos na fila:\n");
        for (int i = fila.frente; i <= fila.tras; i++) {
            printf("%s\n", fila.elementos[i]);
        }
    } else {
        printf("A fila está vazia. Nenhum elemento para exibir.\n");
    }
}

// Função para localizar um elemento na fila para consulta
void localizarElementoConsulta(struct Fila fila, char elemento[]) {
    if (!filaVazia(fila)) {
        for (int i = fila.frente; i <= fila.tras; i++) {
            if (strcmp(fila.elementos[i], elemento) == 0) {
                printf("O elemento '%s' foi encontrado na fila na posição %d.\n", elemento, i + 1);
                return;
            }
        }
        printf("O elemento '%s' não foi encontrado na fila.\n", elemento);
    } else {
        printf("A fila está vazia. Nenhum elemento para consultar.\n");
    }
}

// Função para localizar um elemento na fila para alteração da informação
void localizarElementoAlteracao(struct Fila *fila, char elemento[]) {
    if (!filaVazia(*fila)) {
        for (int i = fila->frente; i <= fila->tras; i++) {
            if (strcmp(fila->elementos[i], elemento) == 0) {
                printf("Digite o novo valor para o elemento '%s': ", elemento);
                scanf(" %[^\n]", fila->elementos[i]); // Lê o novo valor para o elemento
                printf("O elemento '%s' foi alterado para '%s'.\n", elemento, fila->elementos[i]);
                return;
            }
        }
        printf("O elemento '%s' não foi encontrado na fila. Nenhuma alteração feita.\n", elemento);
    } else {
        printf("A fila está vazia. Nenhum elemento para alterar.\n");
    }
}

// Função para buscar por elementos que coincidam com um certo padrão na fila
void buscarPorPadrao(struct Fila fila, char padrao[]) {
    if (!filaVazia(fila)) {
        printf("\nElementos na fila que coincidem com o padrão '%s':\n", padrao);
        for (int i = fila.frente; i <= fila.tras; i++) {
            if (strstr(fila.elementos[i], padrao) != NULL) {
                printf("%s\n", fila.elementos[i]);
            }
        }
    } else {
        printf("A fila está vazia. Nenhum elemento para buscar por padrão.\n");
    }
}

// Função para intercalar duas filas
void intercalarFilas(struct Fila fila1, struct Fila fila2) {
    struct Fila resultado = criarFila();
    int i = fila1.frente, j = fila2.frente;
    while (i <= fila1.tras || j <= fila2.tras) {
        if (i <= fila1.tras) {
            inserirElemento(&resultado, fila1.elementos[i]);
            i++;
        }
        if (j <= fila2.tras) {
            inserirElemento(&resultado, fila2.elementos[j]);
            j++;
        }
    }
    printf("Filas intercaladas:\n");
    exibirElementos(resultado);
}

// Função para concatenar duas filas
void concatenarFilas(struct Fila *fila1, struct Fila fila2) {
    if ((fila1->tras + 1) + (fila2.tras - fila2.frente + 1) <= MAX_ELEMENTOS) {
        for (int i = fila2.frente; i <= fila2.tras; i++) {
            inserirElemento(fila1, fila2.elementos[i]);
        }
        printf("Filas concatenadas:\n");
        exibirElementos(*fila1);
    } else {
        printf("A fila de destino está cheia. Alguns elementos podem não ter sido concatenados.\n");
    }
}

// Função para dividir uma fila em duas
void dividirFila(struct Fila *fila, struct Fila *metade1, struct Fila *metade2) {
    while (!filaVazia(*fila)) {
        if (!filaCheia(*metade1)) {
            inserirElemento(metade1, fila->elementos[fila->frente]);
            removerElemento(fila);
        } else if (!filaCheia(*metade2)) {
            inserirElemento(metade2, fila->elementos[fila->frente]);
            removerElemento(fila);
        } else {
            printf("As filas de destino estão cheias. Alguns elementos podem não ter sido divididos.\n");
            return;
        }
    }
    printf("Fila dividida:\n");
    printf("Metade 1:\n");
    exibirElementos(*metade1);
    printf("Metade 2:\n");
    exibirElementos(*metade2);
}

// Função para fazer uma cópia da fila
void copiarFila(struct Fila fila, struct Fila *copia) {
    while (!filaVazia(fila)) {
        if (!filaCheia(*copia)) {
            inserirElemento(copia, fila.elementos[fila.frente]);
            removerElemento(&fila);
        } else {
            printf("A fila de cópia está cheia. Alguns elementos podem não ter sido copiados.\n");
            return;
        }
    }
    printf("Cópia da fila:\n");
    exibirElementos(*copia);
}

// Função do menu principal
void menu() {
    struct Fila fila1 = criarFila();
    struct Fila fila2 = criarFila();
    int opcao;

    while (1) {
        printf("\nDigite 1 para inserir elemento na fila 1\n");
        printf("Digite 2 para remover elemento da fila 1\n");
        printf("Digite 3 para exibir elementos da fila 1\n");
        printf("Digite 4 para localizar um elemento na fila 1 para consulta\n");
        printf("Digite 5 para localizar um elemento na fila 1 para alteração\n");
        printf("Digite 6 para buscar por padrão na fila 1\n");
        printf("Digite 7 para criar uma nova fila\n");
        printf("Digite 8 para verificar se a fila 1 está vazia\n");
        printf("Digite 9 para verificar se a fila 1 está cheia\n");
        printf("Digite 10 para intercalar fila 1 e fila 2\n");
        printf("Digite 11 para concatenar fila 1 e fila 2\n");
        printf("Digite 12 para dividir a fila 1 em duas\n");
        printf("Digite 13 para fazer uma cópia da fila 1\n");
        printf("Digite 14 para sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char elemento[100];
                printf("Digite o elemento a ser inserido na fila 1: ");
                scanf(" %[^\n]", elemento);
                inserirElemento(&fila1, elemento);
                break;
            }
            case 2:
                removerElemento(&fila1);
                break;
            case 3:
                exibirElementos(fila1);
                break;
            case 4: {
                char elemento[100];
                printf("Digite o elemento que deseja localizar na fila 1: ");
                scanf(" %[^\n]", elemento);
                localizarElementoConsulta(fila1, elemento);
                break;
            }
            case 5: {
                char elemento[100];
                printf("Digite o elemento que deseja alterar na fila 1: ");
                scanf(" %[^\n]", elemento);
                localizarElementoAlteracao(&fila1, elemento);
                break;
            }
            case 6: {
                char padrao[100];
                printf("Digite o padrao a ser buscado na fila 1: ");
                scanf(" %[^\n]", padrao);
                buscarPorPadrao(fila1, padrao);
                break;
            }
            case 7:
                fila1 = criarFila();
                printf("Uma nova fila foi criada.\n");
                break;
            case 8:
                if (filaVazia(fila1)) {
                    printf("A fila 1 está vazia.\n");
                } else {
                    printf("A fila 1 não está vazia.\n");
                }
                break;
            case 9:
                if (filaCheia(fila1)) {
                    printf("A fila 1 está cheia.\n");
                } else {
                    printf("A fila 1 não está cheia.\n");
                }
                break;
            case 10:
                intercalarFilas(fila1, fila2);
                break;
            case 11:
                concatenarFilas(&fila1, fila2);
                break;
            case 12: {
                struct Fila metade1 = criarFila();
                struct Fila metade2 = criarFila();
                dividirFila(&fila1, &metade1, &metade2);
                break;
            }
            case 13: {
                struct Fila copia = criarFila();
                copiarFila(fila1, &copia);
                break;
            }
            case 14:
                printf("Saindo...\n");
                return;
            default:
                printf("Opcao invalida. Por favor, tente novamente.\n");
        }
    }
}

// Função principal
int main() {
    // Chamada da função do menu principal
    menu();

    return 0;
}
