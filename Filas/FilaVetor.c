#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENTOS 100 /** Tamanho máximo do vetor **/

/** Estrutura Fila **/
struct Fila {
    char nomes[MAX_ELEMENTOS][100]; /** Vetor para armazenar todos os nomes **/
    int inicio; /** Início da fila **/
    int fim; /** Fim da fila **/
};

/** Função para criar uma nova fila **/
struct Fila criarFila() {
    struct Fila fila;
    fila.inicio = -1; /** Inicializa o início como -1 (fila vazia) **/
    fila.fim = -1; /** Inicializa o fim como -1 (fila vazia) **/
    return fila;
}

/** Função para destruir uma fila **/
void destruirFila(struct Fila *fila) {
    fila->inicio = -1; /** Define o início como -1 (fila vazia) **/
    fila->fim = -1; /** Define o fim como -1 (fila vazia) **/
    printf("Fila destruída. Todos os elementos foram removidos.\n");
}

/** Função para verificar se a fila está vazia **/
int filaVazia(struct Fila fila) {
    return fila.inicio == -1; /** Retorna 1 se o início for igual a -1 **/
}

/** Função para verificar se a fila está cheia **/
int filaCheia(struct Fila fila) {
    return (fila.fim + 1) % MAX_ELEMENTOS == fila.inicio; /** Retorna 1 se a próxima posição do fim for igual ao início **/
}

/** Função para inserir um elemento na fila **/
void inserirElemento(struct Fila *fila, char elemento[]) {
    if (!filaCheia(*fila)) {
        if (fila->inicio == -1) {
            fila->inicio = 0; /** Se a fila estiver vazia, define o início como 0 **/
        }
        fila->fim = (fila->fim + 1) % MAX_ELEMENTOS; /** Incrementa o fim **/
        strcpy(fila->nomes[fila->fim], elemento); /** Insere o elemento no fim **/
        printf("Elemento '%s' inserido na fila.\n", elemento);
    } else {
        printf("A fila está cheia. Elemento '%s' não foi inserido.\n", elemento);
    }
}

/** Função para remover um elemento da fila **/
void removerElemento(struct Fila *fila) {
    if (!filaVazia(*fila)) {
        printf("Elemento '%s' removido da fila.\n", fila->nomes[fila->inicio]); /** Remove o elemento do início **/
        fila->inicio = (fila->inicio + 1) % MAX_ELEMENTOS; /** Incrementa o início **/
        if (fila->inicio == (fila->fim + 1) % MAX_ELEMENTOS) {
            fila->inicio = -1; /** Se a fila ficar vazia após a remoção, define o início como -1 **/
            fila->fim = -1; /** Define o fim como -1 também **/
        }
    } else {
        printf("A fila está vazia. Nenhum elemento para remover.\n");
    }
}

/** Função para exibir os elementos da fila **/
void exibirElementos(struct Fila fila) {
    int i; /** Declaração da variável de iteração **/
    if (!filaVazia(fila)) {
        printf("\nElementos na fila:\n");
        int index = fila.inicio;
        do {
            printf("%s\n", fila.nomes[index]);
            index = (index + 1) % MAX_ELEMENTOS;
        } while (index != (fila.fim + 1) % MAX_ELEMENTOS);
    } else {
        printf("A fila está vazia. Nenhum elemento para exibir.\n");
    }
}

/** Função para localizar um elemento na fila para consulta **/
void localizarElemento(struct Fila fila, char elemento[]) {
    int index = fila.inicio; /** Início da fila **/
    if (!filaVazia(fila)) {
        do {
            if (strcmp(fila.nomes[index], elemento) == 0) {
                printf("O elemento '%s' foi encontrado na fila.\n", elemento);
                return;
            }
            index = (index + 1) % MAX_ELEMENTOS;
        } while (index != (fila.fim + 1) % MAX_ELEMENTOS);
        printf("O elemento '%s' não foi encontrado na fila.\n", elemento);
    } else {
        printf("A fila está vazia. Nenhum elemento para consultar.\n");
    }
}

/** Função para localizar um elemento na fila para alteração da informação **/
void alterarElemento(struct Fila *fila, char elementoAntigo[], char novoElemento[]) {
    int index = fila->inicio; /** Início da fila **/
    if (!filaVazia(*fila)) {
        do {
            if (strcmp(fila->nomes[index], elementoAntigo) == 0) {
                strcpy(fila->nomes[index], novoElemento); /** Altera o elemento na fila **/
                printf("O elemento '%s' foi alterado para '%s'.\n", elementoAntigo, novoElemento);
                return;
            }
            index = (index + 1) % MAX_ELEMENTOS;
        } while (index != (fila->fim + 1) % MAX_ELEMENTOS);
        printf("O elemento '%s' não foi encontrado na fila. Nenhuma alteração feita.\n", elementoAntigo);
    } else {
        printf("A fila está vazia. Nenhum elemento para alterar.\n");
    }
}

/** Função para buscar elementos que coincidam com um certo padrão na fila **/
void buscarPorPadrao(struct Fila fila, char padrao[]) {
    int index = fila.inicio; /** Início da fila **/
    if (!filaVazia(fila)) {
        printf("\nElementos na fila que coincidem com o padrão '%s':\n", padrao);
        do {
            if (strstr(fila.nomes[index], padrao) != NULL) {
                printf("%s\n", fila.nomes[index]);
            }
            index = (index + 1) % MAX_ELEMENTOS;
        } while (index != (fila.fim + 1) % MAX_ELEMENTOS);
    } else {
        printf("A fila está vazia. Nenhum elemento para buscar por padrão.\n");
    }
}

