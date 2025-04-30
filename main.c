#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void testar_array(int num_buscas);
void testar_lista_nao_ordenada(int num_buscas);
void testar_lista_ordenada(int num_buscas);
void gerar_script_gnuplot(const char* tipo, const char* metrica);
void testar_pior_caso_array();
void testar_pior_caso_lista_nao_ordenada();
void testar_pior_caso_lista_ordenada();

int main() {
    setlocale(LC_ALL, "C"); // Garante separador decimal como ponto

    int escolha;
    printf("Bem-vindo ao programa de Avaliacao de Algoritmos de Busca!\n");
    printf("Escolha a estrutura que deseja testar:\n");
    printf("1 - Arranjo Estatico (Array)\n");
    printf("2 - Lista Ligada NAO Ordenada\n");
    printf("3 - Lista Ligada Ordenada\n");
    printf("4 - Pior Caso - Array\n");
    printf("5 - Pior Caso - Lista NAO Ordenada\n");
    printf("6 - Pior Caso - Lista Ordenada\n");
    printf("Digite sua escolha: ");
    scanf("%d", &escolha);

    int num_buscas;
    printf("Quantas buscas voce deseja realizar? ");
    scanf("%d", &num_buscas);

    switch(escolha) {
        case 4: testar_pior_caso_array(); return 0;
        case 5: testar_pior_caso_lista_nao_ordenada(); return 0;
        case 6: testar_pior_caso_lista_ordenada(); return 0;
        case 1: testar_array(num_buscas); break;
        case 2: testar_lista_nao_ordenada(num_buscas); break;
        case 3: testar_lista_ordenada(num_buscas); break;
        default: printf("Opcao invalida.\n"); return 0;
    }

    char gerar;
    printf("\nDeseja gerar um grafico com os resultados? (Y/N): ");
    scanf(" %c", &gerar);

    if (gerar == 'Y' || gerar == 'y') {
        printf("Escolha o tipo de resultado para o grafico:\n");
        printf("1 - Media dos Tempos\n2 - Desvio Padrao\n3 - Comparacoes\n");
        int opcao;
        scanf("%d", &opcao);

        char* metrica;
        switch(opcao) {
            case 1: metrica = "media"; break;
            case 2: metrica = "desvio"; break;
            case 3: metrica = "comparacoes"; break;
            default: printf("Opcao invalida.\n"); return 0;
        }

        const char* tipo[] = {"array", "lista_nao_ordenada", "lista_ordenada"};
        gerar_script_gnuplot(tipo[escolha - 1], metrica);

        printf("Gerando grafico com gnuplot...\n");
        int result = system("gnuplot gerar_grafico.gnuplot");
        if (result == 0) {
            printf("Grafico gerado com sucesso: %s_%s.png\n", tipo[escolha - 1], metrica);
        } else {
            printf("Falha ao executar gnuplot. Verifique se ele esta instalado no sistema.\n");
        }
    }

    return 0;
}

void gerar_script_gnuplot(const char* tipo, const char* metrica) {
    FILE* f = fopen("gerar_grafico.gnuplot", "w");
    if (!f) {
        printf("Erro ao criar script gnuplot.\n");
        return;
    }
    fprintf(f,
        "set datafile separator ','\n"
        "set terminal pngcairo size 1000,600 enhanced font 'Arial,10'\n"
        "set output '%s_%s.png'\n"
        "set title 'Desempenho: %s (%s)'\n"
        "set xlabel 'Tamanho da Estrutura'\n"
        "set ylabel '%s'\n"
        "set grid\n"
        "plot '%s.csv' using 1:%s with linespoints title '%s'\n",
        tipo, metrica, tipo, metrica, metrica,
        tipo,
        (strcmp(metrica, "media") == 0) ? "2" :
        (strcmp(metrica, "desvio") == 0) ? "3" : "4",
        metrica
    );
    fclose(f);
}

void testar_pior_caso_array() {
    printf("\nExecutando pior caso para Array...\n");
    testar_array(10); // simulando 10 execuções forçadas com chave inexistente
}

void testar_pior_caso_lista_nao_ordenada() {
    printf("\nExecutando pior caso para Lista NÃO Ordenada...\n");
    testar_lista_nao_ordenada(10);
}

void testar_pior_caso_lista_ordenada() {
    printf("\nExecutando pior caso para Lista Ordenada...\n");
    testar_lista_ordenada(10);
}
