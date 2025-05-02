#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    long valor;
    struct no* prox;
} No;

// Busca sequencial simples
long busca_sequencial(long arr[], long n, long chave, long* comparacoes) {
    for (long i = 0; i < n; i++) {
        (*comparacoes)++;
        volatile long dummy = 0; dummy++;
        if (arr[i] == chave) return i;
    }
    return -1;
}

// Busca sequencial otimizada (ordem crescente)
long busca_sequencial_otimizada(long arr[], long n, long chave, long* comparacoes) {
    for (long i = 0; i < n; i++) {
        (*comparacoes)++;
        volatile long dummy = 0; dummy++;
        if (arr[i] == chave) return i;
        if (arr[i] > chave) return -1;
    }
    return -1;
}

// Busca binária
long busca_binaria(long arr[], long n, long chave, long* comparacoes) {
    long esquerda = 0, direita = n - 1;
    while (esquerda <= direita) {
        long meio = (esquerda + direita) / 2;
        (*comparacoes)++;
        volatile long dummy = 0; dummy++;
        if (arr[meio] == chave) return meio;
        if (arr[meio] < chave) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1;
}

// Criação de lista ligada
No* criar_lista(long* vetor, long n, long ordenada) {
    No* head = NULL;
    for (long i = 0; i < n; i++) {
        No* novo = malloc(sizeof(No));
        novo->valor = vetor[i];
        novo->prox = NULL;
        volatile long dummy = 0; dummy++;

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

long busca_lista(No* head, long chave, long* comparacoes) {
    while (head) {
        (*comparacoes)++;
        volatile long dummy = 0; dummy++;
        if (head->valor == chave) return 1;
        head = head->prox;
    }
    return 0;
}

long busca_lista_ordenada(No* head, long chave, long* comparacoes) {
    while (head && head->valor <= chave) {
        (*comparacoes)++;
        volatile long dummy = 0; dummy++;
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