#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTOS 100 /** Tamanho máximo do vetor **/

/** Estrutura Pilha **/
struct Pilha {
    char elementos[MAX_ELEMENTOS][100]; /** Vetor para armazenar todos os elementos **/

    int topo; /** Topo da pilha **/
};

/** Função para criar uma nova pilha **/
struct Pilha criarPilha() {
    struct Pilha pilha;
    pilha.topo = -1; /** Inicializa o topo como -1 **/

    return pilha;
}

/** Função para verificar se a pilha está vazia **/
int pilhaVazia(struct Pilha pilha) {
    return pilha.topo == -1; /** Retorna 1 se o topo for -1 (pilha vazia) **/
}

/** Função para verificar se a pilha está cheia **/
int pilhaCheia(struct Pilha pilha) {
    return pilha.topo == MAX_ELEMENTOS - 1; /** Retorna 1 se o topo for igual ao tamanho máximo - 1 **/
}

/** Função para inserir um elemento na pilha **/
void inserirElemento(struct Pilha *pilha, char elemento[]) {
    if (!pilhaCheia(*pilha)) {
        pilha->topo++; /** Atualiza o topo **/
        strcpy(pilha->elementos[pilha->topo], elemento); /** Insere o elemento no topo **/
        printf("Elemento '%s' inserido na pilha.\n", elemento);
    } else {
        printf("A pilha está cheia. Elemento '%s' não foi inserido.\n", elemento);
    }
}

/** Função para remover um elemento da pilha **/
void removerElemento(struct Pilha *pilha) {
    if (!pilhaVazia(*pilha)) {
        printf("Elemento '%s' removido da pilha.\n", pilha->elementos[pilha->topo]); /** Remove o elemento do topo **/
        pilha->topo--; /** Atualiza o topo **/
    } else {
        printf("A pilha está vazia. Nenhum elemento para remover.\n");
    }
}

/** Função para exibir os elementos da pilha **/
void exibirElementos(struct Pilha pilha) {
    int i; /** Declaração da variável de iteração fora do loop **/
    if (!pilhaVazia(pilha)) {
        printf("\nElementos na pilha:\n");
        for (i = pilha.topo; i >= 0; i--) {
            printf("%s\n", pilha.elementos[i]);
        }
    } else {
        printf("A pilha está vazia. Nenhum elemento para exibir.\n");
    }
}

/** Função para localizar um elemento na pilha para consulta **/
void localizarElementoConsulta(struct Pilha pilha, char elemento[]) {
    int i; /** Declaração da variável de iteração fora do loop **/
    if (!pilhaVazia(pilha)) {
        for (i = pilha.topo; i >= 0; i--) {
            if (strcmp(pilha.elementos[i], elemento) == 0) {
                printf("O elemento '%s' foi encontrado na pilha na posição %d.\n", elemento, i + 1);
                return;
            }
        }
        printf("O elemento '%s' não foi encontrado na pilha.\n", elemento);
    } else {
        printf("A pilha está vazia. Nenhum elemento para consultar.\n");
    }
}

/** Função para localizar um elemento na pilha para alteração da informação **/
void localizarElementoAlteracao(struct Pilha *pilha, char elemento[]) {
    int i; /** Declaração da variável de iteração fora do loop **/
    if (!pilhaVazia(*pilha)) {
        for (i = pilha->topo; i >= 0; i--) {
            if (strcmp(pilha->elementos[i], elemento) == 0) {
                printf("Digite o novo valor para o elemento '%s': ", elemento);
                scanf(" %[^\n]", pilha->elementos[i]); /** Lê o novo valor para o elemento **/
                printf("O elemento '%s' foi alterado para '%s'.\n", elemento, pilha->elementos[i]);
                return;
            }
        }
        printf("O elemento '%s' não foi encontrado na pilha. Nenhuma alteração feita.\n", elemento);
    } else {
        printf("A pilha está vazia. Nenhum elemento para alterar.\n");
    }
}

/** Função para buscar por elementos que coincidam com um certo padrão na pilha **/
void buscarPorPadrao(struct Pilha pilha, char padrao[]) {
    int i; /** Declaração da variável de iteração fora do loop **/
    if (!pilhaVazia(pilha)) {
        printf("\nElementos na pilha que coincidem com o padrão '%s':\n", padrao);
        for (i = pilha.topo; i >= 0; i--) {
            if (strstr(pilha.elementos[i], padrao) != NULL) {
                printf("%s\n", pilha.elementos[i]);
            }
        }
    } else {
        printf("A pilha está vazia. Nenhum elemento para buscar por padrão.\n");
    }
}

