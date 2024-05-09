#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 5 // Defina o número máximo de livros permitidos

// Define a estrutura Livro
struct Livro {
    char titulo[100]; // Título do livro
    struct Livro *prox; // Ponteiro para o próximo livro
};

// Declaracao de variavel global para o topo da pilha de livros
struct Livro *biblioteca = NULL;
struct Livro *pilha1 = NULL;
struct Livro *pilha2 = NULL; // Alterado de pilha

// Função para empilhar um novo livro na pilha
void empilharLivro(char titulo[], struct Livro **pilha) {
    struct Livro *novo_livro = (struct Livro *)malloc(sizeof(struct Livro));
    strcpy(novo_livro->titulo, titulo); // Copia o título do livro
    novo_livro->prox = *pilha; // O próximo será o antigo topo da pilha
    *pilha = novo_livro; // Atualiza o topo da pilha para o novo livro
}

// Função para adicionar livros na pilha
int inserirLivros(struct Livro **pilha) {
    char titulo[100];
    char continuar;
    int count = 0; // Contador para acompanhar o número de livros adicionados

    // Pedindo ao usuário para inserir livros até que ele decida parar ou atingir o limite
    do {
        // Verifica se atingiu o limite máximo de livros
        if (count == MAX_LIVROS) {
            printf("A pilha atingiu o limite máximo de livros.\n");
            break;
        }

        printf("Digite o titulo do livro: ");
        scanf(" %[^\n]", titulo); // Lê o título do livro (pode conter espaços)
        empilharLivro(titulo, pilha);
        count++; // Incrementa o contador de livros adicionados

        // Se atingiu o limite máximo de livros, sai do loop
        if (count == MAX_LIVROS) {
            printf("A pilha atingiu o limite máximo de livros.\n");
            break;
        }

        printf("Deseja adicionar outro livro? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    return 1;
}

// Função para verificar se a pilha está vazia e imprimir uma mensagem
int pilhaEstaVazia(struct Livro *pilha) {
    if (pilha == NULL) {
        printf("A pilha está vazia.\n");
        return 1; // Retorna 1 se a pilha estiver vazia
    }
    return 0; // Retorna 0 se a pilha não estiver vazia
}

// Função para verificar se a pilha está cheia e imprimir uma mensagem
int pilhaEstaCheia(struct Livro *pilha) {
    int count = 0;
    struct Livro *temp = pilha;

    // Conta o número de elementos na pilha
    while (temp != NULL) {
        count++;
        temp = temp->prox;
    }

    if (count >= MAX_LIVROS) {
        printf("A pilha está cheia.\n");
        return 1; // Retorna 1 se a pilha estiver cheia
    }
    return 0; // Retorna 0 se a pilha não estiver cheia
}

// Função para imprimir os livros da pilha
int imprimePilha(struct Livro *pilha) {
    // Percorrendo e imprimindo a pilha de livros
    struct Livro *temp = pilha;
    if (pilha == NULL) {
        printf("A pilha de livros está vazia.\n");
    } else {
        printf("\nLivros na pilha:\n");
        while (temp != NULL) {
            printf("Titulo: %s\n", temp->titulo);
            temp = temp->prox;
        }
    }

    return 0;
}

// Função para buscar por elementos que coincidam com um certo padrão na pilha
int buscarPorPadrao(char padrao[], struct Livro *pilha) {
    struct Livro *temp = pilha;
    int encontrados = 0;

    // Percorre a pilha de livros
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

// Função para desempilhar o título de um livro na pilha
int desempilharLivro(struct Livro **pilha) {
    if (*pilha == NULL) {
        printf("A pilha está vazia. Nenhum livro para remover.\n");
        return 0;
    }

    struct Livro *temp = *pilha;
    *pilha = temp->prox; // Atualiza o topo da pilha para o próximo livro
    free(temp); // Libera a memória do livro removido

    printf("O livro foi removido da pilha.\n");
    return 1;
}

// Função para alterar o título de um livro na pilha
int alterarLivro(char tituloAntigo[], char novoTitulo[], struct Livro *pilha) {
    struct Livro *temp = pilha;

    // Percorre a pilha até encontrar o livro ou chegar ao final
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

// Função para localizar um livro na pilha
int localizarLivro(char titulo[], struct Livro *pilha) {
    struct Livro *temp = pilha;
    int posicao = 1; // Inicia a posição do livro na pilha como 1
    char novoTitulo[100];

    // Percorre a pilha até encontrar o livro ou chegar ao final
    while (temp != NULL) {
        if (strcmp(temp->titulo, titulo) == 0) {
            printf("O livro '%s' foi encontrado na posição %d da pilha. \n", titulo, posicao);
            printf("Deseja alterar o título deste livro? (s/n): ");
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 's' || resposta == 'S') {
                printf("Digite o novo título: ");
                scanf(" %[^\n]", novoTitulo); // Lê o novo título do livro (pode conter espaços)
                alterarLivro(titulo, novoTitulo, pilha);
            }
            return 1; // Retorna 1 se o livro for encontrado
        }
        temp = temp->prox;
        posicao++;
    }

    // Se o livro não for encontrado, exibe uma mensagem
    printf("O livro '%s' não foi encontrado na pilha.\n", titulo);
    return 0;
}

// Função para destruir a pilha de livros
int destruirPilha(struct Livro **pilha) {
    struct Livro *atual = *pilha; // Ponteiro auxiliar que aponta para o topo da pilha
    struct Livro *proximo;
    
    // Loop de destruição da pilha
    while (atual != NULL) {
        proximo = atual->prox; // Salva o próximo livro em 'proximo' antes de remover o livro atual
        free(atual); // Libera a memória do livro atual
        atual = proximo; // Atualiza o ponteiro atual para o próximo livro
    }
    *pilha = NULL; // Define o topo da pilha como NULL

    printf("A pilha foi destruída.\n");

    return 0;
}

// Função para intercalar duas pilhas
struct Livro* intercalarPilhas(struct Livro* pilha1, struct Livro* pilha2) {
    struct Livro* resultado = NULL; // Inicializa a pilha de resultado
    struct Livro* temp1 = pilha1;
    struct Livro* temp2 = pilha2;

    while (temp1 != NULL || temp2 != NULL) {
        if (temp1 != NULL) {
            struct Livro* novoLivro1 = (struct Livro*)malloc(sizeof(struct Livro));
            strcpy(novoLivro1->titulo, temp1->titulo);
            novoLivro1->prox = resultado;
            resultado = novoLivro1;
            temp1 = temp1->prox;
        }
        if (temp2 != NULL) {
            struct Livro* novoLivro2 = (struct Livro*)malloc(sizeof(struct Livro));
            strcpy(novoLivro2->titulo, temp2->titulo);
            novoLivro2->prox = resultado;
            resultado = novoLivro2;
            temp2 = temp2->prox;
        }
    }

    return resultado;
}

// Função para concatenar duas pilhas
void concatenarPilhas(struct Livro** pilha1, struct Livro* pilha2) {
    if (*pilha1 == NULL) {
        *pilha1 = pilha2;
    } else {
        struct Livro* temp = *pilha1;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = pilha2;
    }
}

// Função para dividir uma pilha em duas
void dividirPilha(struct Livro* original, struct Livro** metade1, struct Livro** metade2) {
    *metade1 = NULL; // Inicializa as metades como NULL
    *metade2 = NULL;

    struct Livro* temp = original;
    int size = 0;

    // Conta o tamanho da pilha
    while (temp != NULL) {
        size++;
        temp = temp->prox;
    }

    // Calcula o tamanho de cada metade
    int half_size = size / 2;

    // Reinicializa o ponteiro temporário para o início da pilha
    temp = original;

    // Percorre a pilha original até o ponto médio
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

// Função para fazer uma cópia da pilha
struct Livro* copiarPilha(struct Livro* original) {
    struct Livro* copia = NULL; // Inicializa a cópia como NULL
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
// Função para adicionar um novo livro na segunda pilha
void inserirLivroPilha2(char titulo[]) {
    struct Livro *novo_livro = (struct Livro *)malloc(sizeof(struct Livro));
    strcpy(novo_livro->titulo, titulo); // Copia o título do livro
    novo_livro->prox = NULL; // O próximo será NULL, pois está sendo inserido no final da pilha

    // Se a pilha2 estiver vazia, o novo livro será o primeiro
    if (pilha2 == NULL) {
        pilha2 = novo_livro;
    } else {
        // Encontra o último livro na pilha2
        struct Livro *temp = pilha2;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        // Adiciona o novo livro no final da pilha2
        temp->prox = novo_livro;
    }
}

// Função para adicionar livros na segunda pilha
int inserirLivrosPilha2() {
    char titulo[100];
    char continuar;
    int count = 0; // Contador para acompanhar o número de livros adicionados

    // Pedindo ao usuário para inserir livros até que ele decida parar ou atingir o limite
    do {
        // Verifica se atingiu o limite máximo de livros
        if (count == MAX_LIVROS) {
            printf("A segunda pilha atingiu o limite máximo de livros.\n");
            break;
        }

        printf("Digite o titulo do livro para a segunda pilha: ");
        scanf(" %[^\n]", titulo); // Lê o título do livro (pode conter espaços)
        inserirLivroPilha2(titulo);
        count++; // Incrementa o contador de livros adicionados

        // Se atingiu o limite máximo de livros, sai do loop
        if (count == MAX_LIVROS) {
            printf("A segunda pilha atingiu o limite máximo de livros.\n");
            break;
        }

        printf("Deseja adicionar outro livro na segunda pilha? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    return 1;
}

// Função para remover um livro específico da pilha
int removerLivro(struct Livro **pilha) {
    if (*pilha == NULL) {
        printf("A pilha está vazia. Nenhum livro para remover.\n");
        return 0;
    }

    char titulo[100];
    printf("Digite o título do livro que deseja remover: ");
    scanf(" %[^\n]", titulo);

    struct Livro *atual = *pilha;
    struct Livro *anterior = NULL;

    // Procura o livro na pilha
    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            // Se o livro for encontrado, remove-o da pilha
            if (anterior == NULL) {
                // Se o livro a ser removido for o primeiro da pilha
                *pilha = atual->prox;
            } else {
                // Se o livro a ser removido estiver no meio ou no final da pilha
                anterior->prox = atual->prox;
            }
            free(atual); // Libera a memória do livro removido
            printf("O livro '%s' foi removido da pilha.\n", titulo);
            return 1;
        }
        // Atualiza os ponteiros para continuar procurando
        anterior = atual;
        atual = atual->prox;
    }

    // Se o livro não for encontrado, exibe uma mensagem
    printf("O livro '%s' não foi encontrado na pilha.\n", titulo);
    return 0;
}


// Função do menu principal
int menu() {
    int opcao;

    do { // Loop para exibir o menu repetidamente até que o usuário escolha sair
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
        printf("Digite 15para remover um livro da biblioteca\n");
        printf("Digite 16 para sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                inserirLivros(&biblioteca);
                break;
            case 2: 
                destruirPilha(&biblioteca); // Corrigido o nome da função
                break;
            case 3: 
                imprimePilha(biblioteca); // Corrigido o nome da função
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
                desempilharLivro(&biblioteca); // Corrigido o nome da função
                break;
            }
            case 8: {
                printf("Intercalando as duas pilhas...\n");
                struct Livro* resultado = intercalarPilhas(pilha1, pilha2);
                imprimePilha(resultado); // Corrigido o nome da função
                destruirPilha(&resultado); // Corrigido o nome da função e liberada a memória alocada para a pilha resultante
                break;
            }
            case 9: {
                printf("Concatenando as duas pilhas...\n");
                concatenarPilhas(&pilha1, pilha2);
                imprimePilha(pilha1); // Corrigido o nome da função
                break;
            }
            case 10: {
                printf("Dividindo a pilha...\n");
                struct Livro* metade1 = NULL;
                struct Livro* metade2 = NULL;
                dividirPilha(biblioteca, &metade1, &metade2); // Corrigido o nome da função
                printf("Metade 1:\n");
                imprimePilha(metade1);
                printf("Metade 2:\n");
                imprimePilha(metade2);
                destruirPilha(&metade1); // Corrigido o nome da função e liberada a memória alocada para a primeira metade
                destruirPilha(&metade2); // Corrigido o nome da função e liberada a memória alocada para a segunda metade
                break;
            }
            case 11: {
                printf("Copiando a pilha...\n");
                struct Livro* copia = copiarPilha(biblioteca); // Corrigido o nome da função
                imprimePilha(copia);
                destruirPilha(&copia); // Corrigido o nome da função e liberada a memória alocada para a cópia
                break;
            }
            case 12:
                inserirLivrosPilha2(); // Adiciona livros na segunda pilha
                break;
            case 13:
                pilhaEstaCheia(biblioteca); // Verifica se a pilha está cheia
                break;
            case 14:
                pilhaEstaVazia(biblioteca); // Verifica se a pilha está vazia
                break;
            case 15: // Caso o usuário escolha sair
                 removerLivro(&biblioteca);
                break;               
             case 16: 
                printf("Encerrando o programa...\n");
                break;
            default: // Se o usuário digitar uma opção inválida
                printf("Opcao invalida. Digite novamente.\n");
                break;
        }
    } while (opcao != 16); // O loop continua até que o usuário escolha sair

    return 0;
}


int main() {
    printf("Bem-vindo ao sistema de biblioteca!\n");
    menu(); // Chama a função do menu principal
    return 0;
}
