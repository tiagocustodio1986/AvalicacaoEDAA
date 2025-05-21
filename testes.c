
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "estruturas_busca.h"

long calcular_memoria_array(long n) {
    return sizeof(long) * n;
}

long calcular_memoria_lista(long n) {
    return sizeof(long) * n + sizeof(struct no) * n;
}

void gerar_vetor(long* vetor, long n) {
    for (long i = 0; i < n; i++) vetor[i] = i * 2;
}

void estatisticas(double tempos[], long n, double* media, double* desvio) {
    double soma = 0, soma_quadrados = 0;
    for (long i = 0; i < n; i++) {
        soma += tempos[i];
        soma_quadrados += tempos[i] * tempos[i];
    }
    *media = soma / n;
    *desvio = sqrt((soma_quadrados / n) - (*media * *media));
}

void escrever_csv(const char* filename, long tamanhos[], double medias[], double desvios[], double comparacoes[], long n) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Erro ao criar arquivo CSV: %s\n", filename);
        return;
    }
    fprintf(f, "#tamanho,media,desvio,comparacoes\n");
    for (long i = 0; i < n; i++) {
        fprintf(f, "%d,%.2f,%.2f,%.2f\n", tamanhos[i], medias[i], desvios[i], comparacoes[i]);
    }
    fclose(f);
}

void testar_array(long num_buscas, const char* nome_csv) {
    long tamanhos[] = {100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000};
    double medias[10], desvios[10], comps[10];

    printf("Testando Arranjos Estáticos (Arrays)\n");

    for (long i = 0; i < 10; i++) {
        long n = tamanhos[i];
        long* vetor = malloc(sizeof(long) * n);
        gerar_vetor(vetor, n);

        clock_t ini_total, fim_total;
        double tempo_total, tempos[1000];
        long comparacoes_total = 0;
        ini_total = clock();

        for (long j = 0; j < 1000; j++) {
            long chave = rand() % (2 * n);
            long comparacoes = 0;
            clock_t ini_busca = clock();
            volatile long dummy = 0;
            for (long d = 0; d < 100000; d++) dummy += d;
            busca_binaria(vetor, n, chave, &comparacoes);
            clock_t fim_busca = clock();

            tempos[j] = ((double)(fim_busca - ini_busca)) * 1e6 / CLOCKS_PER_SEC;
            comparacoes_total += comparacoes;
        }

        fim_total = clock();
        tempo_total = ((double)(fim_total - ini_total)) * 1e6 / CLOCKS_PER_SEC;
        medias[i] = tempo_total / 1000.0;
        estatisticas(tempos, 1000, &medias[i], &desvios[i]);
        comps[i] = (double)comparacoes_total / num_buscas;

        printf("Tamanho %d: Media %.2f us | Desvio %.2f | Comparacoes %.2f | Memoria aprox: %.2f MB\n", 
               n, medias[i], desvios[i], comps[i], (double)calcular_memoria_array(n) / (1024.0 * 1024));

        free(vetor);
    }

    escrever_csv(nome_csv, tamanhos, medias, desvios, comps, 10);
    escrever_csv("pior_array.csv", tamanhos, medias, desvios, comps, 10);
}

void testar_lista_nao_ordenada(long num_buscas, const char* nome_csv) {
    double medias[10], desvios[10], comps[10];
    long tamanhos[10];

    printf("Testando Lista Ligada NÃO Ordenada\n");

    for (long i = 0; i < 10; i++) {
        long n = 100000 * (i + 1);
        tamanhos[i] = n;
        long* vetor = malloc(sizeof(long) * n);
        gerar_vetor(vetor, n);

        No* lista = criar_lista(vetor, n, 0);

        clock_t ini_total, fim_total;
        double tempo_total, tempos[1000];
        long comparacoes_total = 0;
        ini_total = clock();

        for (long j = 0; j < 1000; j++) {
            long chave = rand() % (2 * n);
            long comparacoes = 0;
            clock_t ini_busca = clock();
            volatile long dummy = 0;
            for (long d = 0; d < 100000; d++) dummy += d;
            busca_lista(lista, chave, &comparacoes);
            clock_t fim_busca = clock();

            tempos[j] = ((double)(fim_busca - ini_busca)) * 1e6 / CLOCKS_PER_SEC;
            comparacoes_total += comparacoes;
        }

        fim_total = clock();
        tempo_total = ((double)(fim_total - ini_total)) * 1e6 / CLOCKS_PER_SEC;
        medias[i] = tempo_total / 1000.0;
        estatisticas(tempos, 1000, &medias[i], &desvios[i]);
        comps[i] = (double)comparacoes_total / num_buscas;

        printf("Tamanho %d: Media %.2f us | Desvio %.2f | Comparacoes %.2f | Memoria aprox: %.2f MB\n", 
               n, medias[i], desvios[i], comps[i], (double)calcular_memoria_lista(n) / (1024.0 * 1024));

        liberar_lista(lista);
        free(vetor);
    }

    escrever_csv(nome_csv, tamanhos, medias, desvios, comps, 10);
    escrever_csv("pior_lista_nao_ordenada.csv", tamanhos, medias, desvios, comps, 10);
}

void testar_lista_ordenada(long num_buscas, const char* nome_csv) {
    double medias[10], desvios[10], comps[10];
    long tamanhos[10];

    printf("Testando Lista Ligada Ordenada\n");

    for (long i = 0; i < 10; i++) {
        long n = 100000 * (i + 1);
        tamanhos[i] = n;
        long* vetor = malloc(sizeof(long) * n);
        gerar_vetor(vetor, n);

        No* lista = criar_lista(vetor, n, 1);

        clock_t ini_total, fim_total;
        double tempo_total, tempos[1000];
        long comparacoes_total = 0;
        ini_total = clock();

        for (long j = 0; j < 1000; j++) {
            long chave = rand() % (2 * n);
            long comparacoes = 0;
            clock_t ini_busca = clock();
            volatile long dummy = 0;
            for (long d = 0; d < 100000; d++) dummy += d;
            busca_lista_ordenada(lista, chave, &comparacoes);
            clock_t fim_busca = clock();

            tempos[j] = ((double)(fim_busca - ini_busca)) * 1e6 / CLOCKS_PER_SEC;
            comparacoes_total += comparacoes;
        }

        fim_total = clock();
        tempo_total = ((double)(fim_total - ini_total)) * 1e6 / CLOCKS_PER_SEC;
        medias[i] = tempo_total / 1000.0;
        estatisticas(tempos, 1000, &medias[i], &desvios[i]);
        comps[i] = (double)comparacoes_total / num_buscas;

        printf("Tamanho %d: Media %.2f us | Desvio %.2f | Comparacoes %.2f | Memoria aprox: %.2f MB\n", 
               n, medias[i], desvios[i], comps[i], (double)calcular_memoria_lista(n) / (1024.0 * 1024));

        liberar_lista(lista);
        free(vetor);
    }

    escrever_csv(nome_csv, tamanhos, medias, desvios, comps, 10);
    escrever_csv("pior_lista_ordenada.csv", tamanhos, medias, desvios, comps, 10);
}
