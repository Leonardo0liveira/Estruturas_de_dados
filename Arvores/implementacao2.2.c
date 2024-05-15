#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    char letra;
    int indice;
    struct No *filho;
    struct No *irmao;
} No;

No* criarNo(char letra, int indice) {
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo != NULL) {
        novoNo->letra = letra;
        novoNo->indice = indice;
        novoNo->filho = NULL;
        novoNo->irmao = NULL;
    }
    return novoNo;
}

void inserirFilho(No *pai, char letra, int indice) {
    if (pai == NULL)
        return;

    No *novoFilho = criarNo(letra, indice);
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

No* buscarLetra(No *raiz, char letra) {
    if (raiz == NULL)
        return NULL;
    
    if (raiz->letra == letra)
        return raiz;
    
    No *temp = raiz->filho;
    while (temp != NULL) {
        No *resultado = buscarLetra(temp, letra);
        if (resultado != NULL)
            return resultado;
        temp = temp->irmao;
    }
    return NULL;
}

void imprimirArvore(No *raiz, int nivel) {
    if (raiz == NULL)
        return;
    
    for (int i = 0; i < nivel; i++)
        printf("  ");
    printf("%c (%d)\n", raiz->letra, raiz->indice);
    
    imprimirArvore(raiz->filho, nivel + 1);
    imprimirArvore(raiz->irmao, nivel);
}

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
    // Construindo a árvore inicial
    No *raiz = criarNo('A', 0);
    inserirFilho(raiz, 'B', 1);
    inserirFilho(raiz, 'C', 2);
    inserirFilho(raiz->filho, 'D', 3);
    inserirFilho(raiz->filho, 'E', 4);
    inserirFilho(raiz->filho->irmao, 'F', 5);
    inserirFilho(raiz->filho->irmao, 'G', 6);
    
    // 1. Buscar o nó "E" e inserir o nó "I" como filho
    No *noE = buscarLetra(raiz, 'E');
    if (noE != NULL) {
        inserirFilho(noE, 'I', 7);
    } else {
        printf("Erro: nó 'E' não encontrado.\n");
    }
    
    // 2. Buscar o nó "G" e inserir o nó "J" como filho
    No *noG = buscarLetra(raiz, 'G');
    if (noG != NULL) {
        inserirFilho(noG, 'J', 8);
    } else {
        printf("Erro: nó 'G' não encontrado.\n");
    }
    
    // 3. Exibir a árvore atualizada
    printf("Árvore atualizada:\n");
    imprimirArvore(raiz, 0);
    
    // Liberar memória
    liberarArvore(raiz);
    
    return 0;
}
