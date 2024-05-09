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
    pilha.topo = -1; /** Inicializa o topo como -1 (pilha vazia) **/

    return pilha;
}

/** Função para verificar se a pilha está vazia **/
int pilhaVazia(struct Pilha pilha) {
    return pilha.topo == -1; /** Retorna 1 se o topo for igual a -1 **/
}

/** Função para verificar se a pilha está cheia **/
int pilhaCheia(struct Pilha pilha) {
    return pilha.topo == MAX_ELEMENTOS - 1; /** Retorna 1 se o topo for igual ao tamanho máximo - 1 **/
}

/** Função para adicionar um livro à pilha **/
void adicionarLivro(struct Pilha *pilha, char livro[]) {
    if (!pilhaCheia(*pilha)) {
        pilha->topo++; /** Incrementa o topo **/
        strcpy(pilha->elementos[pilha->topo], livro); /** Adiciona o livro no topo **/
        printf("Livro '%s' adicionado à biblioteca.\n", livro);
    } else {
        printf("A biblioteca está cheia. Livro '%s' não foi adicionado.\n", livro);
    }
}

/** Função para destruir a biblioteca (limpar a pilha) **/
void destruirBiblioteca(struct Pilha *pilha) {
    pilha->topo = -1; /** Define o topo como -1 (pilha vazia) **/
    printf("Biblioteca destruída. Todos os livros foram removidos.\n");
}

/** Função para imprimir os livros da biblioteca **/
void imprimirLivros(struct Pilha pilha) {
    int i; /** Declaração da variável de iteração **/
    if (!pilhaVazia(pilha)) {
        printf("\nLivros na biblioteca:\n");
        for (i = pilha.topo; i >= 0; i--) {
            printf("%s\n", pilha.elementos[i]);
        }
    } else {
        printf("A biblioteca está vazia. Nenhum livro para imprimir.\n");
    }
}

/** Função para localizar um livro na biblioteca para consulta **/
void localizarLivro(struct Pilha pilha, char livro[]) {
    int i; /** Declaração da variável de iteração **/
    if (!pilhaVazia(pilha)) {
        for (i = pilha.topo; i >= 0; i--) {
            if (strcmp(pilha.elementos[i], livro) == 0) {
                printf("O livro '%s' foi encontrado na biblioteca no topo da pilha.\n", livro);
                return;
            }
        }
        printf("O livro '%s' não foi encontrado na biblioteca.\n", livro);
    } else {
        printf("A biblioteca está vazia. Nenhum livro para consultar.\n");
    }
}

/** Função para alterar o título de um livro na biblioteca **/
void alterarTituloLivro(struct Pilha *pilha, char livro[]) {
    int i; /** Declaração da variável de iteração **/
    if (!pilhaVazia(*pilha)) {
        for (i = pilha->topo; i >= 0; i--) {
            if (strcmp(pilha->elementos[i], livro) == 0) {
                printf("Digite o novo título para o livro '%s': ", livro);
                scanf(" %[^\n]", pilha->elementos[i]); /** Lê o novo título para o livro **/
                printf("O título do livro '%s' foi alterado para '%s'.\n", livro, pilha->elementos[i]);
                return;
            }
        }
        printf("O livro '%s' não foi encontrado na biblioteca. Nenhuma alteração feita.\n", livro);
    } else {
        printf("A biblioteca está vazia. Nenhum livro para alterar.\n");
    }
}

/** Função para buscar por livros que coincidam com um certo padrão na biblioteca **/
void buscarPorPadrao(struct Pilha pilha, char padrao[]) {
    int i; /** Declaração da variável de iteração **/
    if (!pilhaVazia(pilha)) {
        printf("\nLivros na biblioteca que coincidem com o padrão '%s':\n", padrao);
        for (i = pilha.topo; i >= 0; i--) {
            if (strstr(pilha.elementos[i], padrao) != NULL) {
                printf("%s\n", pilha.elementos[i]);
            }
        }
    } else {
        printf("A biblioteca está vazia. Nenhum livro para buscar por padrão.\n");
    }
}

/** Função para remover um livro da biblioteca **/
void removerLivro(struct Pilha *pilha) {
    if (!pilhaVazia(*pilha)) {
        printf("Livro '%s' removido da biblioteca.\n", pilha->elementos[pilha->topo]); /** Remove o livro do topo **/
        pilha->topo--; /** Decrementa o topo **/
    } else {
        printf("A biblioteca está vazia. Nenhum livro para remover.\n");
    }
}

/** Função para intercalar duas pilhas **/
void intercalarPilhas(struct Pilha pilha1, struct Pilha pilha2) {
    struct Pilha resultado = criarPilha();
    while (!pilhaVazia(pilha1) || !pilhaVazia(pilha2)) {
        if (!pilhaVazia(pilha1)) {
            adicionarLivro(&resultado, pilha1.elementos[pilha1.topo]);
            pilha1.topo--;
        }
        if (!pilhaVazia(pilha2)) {
            adicionarLivro(&resultado, pilha2.elementos[pilha2.topo]);
            pilha2.topo--;
        }
    }
    printf("Pilhas intercaladas:\n");
    imprimirLivros(resultado);
}

/** Função para concatenar duas pilhas **/
void concatenarPilhas(struct Pilha *pilha1, struct Pilha pilha2) {
    while (!pilhaVazia(pilha2)) {
        adicionarLivro(pilha1, pilha2.elementos[pilha2.topo]);
        pilha2.topo--;
    }
    printf("Pilhas concatenadas:\n");
    imprimirLivros(*pilha1);
}

