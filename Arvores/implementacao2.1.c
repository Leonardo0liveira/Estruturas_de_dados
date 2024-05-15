#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó da árvore
typedef struct No {
    int valor;
    struct No *filho; // Ponteiro para o primeiro filho
    struct No *irmao; // Ponteiro para o próximo irmão
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo != NULL) {
        novoNo->valor = valor;
        novoNo->filho = NULL;
        novoNo->irmao = NULL;
    }
    return novoNo;
}

// Função para inserir um novo nó como filho de um nó pai
void inserirFilho(No *pai, int valor) {
    if (pai == NULL)
        return;

    No *novoFilho = criarNo(valor);
    if (novoFilho == NULL)
        return;

    if (pai->filho == NULL)
        pai->filho = novoFilho;
    else {
        No *temp = pai->filho;
        while (temp->irmao != NULL)
            temp = temp->irmao;
        temp->irmao = novoFilho;
    }
}

// Função para buscar um valor na árvore
No* buscarValor(No *raiz, int valor) {
    if (raiz == NULL)
        return NULL;
    
    if (raiz->valor == valor)
        return raiz;
    
    No *temp = raiz->filho;
    while (temp != NULL) {
        No *resultado = buscarValor(temp, valor);
        if (resultado != NULL)
            return resultado;
        temp = temp->irmao;
    }
    return NULL;
}

// Função para remover um nó da árvore
void removerNo(No **raiz, int valor) {
    if (*raiz == NULL)
        return;
    
    if ((*raiz)->valor == valor) {
        No *temp = *raiz;
        *raiz = (*raiz)->irmao;
        free(temp);
        return;
    }
    
    No *pai = *raiz;
    No *atual = (*raiz)->filho;
    while (atual != NULL) {
        if (atual->valor == valor) {
            pai->filho = atual->irmao;
            free(atual);
            return;
        }
        pai = atual;
        atual = atual->irmao;
    }
    
    atual = (*raiz)->filho;
    while (atual != NULL) {
        removerNo(&atual, valor);
        atual = atual->irmao;
    }
}

// Função para imprimir a árvore em pré-ordem
void imprimirArvore(No *raiz, int nivel) {
    if (raiz == NULL)
        return;
    
    for (int i = 0; i < nivel; i++)
        printf("  ");
    printf("%d\n", raiz->valor);
    
    imprimirArvore(raiz->filho, nivel + 1);
    imprimirArvore(raiz->irmao, nivel);
}

// Função para liberar a memória alocada pela árvore
void liberarArvore(No *raiz) {
    if (raiz == NULL)
        return;
    
    No *atual = raiz->filho;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->irmao;
        liberarArvore(temp);
    }
    free(raiz);
}

int main() {
    No *raiz = criarNo(1);
    inserirFilho(raiz, 2);
    inserirFilho(raiz, 3);
    inserirFilho(raiz->filho, 4);
    inserirFilho(raiz->filho, 5);
    inserirFilho(raiz->filho->irmao, 6);

    printf("Árvore:\n");
    imprimirArvore(raiz, 0);

    printf("\nBusca:\n");
    int valorBuscado = 2;
    No *resultadoBusca = buscarValor(raiz, valorBuscado);
    if (resultadoBusca != NULL)
        printf("Valor %d encontrado!\n", valorBuscado);
    else
        printf("Valor %d não encontrado!\n", valorBuscado);

    printf("\nRemoção:\n");
    int valorRemover = 5;
    removerNo(&raiz, valorRemover);
    printf("Valor %d removido!\n", valorRemover);

    printf("\nÁrvore após remoção:\n");
    imprimirArvore(raiz, 0);

    liberarArvore(raiz);

    return 0;
}
