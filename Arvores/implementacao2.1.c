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

void removerNo(No **raiz, char letra) {
    if (*raiz == NULL)
        return;
    
    if ((*raiz)->letra == letra) {
        No *temp = *raiz;
        *raiz = (*raiz)->irmao;
        free(temp);
        return;
    }
    
    No *pai = *raiz;
    No *atual = (*raiz)->filho;
    while (atual != NULL) {
        if (atual->letra == letra) {
            pai->filho = atual->irmao;
            free(atual);
            return;
        }
        pai = atual;
        atual = atual->irmao;
    }
    
    atual = (*raiz)->filho;
    while (atual != NULL) {
        removerNo(&atual, letra);
        atual = atual->irmao;
    }
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
    No *raiz = criarNo('A', 0);
    inserirFilho(raiz, 'B', 1);
    inserirFilho(raiz, 'C', 2);
    inserirFilho(raiz->filho, 'D', 3);
    inserirFilho(raiz->filho, 'E', 4);
    inserirFilho(raiz->filho->irmao, 'F', 5);

    printf("Árvore:\n");
    imprimirArvore(raiz, 0);

    printf("\nBusca:\n");
    char letraBuscada = 'D';
    No *resultadoBusca = buscarLetra(raiz, letraBuscada);
    if (resultadoBusca != NULL)
        printf("Letra %c encontrada no índice %d!\n", letraBuscada, resultadoBusca->indice);
    else
        printf("Letra %c não encontrada!\n", letraBuscada);

    printf("\nRemoção:\n");
    char letraRemover = 'E';
    removerNo(&raiz, letraRemover);
    printf("Letra %c removida!\n", letraRemover);

    printf("\nÁrvore após remoção:\n");
    imprimirArvore(raiz, 0);

    liberarArvore(raiz);

    return 0;
}
