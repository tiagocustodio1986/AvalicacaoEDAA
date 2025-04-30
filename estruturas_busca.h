
#ifndef ESTRUTURAS_BUSCA_H
#define ESTRUTURAS_BUSCA_H

typedef struct no {
    int valor;
    struct no* prox;
} No;

int busca_sequencial(int arr[], int n, int chave, int* comparacoes);
int busca_sequencial_otimizada(int arr[], int n, int chave, int* comparacoes);
int busca_binaria(int arr[], int n, int chave, int* comparacoes);
No* criar_lista(int* vetor, int n, int ordenada);
int busca_lista(No* head, int chave, int* comparacoes);
int busca_lista_ordenada(No* head, int chave, int* comparacoes);
void liberar_lista(No* head);

#endif
