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
struct Livro *fila1 = NULL;
struct Livro *fila2 = NULL; // Alterado de pilha para fila

// Função para inserir um novo livro na fila
void inserirLivro(char titulo[], struct Livro **fila) {
    struct Livro *novo_livro = (struct Livro *)malloc(sizeof(struct Livro));
    strcpy(novo_livro->titulo, titulo); // Copia o título do livro
    novo_livro->prox = NULL; // O próximo será NULL, pois está sendo inserido no final da fila

    // Se a fila estiver vazia, o novo livro será o primeiro
    if (*fila == NULL) {
        *fila = novo_livro;
    } else {
        // Encontra o último livro na fila
        struct Livro *temp = *fila;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        // Adiciona o novo livro no final da fila
        temp->prox = novo_livro;
    }
}

// Função para adicionar livros na fila
int inserirLivros(struct Livro **fila) {
    char titulo[100];
    char continuar;
    int count = 0; // Contador para acompanhar o número de livros adicionados

    // Pedindo ao usuário para inserir livros até que ele decida parar ou atingir o limite
    do {
        // Verifica se atingiu o limite máximo de livros
        if (count == MAX_LIVROS) {
            printf("A fila atingiu o limite máximo de livros.\n");
            break;
        }

        printf("Digite o titulo do livro: ");
        scanf(" %[^\n]", titulo); // Lê o título do livro (pode conter espaços)
        inserirLivro(titulo, fila);
        count++; // Incrementa o contador de livros adicionados

        // Se atingiu o limite máximo de livros, sai do loop
        if (count == MAX_LIVROS) {
            printf("A fila atingiu o limite máximo de livros.\n");
            break;
        }

        printf("Deseja adicionar outro livro? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    return 1;
}

// Função para imprimir os livros da fila
int imprimeFila(struct Livro *fila) {
    // Percorrendo e imprimindo a fila de livros
    struct Livro *temp = fila;
    if (fila == NULL) {
        printf("A fila de livros está vazia.\n");
    } else {
        printf("\nLivros na fila:\n");
        while (temp != NULL) {
            printf("Titulo: %s\n", temp->titulo);
            temp = temp->prox;
        }
    }

    return 0;
}

// Função para buscar por elementos que coincidam com um certo padrão na fila
int buscarPorPadrao(char padrao[], struct Livro *fila) {
    struct Livro *temp = fila;
    int encontrados = 0;

    // Percorre a fila de livros
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
        printf("Nenhum livro encontrado com o padrão '%s'.\n", padrao);
    }

    return encontrados; // Retorna o número de livros encontrados com o padrão especificado
}

// Função para remover o título de um livro na fila
int removerLivro(char titulo[], struct Livro **fila) {
    struct Livro *atual = *fila;
    struct Livro *anterior = NULL;

    // Percorre a fila até encontrar o livro ou chegar ao final
    while (atual != NULL) {
        // Verifica se o livro atual é o que deseja remover
        if (strcmp(atual->titulo, titulo) == 0) {
            // Se o livro a ser removido estiver no início da fila
            if (anterior == NULL) {
                *fila = atual->prox; // Atualiza o início da fila
            } else {
                anterior->prox = atual->prox; // Atualiza o ponteiro do livro anterior para apontar para o próximo livro
            }
            free(atual); // Libera a memória do livro removido
            printf("O livro '%s' foi removido.\n", titulo);
            return 1; // Retorna 1 se o livro for encontrado e removido
        }
        anterior = atual;
        atual = atual->prox;
    }

    // Se o livro não for encontrado, exibe uma mensagem
    printf("O livro '%s' não foi encontrado.\n", titulo);
    return 0;
}

// Função para alterar o título de um livro na fila
int alterarLivro(char tituloAntigo[], char novoTitulo[], struct Livro *fila) {
    struct Livro *temp = fila;

    // Percorre a fila até encontrar o livro ou chegar ao final
    while (temp != NULL) {
        if (strcmp(temp->titulo, tituloAntigo) == 0) {
            strcpy(temp->titulo, novoTitulo); // Altera o título do livro
            printf("O livro '%s' foi alterado para '%s'.\n", tituloAntigo, novoTitulo);
            return 1; // Retorna 1 se o livro for encontrado e alterado
        }
        temp = temp->prox;
    }

    // Se o livro não for encontrado, exibe uma mensagem
    printf("O livro '%s' não foi encontrado.\n", tituloAntigo);
    return 0;
}

// Função para localizar um livro na fila
int localizarLivro(char titulo[], struct Livro *fila) {
    struct Livro *temp = fila;
    int posicao = 1; // Inicia a posição do livro na fila como 1
    char novoTitulo[100];

    // Percorre a fila até encontrar o livro ou chegar ao final
    while (temp != NULL) {
        if (strcmp(temp->titulo, titulo) == 0) {
            printf("O livro '%s' foi encontrado na posição %d da fila. \n", titulo, posicao);
            printf("Deseja alterar o título deste livro? (s/n): ");
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S') {
                printf("Digite o novo título: ");
                scanf(" %[^\n]", novoTitulo); // Lê o novo título do livro (pode conter espaços)
                alterarLivro(titulo, novoTitulo, fila);
            }
            return 1; // Retorna 1 se o livro for encontrado
        }
        temp = temp->prox;
        posicao++;
    }

    // Se o livro não for encontrado, exibe uma mensagem
    printf("O livro '%s' não foi encontrado na fila.\n", titulo);
    return 0;
}

