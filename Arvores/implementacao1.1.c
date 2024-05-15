#include <stdio.h>
#include <stdlib.h>

struct no {
    char letra;
    int filhos[3]; /* Array para os índices dos filhos*/
};

/* Vetor para representar a árvore*/
struct no exemplo1[8];

int main() {
    int i, j;

    for (i = 0; i < 8; i++) {
        exemplo1[i].letra = '\0'; /* Inicializa os nós como vazios*/
        for (j = 0; j < 3; j++) {
            exemplo1[i].filhos[j] = -1; /* Inicializa os índices dos filhos como vazios*/
        }
    }

    /* Exibindo a árvore*/
    for (i = 0; i < 8; i++) {
        printf("\n");
    }

    printf("\n pai:%c \n", exemplo1[i].letra);
    for (j = 0; j < 3; j++) {
        printf("filho %d: %d - ", j, exemplo1[j].filhos[j]);
    }

    printf("\n\n --------- ---------------\n\n");

    /* inserindo o nó raiz na árvore*/
    exemplo1[0].letra = 'A';

    /* Exibindo a árvore novamente apenas para conferir se o nó foi inserido*/
    for (i = 0; i < 8; i++) {
        printf("\n pai:%c \n", exemplo1[i].letra);
        for (j = 0; j < 3; j++) {
            printf("filho %d: %d - ", j, exemplo1[j].filhos[j]);
        }
    }

    printf("\n\n --------- ---------------\n\n");

    /* inserindo o primeiro nó filho da raiz na árvore*/

    printf("\n pai:%c \n", exemplo1[i].letra);
    for (j = 0; j < 3; j++) {
        printf("filho %d: %d - ", j, exemplo1[j].filhos[j]);
    }

    return 0;
}
