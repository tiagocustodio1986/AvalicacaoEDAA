#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no* prox;
} No;

// Busca sequencial simples
int busca_sequencial(int arr[], int n, int chave, int* comparacoes) {
    for (int i = 0; i < n; i++) {
        (*comparacoes)++;
        if (arr[i] == chave) return i;
    }
    return -1;
}

// Busca sequencial otimizada (ordem crescente)
int busca_sequencial_otimizada(int arr[], int n, int chave, int* comparacoes) {
    for (int i = 0; i < n; i++) {
        (*comparacoes)++;
        if (arr[i] == chave) return i;
        if (arr[i] > chave) return -1;
    }
    return -1;
}

// Busca binária
int busca_binaria(int arr[], int n, int chave, int* comparacoes) {
    int esquerda = 0, direita = n - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        (*comparacoes)++;
        if (arr[meio] == chave) return meio;
        if (arr[meio] < chave) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1;
}

// Criação de lista ligada
No* criar_lista(int* vetor, int n, int ordenada) {
    No* head = NULL;
    for (int i = 0; i < n; i++) {
        No* novo = malloc(sizeof(No));
        novo->valor = vetor[i];
        novo->prox = NULL;

        if (!head || !ordenada) {
            novo->prox = head;
            head = novo;
        } else {
            No** ptr = &head;
            while (*ptr && (*ptr)->valor < novo->valor) {
                ptr = &(*ptr)->prox;
            }
            novo->prox = *ptr;
            *ptr = novo;
        }
    }
    return head;
}

int busca_lista(No* head, int chave, int* comparacoes) {
    while (head) {
        (*comparacoes)++;
        if (head->valor == chave) return 1;
        head = head->prox;
    }
    return 0;
}

int busca_lista_ordenada(No* head, int chave, int* comparacoes) {
    while (head && head->valor <= chave) {
        (*comparacoes)++;
        if (head->valor == chave) return 1;
        head = head->prox;
    }
    return 0;
}

void liberar_lista(No* head) {
    while (head) {
        No* temp = head;
        head = head->prox;
        free(temp);
    }
}