// Função para destruir a fila de livros
int destruirFila(struct Livro **fila) {
    struct Livro *atual = *fila; // Ponteiro auxiliar que aponta para o início da fila
    struct Livro *proximo;
    
    // Loop de destruição da fila
    while (atual != NULL) {
        proximo = atual->prox; // Salva o próximo livro em 'proximo' antes de remover o livro atual
        free(atual); // Libera a memória do livro atual
        atual = proximo; // Atualiza o ponteiro atual para o próximo livro
    }
    *fila = NULL; // Define o ponteiro inicial da fila como NULL

    printf("A fila foi destruída.\n");

    return 0;
}

// Função para intercalar duas filas
struct Livro* intercalarFilas(struct Livro* fila1, struct Livro* fila2) {
    struct Livro* resultado = NULL;
    struct Livro* temp1 = fila1;
    struct Livro* temp2 = fila2;

    while (temp1 != NULL || temp2 != NULL) {
        if (temp1 != NULL) {
            struct Livro* novoLivro = (struct Livro*)malloc(sizeof(struct Livro));
            strcpy(novoLivro->titulo, temp1->titulo);
            novoLivro->prox = resultado;
            resultado = novoLivro;
            temp1 = temp1->prox;
        }
        if (temp2 != NULL) {
            struct Livro* novoLivro = (struct Livro*)malloc(sizeof(struct Livro));
            strcpy(novoLivro->titulo, temp2->titulo);
            novoLivro->prox = resultado;
            resultado = novoLivro;
            temp2 = temp2->prox;
        }
    }

    return resultado;
}

// Função para concatenar duas filas
void concatenarFilas(struct Livro** fila1, struct Livro* fila2) {
    if (*fila1 == NULL) {
        *fila1 = fila2;
    } else {
        struct Livro* temp = *fila1;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = fila2;
    }
}

// Função para fazer uma cópia da fila
struct Livro* copiarFila(struct Livro* original) {
    struct Livro* copia = NULL;
    struct Livro* temp = original;
    struct Livro* temp_copia = NULL; // Ponteiro para percorrer a cópia

    while (temp != NULL) {
        struct Livro* novoLivro = (struct Livro*)malloc(sizeof(struct Livro));
        strcpy(novoLivro->titulo, temp->titulo);
        novoLivro->prox = NULL;

        if (copia == NULL) {
            copia = novoLivro;
            temp_copia = copia;
        } else {
            temp_copia->prox = novoLivro;
            temp_copia = temp_copia->prox;
        }

        temp = temp->prox;
    }

    return copia;
}

// Função para dividir uma fila em duas
void dividirFila(struct Livro* original, struct Livro** metade1, struct Livro** metade2) {
    struct Livro* temp = original;
    int size = 0;
    
    // Conta o tamanho da fila
    while (temp != NULL) {
        size++;
        temp = temp->prox;
    }
    
    // Calcula o tamanho de cada metade
    int half_size = size / 2;
    
    // Reinicializa o ponteiro temporário para o início da fila
    temp = original;

    // Percorre a fila original até o ponto médio
    for (int i = 0; i < half_size; i++) {
        struct Livro* novoLivro = (struct Livro*)malloc(sizeof(struct Livro));
        strcpy(novoLivro->titulo, temp->titulo);
        novoLivro->prox = NULL;

        if (*metade1 == NULL) {
            *metade1 = novoLivro;
        } else {
            struct Livro* temp1 = *metade1;
            while (temp1->prox != NULL) {
                temp1 = temp1->prox;
            }
            temp1->prox = novoLivro;
        }
        temp = temp->prox;
    }
    
    // Atribui a segunda metade ao segundo ponteiro
    *metade2 = temp;
}

