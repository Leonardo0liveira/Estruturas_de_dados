#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/** Definição da estrutura para um nó da lista ligada */
struct No {
    char dado[5];
    struct No *proximo;
};
/** Definição da estrutura para a fila com lista ligada */
struct FilaListaLigada {
    struct No *frente;
    struct No *tras;
};

struct FilaListaLigada criarFilaListaLigada() {
    struct FilaListaLigada novaFila;
    novaFila.frente = NULL;
    novaFila.tras = NULL;
    return novaFila;
}

/** Função para criar um novo nó */
struct No* novoNo(char dado[]) {
    struct No *temp = (struct No*)malloc(sizeof(struct No));
    strcpy(temp->dado, dado);
    temp->proximo = NULL;
    return temp;
}


/** Função para verificar se a fila está vazia */
int filaVaziaListaLigada(struct FilaListaLigada fila) {
    return fila.frente == NULL;
}

/** Função para inserir um elemento na fila */
void inserirElementoListaLigada(struct FilaListaLigada *fila, char dado[]) {
    struct No *temp = novoNo(dado);
    if (fila->tras == NULL) {
        fila->frente = fila->tras = temp;
        printf("Cliente '%s' inserido na fila.\n", dado);
        return;
    }
    fila->tras->proximo = temp;
    fila->tras = temp;
    printf("Cliente '%s' inserido na fila.\n", dado);
}

/** Função para remover um elemento da fila */
void removerElementoListaLigada(struct FilaListaLigada *fila) {
    if (filaVaziaListaLigada(*fila)) {
        printf("A fila está vazia. Nenhum cliente para remover.\n");
        return;
    }
    struct No *temp = fila->frente;
    fila->frente = fila->frente->proximo;
    if (fila->frente == NULL) {
        fila->tras = NULL;
    }
    printf("Cliente '%s' removido da fila.\n", temp->dado);
    free(temp);
}

/** Função para exibir os elementos da fila */
void exibirElementosListaLigada(struct FilaListaLigada fila) {
    if (filaVaziaListaLigada(fila)) {
        printf("A fila está vazia. Nenhum cliente para exibir.\n");
        return;
    }
    struct No *temp = fila.frente;
    printf("\nClientes na fila:\n");
    while (temp != NULL) {
        printf("%s\n", temp->dado);
        temp = temp->proximo;
    }
}

/** Função para localizar um elemento na fila para consulta */
void localizarElementoConsultaListaLigada(struct FilaListaLigada fila, char elemento[]) {
    if (!filaVaziaListaLigada(fila)) {
        struct No *atual = fila.frente;
        int posicao = 1;
        while (atual != NULL) {
            if (strcmp(atual->dado, elemento) == 0) {
                printf("O cliente '%s' foi encontrado na fila na posicao %d.\n", elemento, posicao);
                return;
            }
            atual = atual->proximo;
            posicao++;
        }
        printf("O cliente '%s' não foi encontrado na fila.\n", elemento);
    } else {
        printf("A fila está vazia. Nenhum cliente para consultar.\n");
    }
}

/** Função para localizar um elemento na fila para alteração da informação */
void localizarElementoAlteracaoListaLigada(struct FilaListaLigada *fila, char elemento[]) {
    if (!filaVaziaListaLigada(*fila)) {
        struct No *atual = fila->frente;
        while (atual != NULL) {
            if (strcmp(atual->dado, elemento) == 0) {
                printf("Digite o novo valor para o cliente '%s': ", elemento);
                scanf(" %[^\n]", atual->dado); /* Lê o novo valor para o elemento */
                printf("O cliente '%s' foi alterado para '%s'.\n", elemento, atual->dado);
                return;
            }
            atual = atual->proximo;
        }
        printf("O cliente '%s' não foi encontrado na fila. Nenhuma alteracao feita.\n", elemento);
    } else {
        printf("A fila esta vazia. Nenhum cliente para alterar.\n");
    }
}

/** Função para buscar por elementos que coincidam com um certo padrão na fila */
void buscarPorPadraoListaLigada(struct FilaListaLigada fila, char padrao[]) {
    if (!filaVaziaListaLigada(fila)) {
        printf("\nClientes na fila que coincidem com o padrao '%s':\n", padrao);
        struct No *atual = fila.frente;
        while (atual != NULL) {
            if (strstr(atual->dado, padrao) != NULL) {
                printf("%s\n", atual->dado);
            }
            atual = atual->proximo;
        }
    } else {
        printf("A fila esta vazia. Nenhum cliente para buscar por padrão.\n");
    }
}

/** Função para intercalar duas filas */
void intercalarFilasListaLigada(struct FilaListaLigada *fila1, struct FilaListaLigada *fila2, struct FilaListaLigada *resultado) {
    struct No *atual1 = fila1->frente;
    struct No *atual2 = fila2->frente;

    /*  Cria uma fila de resultado vazia */
    *resultado = criarFilaListaLigada();

    /* Intercala os elementos das duas filas */
    while (atual1 != NULL || atual2 != NULL) {
        if (atual1 != NULL) {
            inserirElementoListaLigada(resultado, atual1->dado);
            atual1 = atual1->proximo;
        }
        if (atual2 != NULL) {
            inserirElementoListaLigada(resultado, atual2->dado);
            atual2 = atual2->proximo;
        }
    }
}

