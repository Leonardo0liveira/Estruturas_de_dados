#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no {
    char letra;
    int filhos[3];
};

struct no exemplo1[8]; 

void inicializaArvore() {

    exemplo1[0] = (struct no){'A', {1, 2, 3}};
    exemplo1[1] = (struct no){'B', {4, 5, -1}};
    exemplo1[2] = (struct no){'C', {-1, -1, -1}};
    exemplo1[3] = (struct no){'D', {6, -1, -1}};
    exemplo1[4] = (struct no){'E', {-1, -1, -1}};
    exemplo1[5] = (struct no){'F', {-1, -1, -1}};
    exemplo1[6] = (struct no){'G', {7, -1, -1}};
    exemplo1[7] = (struct no){'H', {-1, -1, -1}};
}

void removeNo(int index) {
    if (index < 0 || index >= 8) return;

    int stack[8], top = -1;
    stack[++top] = index; 

    while (top != -1) {
        int current = stack[top--]; 
        struct no *node = &exemplo1[current];

        node->letra = '\0'; 

        for (int i = 0; i < 3; ++i) {
            if (node->filhos[i] != -1) {
                stack[++top] = node->filhos[i];
            }
        }
    }
}

void printArvore() {
    for (int i = 0; i < 8; i++) {
        if (exemplo1[i].letra != '\0') {
            printf("Nó %c com filhos: ", exemplo1[i].letra);
            for (int j = 0; j < 3; j++) {
                if (exemplo1[i].filhos[j] != -1) {
                    printf("%c ", exemplo1[exemplo1[i].filhos[j]].letra);
                }
            }
            printf("\n");
        }
    }
}

int main() {
    inicializaArvore();
    printArvore();
    removeNo(1);
    printf("Após remover o nó D e seus descendentes:\n");
    printArvore();

    return 0;
}