// Função para adicionar um novo livro na segunda fila
void inserirLivroFila2(char titulo[]) {
    struct Livro *novo_livro = (struct Livro *)malloc(sizeof(struct Livro));
    strcpy(novo_livro->titulo, titulo); // Copia o título do livro
    novo_livro->prox = NULL; // O próximo será NULL, pois está sendo inserido no final da fila

    // Se a fila2 estiver vazia, o novo livro será o primeiro
    if (fila2 == NULL) {
        fila2 = novo_livro;
    } else {
        // Encontra o último livro na fila2
        struct Livro *temp = fila2;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        // Adiciona o novo livro no final da fila2
        temp->prox = novo_livro;
    }
}

// Função para adicionar livros na segunda fila
int inserirLivrosFila2() {
    char titulo[100];
    char continuar;
    int count = 0; // Contador para acompanhar o número de livros adicionados

    // Pedindo ao usuário para inserir livros até que ele decida parar ou atingir o limite
    do {
        // Verifica se atingiu o limite máximo de livros
        if (count == MAX_LIVROS) {
            printf("A segunda fila atingiu o limite máximo de livros.\n");
            break;
        }

        printf("Digite o titulo do livro para a segunda fila: ");
        scanf(" %[^\n]", titulo); // Lê o título do livro (pode conter espaços)
        inserirLivroFila2(titulo);
        count++; // Incrementa o contador de livros adicionados

        // Se atingiu o limite máximo de livros, sai do loop
        if (count == MAX_LIVROS) {
            printf("A segunda fila atingiu o limite máximo de livros.\n");
            break;
        }

        printf("Deseja adicionar outro livro na segunda fila? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    return 1;
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
        printf("Digite 8 para intercalar duas filas\n");
        printf("Digite 9 para concatenar duas filas\n");
        printf("Digite 10 para dividir uma fila em duas\n");
        printf("Digite 11 para fazer uma copia da fila\n");
        printf("Digite 12 para adicionar livros na segunda fila\n");
        printf("Digite 13 para sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                inserirLivros(&biblioteca);
                break;
            case 2: 
                destruirFila(&biblioteca);
                break;
            case 3: 
                imprimeFila(biblioteca);
                break;
            case 4: {
                char titulo[100];
                printf("Digite o titulo do livro que deseja localizar: ");
                scanf(" %[^\n]", titulo); // Lê o título do livro (pode conter espaços)
                localizarLivro(titulo, biblioteca);
                break;
            }
            case 5: {
                char tituloAntigo[100], novoTitulo[100];
                printf("Digite o titulo do livro que deseja alterar: ");
                scanf(" %[^\n]", tituloAntigo); // Lê o título do livro (pode conter espaços)
                printf("Digite o novo titulo: ");
                scanf(" %[^\n]", novoTitulo); // Lê o novo título do livro (pode conter espaços)
                alterarLivro(tituloAntigo, novoTitulo, biblioteca);
                break;
            }
            case 6: {
                char padrao[100];
                printf("Digite o padrao de busca: ");
                scanf(" %[^\n]", padrao); // Lê o padrão de busca
                buscarPorPadrao(padrao, biblioteca);
                break;
            }
            case 7: {
                char titulo[100];
                printf("Digite o titulo do livro que deseja remover: ");
                scanf(" %[^\n]", titulo); // Lê o título do livro (pode conter espaços)
                removerLivro(titulo, &biblioteca);
                break;
            }
            case 8: {
                printf("Intercalando as duas filas...\n");
                struct Livro* resultado = intercalarFilas(fila1, fila2);
                imprimeFila(resultado);
                destruirFila(&resultado); // Libera a memória alocada para a fila resultante
                break;
            }
            case 9: {
                printf("Concatenando as duas filas...\n");
                concatenarFilas(&fila1, fila2);
                imprimeFila(fila1);
                break;
            }
            case 10: {
                struct Livro* metade1 = NULL;
                struct Livro* metade2 = NULL;
                dividirFila(biblioteca, &metade1, &metade2);
                printf("Primeira metade:\n");
                imprimeFila(metade1);
                printf("Segunda metade:\n");
                imprimeFila(metade2);
                destruirFila(&metade1); // Libera a memória alocada para a primeira metade
                break;
            }
            case 11: {
                struct Livro* copia = copiarFila(biblioteca);
                printf("Copia da fila:\n");
                imprimeFila(copia);
                destruirFila(&copia); // Libera a memória alocada para a cópia
                break;
            }
            case 12: 
                inserirLivrosFila2();
                break;
            case 13:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}

// Função principal
int main() {
    menu(); // Chama a função do menu
    return 0;
}
