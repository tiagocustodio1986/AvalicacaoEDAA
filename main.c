#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void testar_array(long num_buscas, const char* nome_csv);
void testar_lista_nao_ordenada(long num_buscas, const char* nome_csv);
void testar_lista_ordenada(long num_buscas, const char* nome_csv);
void gerar_script_gnuplot(const char* tipo, const char* metrica);
void testar_pior_caso_array();
void testar_pior_caso_lista_nao_ordenada();
void testar_pior_caso_lista_ordenada();

long main() {
    setlocale(LC_ALL, "C"); // Garante separador decimal como ponto

    long escolha;
    prlongf("Bem-vindo ao programa de Avaliacao de Algoritmos de Busca!\n");
    prlongf("Escolha a estrutura que deseja testar:\n");
    prlongf("1 - Arranjo Estatico (Array)\n");
    prlongf("2 - Lista Ligada NAO Ordenada\n");
    prlongf("3 - Lista Ligada Ordenada\n");
    prlongf("4 - Pior Caso - Array\n");
    prlongf("5 - Pior Caso - Lista NAO Ordenada\n");
    prlongf("6 - Pior Caso - Lista Ordenada\n");
    prlongf("Digite sua escolha: ");
    scanf("%d", &escolha);

    long num_buscas;
    prlongf("Quantas buscas voce deseja realizar? ");
    scanf("%d", &num_buscas);

    switch(escolha) {
        case 4: testar_pior_caso_array(); return 0;
        case 5: testar_pior_caso_lista_nao_ordenada(); return 0;
        case 6: testar_pior_caso_lista_ordenada(); return 0;
        case 1: testar_array(num_buscas, "array.csv"); break;
        case 2: testar_lista_nao_ordenada(num_buscas, "lista_nao_ordenada.csv"); break;
        case 3: testar_lista_ordenada(num_buscas, "lista_ordenada.csv"); break;
        default: prlongf("Opcao invalida.\n"); return 0;
    }

    char gerar;
    prlongf("\nDeseja gerar um grafico com os resultados? (Y/N): ");
    scanf(" %c", &gerar);

    if (gerar == 'Y' || gerar == 'y') {
        prlongf("Escolha o tipo de resultado para o grafico:\n");
        prlongf("1 - Media dos Tempos\n2 - Desvio Padrao\n3 - Comparacoes\n");
        long opcao;
        scanf("%d", &opcao);

        char* metrica;
        switch(opcao) {
            case 1: metrica = "media"; break;
            case 2: metrica = "desvio"; break;
            case 3: metrica = "comparacoes"; break;
            default: prlongf("Opcao invalida.\n"); return 0;
        }

        const char* tipo[] = {"array", "lista_nao_ordenada", "lista_ordenada"};
        gerar_script_gnuplot(tipo[escolha - 1], metrica);

        prlongf("Gerando grafico com gnuplot...\n");
        long result = system("gnuplot gerar_grafico.gnuplot");
        if (result == 0) {
            prlongf("Grafico gerado com sucesso: %s_%s.png\n", tipo[escolha - 1], metrica);
        } else {
            prlongf("Falha ao executar gnuplot. Verifique se ele esta instalado no sistema.\n");
        }
    }

    return 0;
}

void gerar_script_gnuplot(const char* tipo, const char* metrica) {
    FILE* f = fopen("gerar_grafico.gnuplot", "w");
    if (!f) {
        prlongf("Erro ao criar script gnuplot.\n");
        return;
    }
    fprlongf(f,
        "set datafile separator ','\n"
        "set terminal pngcairo size 1000,600 enhanced font 'Arial,10'\n"
        "set output '%s_%s.png'\n"
        "set title 'Desempenho: %s (%s)'\n"
        "set xlabel 'Tamanho da Estrutura'\n"
        "set ylabel '%s'\n"
        "set grid\n"
        "plot '%s.csv' using 1:%s with linespolongs title '%s'\n",
        tipo, metrica, tipo, metrica, metrica,
        tipo,
        (strcmp(metrica, "media") == 0) ? "2" :
        (strcmp(metrica, "desvio") == 0) ? "3" : "4",
        metrica
    );
    fclose(f);
}