/** Função para concatenar duas filas */
void concatenarFilasListaLigada(struct FilaListaLigada *fila1, struct FilaListaLigada *fila2) {
    if (fila1->tras != NULL) {
        fila1->tras->proximo = fila2->frente;
    } else {
        fila1->frente = fila2->frente;
    }

    if (fila2->tras != NULL) {
        fila1->tras = fila2->tras;
    }

    /* Limpa a segunda fila */
    fila2->frente = fila2->tras = NULL;
}

/** Função para dividir uma fila em duas */
void dividirFilaListaLigada(struct FilaListaLigada *fila, struct FilaListaLigada *metade1, struct FilaListaLigada *metade2) {
    struct No *atual = fila->frente;
    struct No *temp;
    int meio = 0;
    int i;

    /* Cria duas filas vazias para as metades */
    *metade1 = criarFilaListaLigada();
    *metade2 = criarFilaListaLigada();

    while (atual != NULL) {
        meio++;
        atual = atual->proximo;
    }

    meio /= 2; /* Encontra o ponto médio */
    atual = fila->frente;

    /* Divide a fila original em duas metades */
    for (i = 0; i < meio; i++) {
        temp = atual->proximo;
        atual->proximo = NULL;
        if (metade1->tras != NULL) {
            metade1->tras->proximo = atual;
        } else {
            metade1->frente = atual;
        }
        metade1->tras = atual;
        atual = temp;
    }

    metade2->frente = atual;
    if (atual != NULL) {
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        metade2->tras = atual;
    }

    /* Limpa a fila original */
    fila->frente = fila->tras = NULL;
}

/** Função para fazer uma cópia da fila lista ligada */
void copiarFilaListaLigada(struct FilaListaLigada fila, struct FilaListaLigada *copia) {
    /* Cria uma fila de cópia vazia */
    *copia = criarFilaListaLigada();

    struct No *atual = fila.frente;
    while (atual != NULL) {
        inserirElementoListaLigada(copia, atual->dado);
        atual = atual->proximo;
    }
    printf("Cópia da fila de clientes:\n");
    exibirElementosListaLigada(*copia);
}

/* Função do menu principal */
void menu() {
    struct FilaListaLigada fila1 = criarFilaListaLigada();
    struct FilaListaLigada fila2 = criarFilaListaLigada();
    struct FilaListaLigada resultado; /* Adicionado para armazenar o resultado da intercalação */
    int opcao;

    while (1) {
        printf("\nDigite 1 para inserir cliente na fila 1\n");
        printf("Digite 2 para remover cliente da fila 1\n");
        printf("Digite 3 para exibir clientes da fila 1\n");
        printf("Digite 4 para localizar um cliente na fila 1 para consulta\n");
        printf("Digite 5 para localizar um cliente na fila 1 para alteracao\n");
        printf("Digite 6 para buscar por padrao na fila 1\n");
        printf("Digite 7 para criar uma nova fila de clientes\n");
        printf("Digite 8 para verificar se a fila esta vazia\n");
        printf("Digite 9 para intercalar fila 1 e fila 2\n");
        printf("Digite 10 para concatenar fila 1 e fila 2\n");
        printf("Digite 11 para dividir a fila 1 em duas\n");
        printf("Digite 12 para fazer uma copia da fila 1\n");
        printf("Digite 13 para sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                char elemento[100];
                printf("Digite o cliente a ser inserido na fila 1: ");
                scanf(" %[^\n]", elemento);
                inserirElementoListaLigada(&fila1, elemento);
                break;
            }
            case 2:
                removerElementoListaLigada(&fila1);
                break;
            case 3:
                exibirElementosListaLigada(fila1);
                break;
            case 4: {
                char elemento[100];
                printf("Digite o cliente que deseja localizar na fila 1: ");
                scanf(" %[^\n]", elemento);
                localizarElementoConsultaListaLigada(fila1, elemento);
                break;
            }
            case 5: {
                char elemento[100];
                printf("Digite o cliente que deseja alterar na fila 1: ");
                scanf(" %[^\n]", elemento);
                localizarElementoAlteracaoListaLigada(&fila1, elemento);
                break;
            }
            case 6: {
                char padrao[100];
                printf("Digite o padrao a ser buscado na fila 1: ");
                scanf(" %[^\n]", padrao);
                buscarPorPadraoListaLigada(fila1, padrao);
                break;
            }
            case 7:
                fila1 = criarFilaListaLigada();
                printf("Uma nova fila de clientes foi criada.\n");
                break;
            case 8:
                if (filaVaziaListaLigada(fila1)) {
                    printf("A fila de clientes 1 esta vazia.\n");
                } else {
                    printf("A fila de clientes 1 nao esta vazia.\n");
                }
                break;

            case 9:
                resultado = criarFilaListaLigada();
                intercalarFilasListaLigada(&fila1, &fila2, &resultado);
                break;
            case 10:
                concatenarFilasListaLigada(&fila1, &fila2);
                break;
            case 11: {
                struct FilaListaLigada metade1 = criarFilaListaLigada();
                struct FilaListaLigada metade2 = criarFilaListaLigada();
                dividirFilaListaLigada(&fila1, &metade1, &metade2);
                break;
            }
            case 12: {
                struct FilaListaLigada copia = criarFilaListaLigada();
                copiarFilaListaLigada(fila1, &copia);
                break;
            }
            case 13:
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
