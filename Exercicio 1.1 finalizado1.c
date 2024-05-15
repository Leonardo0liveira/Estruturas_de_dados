#include <stdio.h>
#include <stdbool.h> // Para usar o tipo bool

struct no {
    char letra;
    int filhos[3];
};

// Função para realizar a busca em profundidade
void buscaProfundidade(struct no exemplo[], int noAtual, int profundidade) {
    // Exiba o nó atual com sua profundidade
    printf("Visitando no (Profundidade %d): %c\n", profundidade, exemplo[noAtual].letra);

    // Empilhe os filhos do nó atual (se existirem)
    for (int i = 0; i < 3; i++) {
        int filho = exemplo[noAtual].filhos[i];
        if (filho != -1) {
            buscaProfundidade(exemplo, filho, profundidade + 1);
        }
    }
}

int main() {
    struct no exemplo1[8];
    int i, j;

    for (i = 0; i < 8; i++) {
        exemplo1[i].letra = '\0';
        for (j = 0; j < 3; j++) {
            exemplo1[i].filhos[j] = -1;
        }
    }

    // Inserindo o nó raiz na árvore
    exemplo1[0].letra = 'A';

    // Inserindo os filhos de A
    exemplo1[0].filhos[0] = 1; // B
    exemplo1[0].filhos[1] = 2; // C
    exemplo1[0].filhos[2] = 3; // D

    // Inserindo os filhos de B
    exemplo1[1].letra = 'B';
    exemplo1[1].filhos[0] = 4; // E
    exemplo1[1].filhos[1] = 5; // F

    // Inserindo os filhos de C
    exemplo1[2].letra = 'C'; // Sem filhos

    // Inserindo o filho de D
    exemplo1[3].letra = 'D';
    exemplo1[3].filhos[0] = 6; // G

    // Inserindo os filhos de E
    exemplo1[4].letra = 'E'; // Sem filhos

    // Inserindo os filhos de F
    exemplo1[5].letra = 'F'; // Sem filhos

    // Inserindo o filho de G
    exemplo1[6].letra = 'G';
    exemplo1[6].filhos[0] = 7; // H

    // Inserindo os filhos de H
    exemplo1[7].letra = 'H'; // Sem filhos

    // Exibindo a árvore original
    printf("Arvore original:\n");
    for (i = 0; i < 8; i++) {
        printf("Pai: %c\n", exemplo1[i].letra);
        for (j = 0; j < 3; j++) {
            printf("Filho %d: %d - ", j, exemplo1[i].filhos[j]);
        }
        printf("\n");
    }
    printf("\n Representacoes: 1=B; 2=C; 3=D; 4=E; 5=F; 6=G; 7=H");
    // Realize a busca em profundidade a partir do nó raiz (nó 0)
    printf("\nBusca em profundidade:\n");
    buscaProfundidade(exemplo1, 0,0);

    return 0;
}


