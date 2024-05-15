#include <stdio.h>
#include <stdlib.h>

#define MAX_NO 100

// Estrutura para representar um nó da árvore
typedef struct {
    char letra;
    int indice;
} No;

No arvore[MAX_NO];
int proximo_indice = 0;

void inserirFilho(char letra_pai, char nova_letra) {
    int i;
    for (i = 0; i < proximo_indice; i++) {
        if (arvore[i].letra == letra_pai) {
            arvore[proximo_indice].letra = nova_letra;
            arvore[proximo_indice].indice = proximo_indice;
            proximo_indice++;
            return;
        }
    }
    printf("Erro: Nó pai não encontrado!\n");
}

int buscaLargura(char letra) {
    int i;
    for (i = 0; i < proximo_indice; i++) {
        if (arvore[i].letra == letra) {
            printf("Letra %c encontrada no índice %d!\n", letra, i);
            return i;
        }
    }
    printf("Letra %c não encontrada!\n", letra);
    return -1;
}

void exibirArvore() {
    printf("Árvore atualizada:\n");
    for (int i = 0; i < proximo_indice; i++) {
        printf("%c (%d)\n", arvore[i].letra, arvore[i].indice);
    }
}

int main() {
    // Construindo a árvore inicial
    arvore[0].letra = 'A';
    arvore[0].indice = 0;
    proximo_indice++;

    inserirFilho('A', 'B');
    inserirFilho('A', 'C');
    inserirFilho('B', 'D');
    inserirFilho('B', 'E');
    inserirFilho('C', 'F');

    printf("Árvore inicial:\n");
    exibirArvore();
    
    // Busca em largura do nó E e inserção do nó I como filho de E
    int indice_E = buscaLargura('E');
    if (indice_E != -1) {
        inserirFilho(arvore[indice_E].letra, 'I');
    }

    // Busca em largura do nó G e inserção do nó J como filho de G
    int indice_G = buscaLargura('G');
    if (indice_G != -1) {
        inserirFilho(arvore[indice_G].letra, 'J');
    }

    printf("\nÁrvore atualizada após inserções:\n");
    exibirArvore();

    return 0;
}
