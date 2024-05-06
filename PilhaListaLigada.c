#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 5 // Defina o número máximo de livros permitidos

// Define a estrutura Livro
struct Livro {
    char titulo[100]; // Título do livro
    struct Livro *prox; // Ponteiro para o próximo livro
};

// Declaracao de variavel global para o início da lista de livros
struct Livro *biblioteca = NULL;

// Função para inserir um novo livro na lista
void inserirLivro(char titulo[]) {
    struct Livro *novo_livro = (struct Livro *)malloc(sizeof(struct Livro));
    strcpy(novo_livro->titulo, titulo); // Copia o título do livro
    novo_livro->prox = biblioteca; // Insere no início da lista
    biblioteca = novo_livro;
}

// Função para inserir os livros na lista 
int inserirLivros() {
    char titulo[100];
    char continuar;
    int count = 0; // Contador para acompanhar o número de livros adicionados

    // Pedindo ao usuário para inserir livros até que ele decida parar ou atingir o limite
    do {
        // Verifica se atingiu o limite máximo de livros
        if (count == MAX_LIVROS) {
            printf("A biblioteca atingiu o limite máximo de livros.\n");
            break;
        }

        printf("Digite o titulo do livro: ");
        scanf(" %[^\n]", titulo); // Lê o título do livro (pode conter espaços)
        inserirLivro(titulo);
        count++; // Incrementa o contador de livros adicionados

        // Se atingiu o limite máximo de livros, sai do loop
        if (count == MAX_LIVROS) {
            printf("A biblioteca atingiu o limite máximo de livros.\n");
            break;
        }

        printf("Deseja adicionar outro livro? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    return 1;
}

// Função para imprimir os livros da biblioteca
int imprimeBiblioteca() {
    // Percorrendo e imprimindo a lista de livros
    struct Livro *temp = biblioteca;
    if (biblioteca == NULL) {
        printf("A biblioteca está vazia.\n");
    } else {
        printf("\nLivros na biblioteca:\n");
        while (temp != NULL) {
            printf("Titulo: %s\n", temp->titulo);
            temp = temp->prox;
        }
    }

    return 0;
}

// Função para buscar por elementos que coincidam com um certo padrão
int buscarPorPadrao(char padrao[]) {
    struct Livro *temp = biblioteca;
    int encontrados = 0;

    // Percorre a lista de livros
    while (temp != NULL) {
        // Verifica se o título do livro contém o padrão especificado
        if (strstr(temp->titulo, padrao) != NULL) {
            printf("Livro encontrado: %s\n", temp->titulo);
            encontrados++;
        }
        temp = temp->prox;
    }

    // Se nenhum livro for encontrado, exibe uma mensagem
    if (encontrados == 0) {
        printf("Nenhum livro encontrado com o padrao '%s'.\n", padrao);
    }

    return encontrados; // Retorna o número de livros encontrados com o padrão especificado
}

// Função para remover o título de um livro na biblioteca
int removerLivro(char titulo[]) {
    struct Livro *atual = biblioteca;
    struct Livro *anterior = NULL;

    // Percorre a lista até encontrar o livro ou chegar ao final
    while (atual != NULL) {
        // Verifica se o livro atual é o que deseja remover
        if (strcmp(atual->titulo, titulo) == 0) {
            // Se o livro a ser removido estiver no início da lista
            if (anterior == NULL) {
                biblioteca = atual->prox; // Atualiza o início da lista
            } else {
                anterior->prox = atual->prox; // Atualiza o ponteiro do livro anterior para apontar para o próximo livro
            }
            free(atual); // Libera a memória do livro removido
            printf("O livro '%s' foi removido da biblioteca.\n", titulo);
            return 1; // Retorna 1 se o livro for encontrado e removido
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Se o livro não for encontrado, exibe uma mensagem
    printf("O livro '%s' nao foi encontrado na biblioteca.\n", titulo);
    return 0;
}

// Função para alterar o título de um livro na biblioteca
int alterarLivro(char tituloAntigo[], char novoTitulo[]) {
    struct Livro *temp = biblioteca;

    // Percorre a lista até encontrar o livro ou chegar ao final
    while (temp != NULL) {
        if (strcmp(temp->titulo, tituloAntigo) == 0) {
            strcpy(temp->titulo, novoTitulo); // Altera o título do livro
            printf("O livro '%s' foi alterado para '%s'.\n", tituloAntigo, novoTitulo);
            return 1; // Retorna 1 se o livro for encontrado e alterado
        }
        temp = temp->prox;
    }

    // Se o livro não for encontrado, exibe uma mensagem
    printf("O livro '%s' nao foi encontrado na biblioteca.\n", tituloAntigo);
    return 0;
}

// Função para localizar um livro na biblioteca
int localizarLivro(char titulo[]) {
    struct Livro *temp = biblioteca;
    int posicao = 1; // Inicia a posição do livro na lista como 1
    char novoTitulo[100];

    // Percorre a lista até encontrar o livro ou chegar ao final
    while (temp != NULL) {
        if (strcmp(temp->titulo, titulo) == 0) {
            printf("O livro '%s' foi encontrado na posicao %d da biblioteca. \n", titulo, posicao);
            printf("Deseja alterar o titulo deste livro? (s/n): ");
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S') {
                printf("Digite o novo titulo: ");
                scanf(" %[^\n]", novoTitulo); // Lê o novo título do livro (pode conter espaços)
                alterarLivro(titulo, novoTitulo);
            }
            return 1; // Retorna 1 se o livro for encontrado
        }
        temp = temp->prox;
        posicao++;
    }

    // Se o livro não for encontrado, exibe uma mensagem
    printf("O livro '%s' nao foi encontrado na biblioteca.\n", titulo);
    return 0;
}

// Função para destruir a biblioteca
int destruirBiblioteca() {
    struct Livro *atual = biblioteca; // Ponteiro auxiliar que aponta para o início da lista
    struct Livro *proximo;
    
    // Loop de destruição da biblioteca 
    while (atual != NULL) {
        proximo = atual->prox; // Salva o próximo livro em 'proximo' antes de remover o livro atual
        free(atual); // Libera a memória do livro atual
        atual = proximo; // Atualiza o ponteiro atual para o próximo livro
    }
    biblioteca = NULL; // Define o ponteiro inicial da biblioteca como NULL

    printf("A biblioteca foi destruida.\n");

    return 0;
}

// Função do menu principal
int menu() {
    int opcao;

    while (1) { // Loop para exibir o menu repetidamente
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
        printf("Digite 12 para sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                inserirLivros();
                break;
            case 2:
                destruirBiblioteca();
                break;
            case 3:
                imprimeBiblioteca();
                break;
            case 4: {
                char titulo[100];
                printf("Digite o titulo do livro que deseja localizar: ");
                scanf(" %[^\n]", titulo); // Lê o título do livro (pode conter espaços)
                localizarLivro(titulo);
                break;
            }
            case 5: {
                char tituloAntigo[100], novoTitulo[100];
                printf("Digite o titulo do livro que deseja alterar: ");
                scanf(" %[^\n]", tituloAntigo); // Lê o título antigo do livro
                printf("Digite o novo titulo para o livro: ");
                scanf(" %[^\n]", novoTitulo); // Lê o novo título do livro
                alterarLivro(tituloAntigo, novoTitulo);
                break;
            }
            case 6: {
                char padrao[100];
                printf("Digite o padrao que deseja buscar nos titulos dos livros: ");
                scanf(" %[^\n]", padrao); // Lê o padrão a ser buscado
                buscarPorPadrao(padrao);
                break;
            }
            case 7: {
                char titulo[100];
                printf("Digite o titulo do livro que deseja remover: ");
                scanf(" %[^\n]", titulo); // Lê o título do livro (pode conter espaços)
                removerLivro(titulo);
                break;
            }
            case 8: {
                struct Livro* resultado = intercalarPilhas(pilha1, pilha2);
                printf("Pilhas intercaladas:\n");
                imprimirPilha(resultado);
                break;
            }
            case 9: {
                concatenarPilhas(&pilha1, pilha2);
                printf("Pilhas concatenadas:\n");
                imprimirPilha(pilha1);
                break;
            }
            case 10: {
                struct Livro* metade1 = NULL;
                struct Livro* metade2 = NULL;
                dividirPilha(biblioteca, &metade1, &metade2);
                printf("Pilha dividida:\n");
                printf("Metade 1:\n");
                imprimirPilha(metade1);
                printf("Metade 2:\n");
                imprimirPilha(metade2);
                break;
            }
            case 11: {
                struct Livro* copia = copiarPilha(biblioteca);
                printf("Copia da pilha criada:\n");
                imprimirPilha(copia);
                break;
            }
            case 12:
                printf("Saindo...\n");
                return 0; // Sai da função main()
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
