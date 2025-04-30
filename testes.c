
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "estruturas_busca.h"

void gerar_vetor(int* vetor, int n) {
    for (int i = 0; i < n; i++) vetor[i] = i * 2;
}

void estatisticas(double tempos[], int n, double* media, double* desvio) {
    double soma = 0, soma_quadrados = 0;
    for (int i = 0; i < n; i++) {
        soma += tempos[i];
        soma_quadrados += tempos[i] * tempos[i];
    }
    *media = soma / n;
    *desvio = sqrt((soma_quadrados / n) - (*media * *media));
}

void escrever_csv(const char* filename, int tamanhos[], double medias[], double desvios[], double comparacoes[], int n) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Erro ao criar arquivo CSV: %s\n", filename);
        return;
    }
    fprintf(f, "#tamanho,media,desvio,comparacoes\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d,%.2f,%.2f,%.2f\n", tamanhos[i], medias[i], desvios[i], comparacoes[i]);
    }
    fclose(f);
}

void testar_array(int num_buscas) {
    int tamanhos[] = {100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000};
    double medias[10], desvios[10], comps[10];

    printf("\nTestando Arranjos Estáticos (Arrays)\n");

    for (int i = 0; i < 10; i++) {
        int n = tamanhos[i];
        int* vetor = malloc(sizeof(int) * n);
        gerar_vetor(vetor, n);

        double tempos[1000];
        int comparacoes_total = 0;

        for (int j = 0; j < (num_buscas < 100 ? 1000 : num_buscas); j++) {
            int chave = rand() % (2 * n);
            int comparacoes = 0;
            clock_t ini_busca = clock();
            busca_binaria(vetor, n, chave, &comparacoes);
            clock_t fim_busca = clock();

            tempos[j] = ((double)(fim_busca - ini_busca)) * 1e6 / CLOCKS_PER_SEC;
            comparacoes_total += comparacoes;
        }

        estatisticas(tempos, num_buscas, &medias[i], &desvios[i]);
        comps[i] = (double)comparacoes_total / num_buscas;

        printf("Tamanho %d: Média %.2f µs | Desvio %.2f | Comparações %.2f\n", n, medias[i], desvios[i], comps[i]);
        free(vetor);
    }

    escrever_csv("array.csv", tamanhos, medias, desvios, comps, 10);
}

void testar_lista_nao_ordenada(int num_buscas) {
    double medias[10], desvios[10], comps[10];
    int tamanhos[10];

    printf("\nTestando Lista Ligada NÃO Ordenada\n");

    for (int i = 0; i < 10; i++) {
        int n = 100000 * (i + 1);
        tamanhos[i] = n;
        int* vetor = malloc(sizeof(int) * n);
        gerar_vetor(vetor, n);

        No* lista = criar_lista(vetor, n, 0);

        double tempos[1000];
        int comparacoes_total = 0;

        for (int j = 0; j < (num_buscas < 100 ? 1000 : num_buscas); j++) {
            int chave = rand() % (2 * n);
            int comparacoes = 0;
            clock_t ini_busca = clock();
            busca_lista(lista, chave, &comparacoes);
            clock_t fim_busca = clock();

            tempos[j] = ((double)(fim_busca - ini_busca)) * 1e6 / CLOCKS_PER_SEC;
            comparacoes_total += comparacoes;
        }

        estatisticas(tempos, num_buscas, &medias[i], &desvios[i]);
        comps[i] = (double)comparacoes_total / num_buscas;

        printf("Tamanho %d: Média %.2f µs | Desvio %.2f | Comparações %.2f\n", n, medias[i], desvios[i], comps[i]);

        liberar_lista(lista);
        free(vetor);
    }

    escrever_csv("lista_nao_ordenada.csv", tamanhos, medias, desvios, comps, 10);
}

void testar_lista_ordenada(int num_buscas) {
    double medias[10], desvios[10], comps[10];
    int tamanhos[10];

    printf("\nTestando Lista Ligada Ordenada\n");

    for (int i = 0; i < 10; i++) {
        int n = 100000 * (i + 1);
        tamanhos[i] = n;
        int* vetor = malloc(sizeof(int) * n);
        gerar_vetor(vetor, n);

        No* lista = criar_lista(vetor, n, 1);

        double tempos[1000];
        int comparacoes_total = 0;

        for (int j = 0; j < (num_buscas < 100 ? 1000 : num_buscas); j++) {
            int chave = rand() % (2 * n);
            int comparacoes = 0;
            clock_t ini_busca = clock();
            busca_lista_ordenada(lista, chave, &comparacoes);
            clock_t fim_busca = clock();

            tempos[j] = ((double)(fim_busca - ini_busca)) * 1e6 / CLOCKS_PER_SEC;
            comparacoes_total += comparacoes;
        }

        estatisticas(tempos, num_buscas, &medias[i], &desvios[i]);
        comps[i] = (double)comparacoes_total / num_buscas;

        printf("Tamanho %d: Média %.2f µs | Desvio %.2f | Comparações %.2f\n", n, medias[i], desvios[i], comps[i]);

        liberar_lista(lista);
        free(vetor);
    }

    escrever_csv("lista_ordenada.csv", tamanhos, medias, desvios, comps, 10);
}