/** Função para dividir uma pilha em duas **/
void dividirPilha(struct Pilha *pilha) {
    if (!pilhaVazia(*pilha)) {
        int metade = pilha->topo / 2;
        struct Pilha pilha2 = criarPilha(); /** Cria uma nova pilha **/
        while (pilha->topo > metade) {
            adicionarLivro(&pilha2, pilha->elementos[pilha->topo]);
            pilha->topo--;
        }
        printf("Pilha dividida em duas:\n");
        printf("Pilha 1:\n");
        imprimirLivros(*pilha);
        printf("Pilha 2:\n");
        imprimirLivros(pilha2);
    } else {
        printf("A biblioteca está vazia. Nada para dividir.\n");
    }
}

/** Função para fazer uma cópia da pilha **/
struct Pilha copiarPilha(struct Pilha pilha) {
    struct Pilha copia = criarPilha();
    int i; /** Declaração da variável de iteração **/
    for (i = pilha.topo; i >= 0; i--) {
        adicionarLivro(&copia, pilha.elementos[i]);
    }
    return copia;
}

/* Função do menu principal */
void menu() {
    struct Pilha biblioteca = criarPilha();
    int opcao;

    while (1) {
        printf("\nDigite 1 para adicionar livros na biblioteca\n");
        printf("Digite 2 para destruir a biblioteca\n");
        printf("Digite 3 para imprimir os livros da biblioteca\n");
        printf("Digite 4 para localizar um livro na biblioteca\n");
        printf("Digite 5 para alterar o titulo de um livro na biblioteca\n");
        printf("Digite 6 para buscar por padrao\n");
        printf("Digite 7 para remover um livro da biblioteca\n");
        printf("Digite 8 para intercalar duas pilhas\n");
        printf("Digite 9 para concatenar duas pilhas\n");
        printf("Digite 10 para dividir uma pilha em duas\n");
        printf("Digite 11 para fazer uma copia da pilha\n");
        printf("Digite 12 para adicionar livros na segunda pilha\n");
        printf("Digite 13 para verificar se a pilha está cheia\n");
        printf("Digite 14 para verificar se a pilha está vazia\n");
        printf("Digite 15 para remover um livro da biblioteca\n");
        printf("Digite 16 para sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char livro[100];
                printf("Digite o nome do livro a ser adicionado na biblioteca: ");
                scanf(" %[^\n]", livro);
                adicionarLivro(&biblioteca, livro);
                break;
            }
            case 2:
                destruirBiblioteca(&biblioteca);
                break;
            case 3:
                imprimirLivros(biblioteca);
                break;
            case 4: {
                char livro[100];
                printf("Digite o nome do livro que deseja localizar na biblioteca: ");
                scanf(" %[^\n]", livro);
                localizarLivro(biblioteca, livro);
                break;
            }
            case 5: {
                char livro[100];
                printf("Digite o nome do livro que deseja alterar na biblioteca: ");
                scanf(" %[^\n]", livro);
                alterarTituloLivro(&biblioteca, livro);
                break;
            }
            case 6: {
                char padrao[100];
                printf("Digite o padrão a ser buscado na biblioteca: ");
                scanf(" %[^\n]", padrao);
                buscarPorPadrao(biblioteca, padrao);
                break;
            }
            case 7:
                removerLivro(&biblioteca);
                break;
            case 8: {
                struct Pilha segundaPilha = criarPilha();
                printf("Digite os livros para a segunda pilha (digite 'fim' para parar):\n");
                char livro[100];
                do {
                    printf("Livro: ");
                    scanf(" %[^\n]", livro);
                    if (strcmp(livro, "fim") != 0) {
                        adicionarLivro(&segundaPilha, livro);
                    }
                } while (strcmp(livro, "fim") != 0);
                intercalarPilhas(biblioteca, segundaPilha);
                break;
            }
            case 9: {
                struct Pilha segundaPilha = criarPilha();
                printf("Digite os livros para a segunda pilha (digite 'fim' para parar):\n");
                char livro[100];
                do {
                    printf("Livro: ");
                    scanf(" %[^\n]", livro);
                    if (strcmp(livro, "fim") != 0) {
                        adicionarLivro(&segundaPilha, livro);
                    }
                } while (strcmp(livro, "fim") != 0);
                concatenarPilhas(&biblioteca, segundaPilha);
                break;
            }
            case 10:
                dividirPilha(&biblioteca);
                break;
            case 11: {
                struct Pilha copia = copiarPilha(biblioteca);
                printf("Cópia da pilha criada:\n");
                imprimirLivros(copia);
                break;
            }
            case 12: {
                char livro[100];
                printf("Digite o nome do livro a ser adicionado na segunda pilha: ");
                scanf(" %[^\n]", livro);
                adicionarLivro(&biblioteca, livro);
                break;
            }
            case 13:
                if (pilhaCheia(biblioteca)) {
                    printf("A biblioteca está cheia.\n");
                } else {
                    printf("A biblioteca não está cheia.\n");
                }
                break;
            case 14:
                if (pilhaVazia(biblioteca)) {
                    printf("A biblioteca está vazia.\n");
                } else {
                    printf("A biblioteca não está vazia.\n");
                }
                break;
            case 15:
                removerLivro(&biblioteca);
                break;
            case 16:
                printf("Saindo...\n");
                return;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
        }
    }
}

/* Função principal */
int main() {
    /* Chamada da função do menu principal */
    menu();

    return 0;
}
