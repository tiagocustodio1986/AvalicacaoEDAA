
#ifndef ESTRUTURAS_BUSCA_H
#define ESTRUTURAS_BUSCA_H

typedef struct no {
    long valor;
    struct no* prox;
} No;

long busca_sequencial(long arr[], long n, long chave, long* comparacoes);
long busca_sequencial_otimizada(long arr[], long n, long chave, long* comparacoes);
long busca_binaria(long arr[], long n, long chave, long* comparacoes);
No* criar_lista(long* vetor, long n, long ordenada);
long busca_lista(No* head, long chave, long* comparacoes);
long busca_lista_ordenada(No* head, long chave, long* comparacoes);
void liberar_lista(No* head);

#endif