/** Função para intercalar duas pilhas **/
void intercalarPilhas(struct Pilha pilha1, struct Pilha pilha2) {
    struct Pilha resultado = criarPilha();
    while (!pilhaVazia(pilha1) || !pilhaVazia(pilha2)) {
        if (!pilhaVazia(pilha1)) {
            inserirElemento(&resultado, pilha1.elementos[pilha1.topo]);
            removerElemento(&pilha1);
        }
        if (!pilhaVazia(pilha2)) {
            inserirElemento(&resultado, pilha2.elementos[pilha2.topo]);
            removerElemento(&pilha2);
        }
    }
    printf("Pilhas intercaladas:\n");
    exibirElementos(resultado);
}

/** Função para concatenar duas pilhas **/
void concatenarPilhas(struct Pilha *pilha1, struct Pilha pilha2) {
    struct Pilha copiaPilha2 = criarPilha();
    /** Copia os elementos da pilha2 para uma pilha temporária para manter a ordem correta **/
    while (!pilhaVazia(pilha2)) {
        inserirElemento(&copiaPilha2, pilha2.elementos[pilha2.topo]);
        removerElemento(&pilha2);
    }
    /** Concatena a pilha1 com a pilha temporária que contém os elementos da pilha2 **/
    while (!pilhaVazia(copiaPilha2)) {
        inserirElemento(pilha1, copiaPilha2.elementos[copiaPilha2.topo]);
        removerElemento(&copiaPilha2);
    }
    printf("Pilhas concatenadas:\n");
    exibirElementos(*pilha1);
}


/* Função do menu principal */
void menu() {
    struct Pilha pilha1 = criarPilha();
    struct Pilha pilha2 = criarPilha();
    int opcao;

    while (1) {
        printf("\nDigite 1 para inserir elemento na pilha 1 \n");
        printf("Digite 2 para remover elemento da pilha 1 \n");
        printf("Digite 3 para exibir elementos da pilha 1 \n");
        printf("Digite 4 para localizar um elemento na pilha 1 para consulta\n");
        printf("Digite 5 para localizar um elemento na pilha 1 para alteracao \n");
        printf("Digite 6 para buscar por padrão na pilha 1 \n");
        printf("Digite 7 para criar uma nova pilha \n");
        printf("Digite 8 para verificar se a pilha 1 esta vazia \n");
        printf("Digite 9 para verificar se a pilha 1 esta cheia \n");
        printf("Digite 10 para intercalar pilha 1 e pilha 2 \n");
        printf("Digite 11 para concatenar pilha 1 e pilha 2 \n");
        printf("Digite 12 para sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char elemento[100];
                printf("Digite o elemento a ser inserido na pilha 1: ");
                scanf(" %[^\n]", elemento);
                inserirElemento(&pilha1, elemento);
                break;
            }
            case 2:
                removerElemento(&pilha1);
                break;
            case 3:
                exibirElementos(pilha1);
                break;
            case 4: {
                char elemento[100];
                printf("Digite o elemento que deseja localizar na pilha 1: ");
                scanf(" %[^\n]", elemento);
                localizarElementoConsulta(pilha1, elemento);
                break;
            }
            case 5: {
                char elemento[100];
                printf("Digite o elemento que deseja alterar na pilha 1: ");
                scanf(" %[^\n]", elemento);
                localizarElementoAlteracao(&pilha1, elemento);
                break;
            }
            case 6: {
                char padrao[100];
                printf("Digite o padrao a ser buscado na pilha 1: ");
                scanf(" %[^\n]", padrao);
                buscarPorPadrao(pilha1, padrao);
                break;
            }
            case 7:
                pilha1 = criarPilha();
                printf("Uma nova pilha foi criada.\n");
                break;
            case 8:
                if (pilhaVazia(pilha1)) {
                    printf("A pilha 1 está vazia.\n");
                } else {
                    printf("A pilha 1 não está vazia.\n");
                }
                break;
            case 9:
                if (pilhaCheia(pilha1)) {
                    printf("A pilha 1 está cheia.\n");
                } else {
                    printf("A pilha 1 não está cheia.\n");
                }
                break;
            case 10:
                intercalarPilhas(pilha1, pilha2);
                break;
            case 11:
                concatenarPilhas(&pilha1, pilha2);
                break;
            case 12:
                printf("Saindo...\n");
                return;
            default:
                printf("Opcao invalida. Por favor, tente novamente.\n");
        }
    }
}

/* Função principal */
int main() {
    /* Chamada da função do menu principal */
    menu();

    return 0;
}