/** Função para intercalar duas filas **/
void intercalarFilas(struct Fila fila1, struct Fila fila2) {
    struct Fila resultado = criarFila();
    while (!filaVazia(fila1) || !filaVazia(fila2)) {
        if (!filaVazia(fila1)) {
            inserirElemento(&resultado, fila1.nomes[fila1.inicio]);
            fila1.inicio = (fila1.inicio + 1) % MAX_ELEMENTOS;
        }
        if (!filaVazia(fila2)) {
            inserirElemento(&resultado, fila2.nomes[fila2.inicio]);
            fila2.inicio = (fila2.inicio + 1) % MAX_ELEMENTOS;
        }
    }
    printf("Filas intercaladas:\n");
    exibirElementos(resultado);
}

/** Função para concatenar duas filas **/
void concatenarFilas(struct Fila *fila1, struct Fila fila2) {
    while (!filaVazia(fila2)) {
        inserirElemento(fila1, fila2.nomes[fila2.inicio]);
        fila2.inicio = (fila2.inicio + 1) % MAX_ELEMENTOS;
    }
    printf("Filas concatenadas:\n");
    exibirElementos(*fila1);
}

/** Função para dividir uma fila em duas **/
void dividirFila(struct Fila *fila) {
    if (!filaVazia(*fila)) {
        int metade = (fila->inicio + fila->fim + 1) / 2;
        struct Fila fila2 = criarFila(); /** Cria uma nova fila **/
        while (fila->inicio != metade) {
            inserirElemento(&fila2, fila->nomes[fila->inicio]);
            fila->inicio = (fila->inicio + 1) % MAX_ELEMENTOS;
        }
        printf("Fila dividida em duas:\n");
        printf("Fila 1:\n");
        exibirElementos(*fila);
        printf("Fila 2:\n");
        exibirElementos(fila2);
    } else {
        printf("A fila está vazia. Nada para dividir.\n");
    }
}

/** Função para fazer uma cópia da fila **/
struct Fila copiarFila(struct Fila fila) {
    struct Fila copia = criarFila();
    int index = fila.inicio; /** Início da fila **/
    if (!filaVazia(fila)) {
        do {
            inserirElemento(&copia, fila.nomes[index]);
            index = (index + 1) % MAX_ELEMENTOS;
        } while (index != (fila.fim + 1) % MAX_ELEMENTOS);
    }
    return copia;
}

/* Função do menu principal */
void menu() {
    struct Fila listaBiblioteca = criarFila();
    int opcao;

    while (1) {
        printf("\nDigite 1 para adicionar cliente na lista da biblioteca\n");
        printf("Digite 2 para remover cliente da lista da biblioteca\n");
        printf("Digite 3 para imprimir os clientes da lista da biblioteca\n");
        printf("Digite 4 para buscar cliente por padrão\n");
        printf("Digite 5 para localizar um cliente para consulta\n");
        printf("Digite 6 para alterar o nome de um cliente\n");
        printf("Digite 7 para intercalar duas filas de clientes\n");
        printf("Digite 8 para concatenar duas filas de clientes\n");
        printf("Digite 9 para dividir uma fila de clientes em duas\n");
        printf("Digite 10 para fazer uma cópia da fila de clientes\n");
        printf("Digite 11 para sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char nome[100];
                printf("Digite o nome do cliente a ser adicionado na lista da biblioteca: ");
                scanf(" %[^\n]", nome);
                inserirElemento(&listaBiblioteca, nome);
                break;
            }
            case 2:
                removerElemento(&listaBiblioteca);
                break;
            case 3:
                exibirElementos(listaBiblioteca);
                break;
            case 4: {
                char padrao[100];
                printf("Digite o padrão a ser buscado na lista da biblioteca: ");
                scanf(" %[^\n]", padrao);
                buscarPorPadrao(listaBiblioteca, padrao);
                break;
            }
            case 5: {
                char nome[100];
                printf("Digite o nome do cliente que deseja localizar na lista da biblioteca: ");
                scanf(" %[^\n]", nome);
                localizarElemento(listaBiblioteca, nome);
                break;
            }
            case 6: {
                char nomeAntigo[100], novoNome[100];
                printf("Digite o nome do cliente que deseja alterar na lista da biblioteca: ");
                scanf(" %[^\n]", nomeAntigo);
                printf("Digite o novo nome para o cliente '%s': ", nomeAntigo);
                scanf(" %[^\n]", novoNome);
                alterarElemento(&listaBiblioteca, nomeAntigo, novoNome);
                break;
            }
            case 7: {
                struct Fila segundaFila = criarFila();
                printf("Digite os nomes para a segunda fila (digite 'fim' para parar):\n");
                char nome[100];
                do {
                    printf("Nome: ");
                    scanf(" %[^\n]", nome);
                    if (strcmp(nome, "fim") != 0) {
                        inserirElemento(&segundaFila, nome);
                    }
                } while (strcmp(nome, "fim") != 0);
                intercalarFilas(listaBiblioteca, segundaFila);
                break;
            }
            case 8: {
                struct Fila segundaFila = criarFila();
                printf("Digite os nomes para a segunda fila (digite 'fim' para parar):\n");
                char nome[100];
                do {
                    printf("Nome: ");
                    scanf(" %[^\n]", nome);
                    if (strcmp(nome, "fim") != 0) {
                        inserirElemento(&segundaFila, nome);
                    }
                } while (strcmp(nome, "fim") != 0);
                concatenarFilas(&listaBiblioteca, segundaFila);
                break;
            }
            case 9:
                dividirFila(&listaBiblioteca);
                break;
            case 10: {
                struct Fila copia = copiarFila(listaBiblioteca);
                printf("Cópia da fila de clientes criada:\n");
                exibirElementos(copia);
                break;
            }
            case 11:
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