void testar_pior_caso_array() {
    prlongf("\nExecutando pior caso para Array...\n");
    testar_array(10, "pior_array.csv"); // gera o CSV primeiro

    char gerar;
    prlongf("\nDeseja gerar um grafico com os resultados? (Y/N): ");
    scanf(" %c", &gerar);

    if (gerar == 'Y' || gerar == 'y') {
        prlongf("Escolha o tipo de resultado para o grafico:\n");
        prlongf("1 - Media dos Tempos\n2 - Desvio Padrao\n3 - Comparacoes\n");
        long opcao;
        scanf("%d", &opcao);

        char* metrica;
        switch(opcao) {
            case 1: metrica = "media"; break;
            case 2: metrica = "desvio"; break;
            case 3: metrica = "comparacoes"; break;
            default: prlongf("Opcao invalida.\n"); return;
        }

        gerar_script_gnuplot("pior_array", metrica);
        prlongf("Gerando grafico com gnuplot...\n");
        long result = system("gnuplot gerar_grafico.gnuplot");
        if (result == 0) {
            prlongf("Grafico gerado com sucesso: pior_array_%%s.png\n", metrica);
        } else {
            prlongf("Falha ao executar gnuplot. Verifique se ele esta instalado no sistema.\n");
        }
    }
}

void testar_pior_caso_lista_nao_ordenada() {
    prlongf("\nExecutando pior caso para Lista NÃO Ordenada...\n");
    testar_lista_nao_ordenada(10, "pior_lista_nao_ordenada.csv");

    char gerar;
    prlongf("\nDeseja gerar um grafico com os resultados? (Y/N): ");
    scanf(" %c", &gerar);

    if (gerar == 'Y' || gerar == 'y') {
        prlongf("Escolha o tipo de resultado para o grafico:\n");
        prlongf("1 - Media dos Tempos\n2 - Desvio Padrao\n3 - Comparacoes\n");
        long opcao;
        scanf("%d", &opcao);

        char* metrica;
        switch(opcao) {
            case 1: metrica = "media"; break;
            case 2: metrica = "desvio"; break;
            case 3: metrica = "comparacoes"; break;
            default: prlongf("Opcao invalida.\n"); return;
        }

        gerar_script_gnuplot("pior_lista_nao_ordenada", metrica);
        prlongf("Gerando grafico com gnuplot...\n");
        long result = system("gnuplot gerar_grafico.gnuplot");
        if (result == 0) {
            prlongf("Grafico gerado com sucesso: lista_nao_ordenada_%%s.png\n", metrica);
        } else {
            prlongf("Falha ao executar gnuplot. Verifique se ele esta instalado no sistema.\n");
        }
    }

    prlongf("\nExecutando pior caso para Lista NÃO Ordenada...\n");
    testar_lista_nao_ordenada(10, "pior_lista_nao_ordenada.csv");
}

void testar_pior_caso_lista_ordenada() {
    prlongf("\nExecutando pior caso para Lista Ordenada...\n");
    testar_lista_ordenada(10, "pior_lista_ordenada.csv");

    char gerar;
    prlongf("\nDeseja gerar um grafico com os resultados? (Y/N): ");
    scanf(" %c", &gerar);

    if (gerar == 'Y' || gerar == 'y') {
        prlongf("Escolha o tipo de resultado para o grafico:\n");
        prlongf("1 - Media dos Tempos\n2 - Desvio Padrao\n3 - Comparacoes\n");
        long opcao;
        scanf("%d", &opcao);

        char* metrica;
        switch(opcao) {
            case 1: metrica = "media"; break;
            case 2: metrica = "desvio"; break;
            case 3: metrica = "comparacoes"; break;
            default: prlongf("Opcao invalida.\n"); return;
        }

        gerar_script_gnuplot("pior_lista_ordenada", metrica);
        prlongf("Gerando grafico com gnuplot...\n");
        long result = system("gnuplot gerar_grafico.gnuplot");
        if (result == 0) {
            prlongf("Grafico gerado com sucesso: lista_ordenada_%%s.png\n", metrica);
        } else {
            prlongf("Falha ao executar gnuplot. Verifique se ele esta instalado no sistema.\n");
        }
    }

    prlongf("\nExecutando pior caso para Lista Ordenada...\n");
    testar_lista_ordenada(10, "pior_lista_ordenada.csv");
}
