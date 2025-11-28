/*
 * =====================================================================================
 * 
 * PROJETO: SISTEMA DE ORDENAÇÃO DE JOGADORES DE FUTEBOL
 * 
 * DESENVOLVEDORES:
 * - Isabela Majeste
 * - Joaquim Pedro  
 * - Victoria Tambasco
 * 
 * INSTITUIÇÃO: UNIFAL - UNIVERSIDADE FEDERAL DE ALFENAS
 * CURSO: CIÊNCIA DA COMPUTAÇÃO
 * DISCIPLINA: ANÁLISE E DESENVOLVIMENTO DE SISTEMAS II - PRÁTICA
 * 
 * OBJETIVO:
 * Este programa tem como objetivo implementar e comparar diferentes algoritmos de 
 * ordenação aplicados a um dataset de jogadores de futebol. O sistema permite ao 
 * usuário escolher entre três métodos de ordenação (Bubble Sort, Merge Sort e 
 * Bucket Sort) para ordenar os jogadores por nome, com suporte a caracteres 
 * acentuados. Para cada ordenação, são exibidas métricas detalhadas de desempenho
 * incluindo tempo de execução, número de operações e consumo de memória.
 * 
 * FUNCIONAMENTO:
 * 1. Carrega dados de jogadores a partir de um arquivo CSV
 * 2. Oferece menu interativo com três algoritmos de ordenação
 * 3. Executa a ordenação selecionada e exibe o vetor completo ordenado
 * 4. Apresenta métricas de desempenho detalhadas
 * 5. Permite salvar o resultado em arquivo CSV
 * 6. Suporta caracteres acentuados através do locale pt_BR.UTF-8
 * 
 * =====================================================================================
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>  // Para suporte a caracteres acentuados

// ============================================================================
// ESTRUTURAS DE DADOS
// ============================================================================

/**
 * Estrutura que representa um jogador de futebol
 * Contém todas as informações básicas de um jogador
 */
typedef struct p
{
    char name[100];          // Nome do jogador
    char posicion[100];      // Posição em campo
    char nationalite[100];   // Nacionalidade
    char team[100];          // Clube atual
    int age;                 // Idade
    struct p *prox;          // Ponteiro para próximo (uso em listas)
} player;

/**
 * Estrutura para armazenar métricas de desempenho dos algoritmos
 * Utilizada para comparar a eficiência dos diferentes métodos
 */
typedef struct {
    double tempo_execucao;   // Tempo total em segundos
    long long comparacoes;   // Número de comparações realizadas
    long long trocas;        // Número de trocas/operações de movimentação
    double memoria_gasta;    // Memória utilizada em MB
} Metricas;

// ============================================================================
// VARIÁVEIS GLOBAIS PARA CONTAGEM DE OPERAÇÕES
// ============================================================================

long long comparacoes_count = 0;  // Contador global de comparações
long long trocas_count = 0;       // Contador global de trocas

// ============================================================================
// FUNÇÕES AUXILIARES E DE COMPARAÇÃO
// ============================================================================

/**
 * Função para comparar duas strings considerando a localização
 * Utiliza strcoll() que é sensível ao locale configurado
 * 
 * @param a Primeira string para comparação
 * @param b Segunda string para comparação
 * @return Retorna <0 se a < b, 0 se a == b, >0 se a > b
 */
int compararStrings(const char *a, const char *b) {
    comparacoes_count++;  // Incrementa contador de comparações
    return strcoll(a, b); // Usa strcoll que considera locale (acentos)
}

/**
 * Função para trocar dois jogadores de posição no vetor
 * 
 * @param a Ponteiro para o primeiro jogador
 * @param b Ponteiro para o segundo jogador
 */
void trocarPlayers(player *a, player *b) {
    trocas_count++;  // Incrementa contador de trocas
    player temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Função para imprimir todos os jogadores do vetor
 * Exibe formato tabular com todas as informações
 * 
 * @param players Vetor de jogadores
 * @param n Número total de jogadores
 */
void imprimirTodosJogadores(player *players, int n) {
    printf("\n=== VETOR COMPLETO ORDENADO (%d jogadores) ===\n", n);
    for (int i = 0; i < n; i++) {
        // Formatação alinhada para melhor visualização
        printf("%3d. %-25s | %-15s | %-15s | %-25s | %2d anos\n", 
               i + 1, 
               players[i].name, 
               players[i].posicion, 
               players[i].nationalite, 
               players[i].team, 
               players[i].age);
    }
    printf("=== FIM DO VETOR ORDENADO ===\n\n");
}

/**
 * Função para exibir as métricas de desempenho do algoritmo
 * 
 * @param metricas Estrutura contendo todas as métricas coletadas
 * @param metodo Nome do método de ordenação utilizado
 */
void exibirMetricas(Metricas metricas, const char *metodo) {
    printf("\n=== MÉTRICAS DO %s ===\n", metodo);
    printf("Tempo de execução:        %.4f milissegundos\n", metricas.tempo_execucao * 1000);
    printf("Operações de comparação:  %lld\n", metricas.comparacoes);
    printf("Operações de troca:       %lld\n", metricas.trocas);
    printf("Memória gasta:           %.6f MB\n", metricas.memoria_gasta);
    printf("==============================\n\n");
}

// ============================================================================
// ALGORITMOS DE ORDENAÇÃO
// ============================================================================

/**
 * 1. BUBBLE SORT - Algoritmo de ordenação simples
 * Complexidade: O(n²) no pior caso
 * Estável: Sim
 * In-place: Sim
 * 
 * @param players Vetor de jogadores a ser ordenado
 * @param n Tamanho do vetor
 * @param metricas Ponteiro para estrutura de métricas
 */
void bubbleSort(player *players, int n, Metricas *metricas) {
    // Reinicia contadores para esta execução
    comparacoes_count = 0;
    trocas_count = 0;
    
    // Algoritmo Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Compara elementos adjacentes
            if (compararStrings(players[j].name, players[j + 1].name) > 0) {
                trocarPlayers(&players[j], &players[j + 1]);  // Troca se estiverem na ordem errada
            }
        }
    }
    
    // Atualiza métricas
    metricas->comparacoes = comparacoes_count;
    metricas->trocas = trocas_count;
    metricas->memoria_gasta = n * sizeof(player) / 1024.0 / 1024.0; // Calcula memória em MB
}

/**
 * 2. MERGE SORT - Algoritmo de ordenação ótimo (divisão e conquista)
 * Complexidade: O(n log n) em todos os casos
 * Estável: Sim
 * In-place: Não (requer memória auxiliar)
 */

/**
 * Função auxiliar do Merge Sort para mesclar dois subarrays ordenados
 * 
 * @param players Vetor principal
 * @param left Índice inicial do primeiro subarray
 * @param mid Índice do meio (fim do primeiro, início do segundo)
 * @param right Índice final do segundo subarray
 */
void merge(player *players, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;  // Tamanho do primeiro subarray
    int n2 = right - mid;     // Tamanho do segundo subarray
    
    // Aloca arrays temporários
    player *L = (player*)malloc(n1 * sizeof(player));
    player *R = (player*)malloc(n2 * sizeof(player));
    
    // Copia dados para arrays temporários
    for (i = 0; i < n1; i++)
        L[i] = players[left + i];
    for (j = 0; j < n2; j++)
        R[j] = players[mid + 1 + j];
    
    // Mescla os arrays temporários de volta no array original
    i = 0;      // Índice do primeiro subarray
    j = 0;      // Índice do segundo subarray  
    k = left;   // Índice do array mesclado
    
    while (i < n1 && j < n2) {
        if (compararStrings(L[i].name, R[j].name) <= 0) {
            players[k] = L[i];
            trocas_count++;  // Conta cópia como operação de troca
            i++;
        } else {
            players[k] = R[j];
            trocas_count++;  // Conta cópia como operação de troca
            j++;
        }
        k++;
    }
    
    // Copia elementos restantes do primeiro subarray, se houver
    while (i < n1) {
        players[k] = L[i];
        trocas_count++;
        i++;
        k++;
    }
    
    // Copia elementos restantes do segundo subarray, se houver
    while (j < n2) {
        players[k] = R[j];
        trocas_count++;
        j++;
        k++;
    }
    
    // Libera memória dos arrays temporários
    free(L);
    free(R);
}

/**
 * Função recursiva principal do Merge Sort
 * 
 * @param players Vetor a ser ordenado
 * @param left Índice inicial
 * @param right Índice final
 */
void mergeSortRecursivo(player *players, int left, int right) {
    if (left < right) {
        // Encontra o ponto médio
        int mid = left + (right - left) / 2;
        
        // Ordena primeira e segunda metades
        mergeSortRecursivo(players, left, mid);
        mergeSortRecursivo(players, mid + 1, right);
        
        // Mescla as metades ordenadas
        merge(players, left, mid, right);
    }
}

/**
 * Função principal do Merge Sort
 * 
 * @param players Vetor de jogadores
 * @param n Tamanho do vetor
 * @param metricas Ponteiro para métricas
 */
void mergeSort(player *players, int n, Metricas *metricas) {
    comparacoes_count = 0;
    trocas_count = 0;
    
    // Chama função recursiva
    mergeSortRecursivo(players, 0, n - 1);
    
    // Atualiza métricas
    metricas->comparacoes = comparacoes_count;
    metricas->trocas = trocas_count;
    metricas->memoria_gasta = (n * sizeof(player) * 2) / 1024.0 / 1024.0; // Considera arrays temporários
}

/**
 * 3. BUCKET SORT - Algoritmo de ordenação linear por distribuição
 * Complexidade: O(n + k) no melhor caso
 * Estável: Sim (quando implementado corretamente)
 * In-place: Não
 */

/**
 * Função para normalizar strings (remover acentos para distribuição nos buckets)
 * Necessária para garantir distribuição correta no Bucket Sort
 * 
 * @param str String a ser normalizada
 */
void normalizarString(char *str) {
    // Mapeamento de caracteres acentuados UTF-8 para equivalentes sem acento
    for (int i = 0; str[i]; i++) {
        switch ((unsigned char)str[i]) {
            case 0xC3: // Prefixo UTF-8 para caracteres acentuados latinos
                switch ((unsigned char)str[i + 1]) {
                    case 0x81: case 0xA1: str[i] = 'a'; str[i+1] = ' '; break; // Á, á
                    case 0x89: case 0xA9: str[i] = 'e'; str[i+1] = ' '; break; // É, é
                    case 0x8D: case 0xAD: str[i] = 'i'; str[i+1] = ' '; break; // Í, í
                    case 0x93: case 0xB3: str[i] = 'o'; str[i+1] = ' '; break; // Ó, ó
                    case 0x9A: case 0xBA: str[i] = 'u'; str[i+1] = ' '; break; // Ú, ú
                    case 0x87: case 0xA7: str[i] = 'c'; str[i+1] = ' '; break; // Ç, ç
                    case 0x91: case 0xB1: str[i] = 'n'; str[i+1] = ' '; break; // Ñ, ñ
                }
                break;
        }
    }
    
    // Remove espaços extras criados pela normalização
    char *src = str, *dst = str;
    while (*src) {
        if (*src != ' ') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

/**
 * Implementação do Bucket Sort para ordenação por primeira letra do nome
 * 
 * @param players Vetor de jogadores
 * @param n Tamanho do vetor
 * @param metricas Ponteiro para métricas
 */
void bucketSort(player *players, int n, Metricas *metricas) {
    comparacoes_count = 0;
    trocas_count = 0;
    
    // Cria 26 buckets (A-Z)
    player **buckets = (player**)malloc(26 * sizeof(player*));
    int *tamanhos = (int*)calloc(26, sizeof(int));
    int *capacidades = (int*)malloc(26 * sizeof(int));
    
    // Calcula memória utilizada pelos buckets
    double memoria_buckets = 0;
    memoria_buckets += 26 * sizeof(player*); // Array de ponteiros
    memoria_buckets += 26 * sizeof(int) * 2; // Arrays de tamanhos e capacidades
    
    // Inicializa buckets com capacidade inicial
    for (int i = 0; i < 26; i++) {
        capacidades[i] = 10;  // Capacidade inicial de cada bucket
        buckets[i] = (player*)malloc(capacidades[i] * sizeof(player));
        tamanhos[i] = 0;
        memoria_buckets += capacidades[i] * sizeof(player);
    }
    
    // Fase de distribuição: coloca cada jogador no bucket correspondente
    for (int i = 0; i < n; i++) {
        char nome_normalizado[100];
        strcpy(nome_normalizado, players[i].name);
        normalizarString(nome_normalizado);  // Normaliza para lidar com acentos
        
        char primeiraLetra = nome_normalizado[0];
        int bucketIndex;
        
        // Determina índice do bucket baseado na primeira letra
        if (primeiraLetra >= 'a' && primeiraLetra <= 'z') {
            bucketIndex = primeiraLetra - 'a';
        } else if (primeiraLetra >= 'A' && primeiraLetra <= 'Z') {
            bucketIndex = primeiraLetra - 'A';
        } else {
            bucketIndex = 0;  // Caracteres especiais vão para o bucket A
        }
        
        // Verifica se precisa redimensionar o bucket
        if (tamanhos[bucketIndex] >= capacidades[bucketIndex]) {
            capacidades[bucketIndex] *= 2;  // Dobra a capacidade
            buckets[bucketIndex] = (player*)realloc(buckets[bucketIndex], 
                                                capacidades[bucketIndex] * sizeof(player));
            memoria_buckets += capacidades[bucketIndex] / 2 * sizeof(player); // Memória adicional
        }
        
        // Adiciona jogador ao bucket
        buckets[bucketIndex][tamanhos[bucketIndex]] = players[i];
        tamanhos[bucketIndex]++;
    }
    
    // Fase de ordenação: ordena cada bucket individualmente
    Metricas metricas_bucket;
    for (int i = 0; i < 26; i++) {
        if (tamanhos[i] > 0) {
            bubbleSort(buckets[i], tamanhos[i], &metricas_bucket);
            // Acumula métricas de todos os buckets
            comparacoes_count += metricas_bucket.comparacoes;
            trocas_count += metricas_bucket.trocas;
        }
    }
    
    // Fase de concatenação: junta todos os buckets ordenados no array original
    int index = 0;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < tamanhos[i]; j++) {
            players[index++] = buckets[i][j];
        }
        free(buckets[i]);  // Libera memória do bucket
    }
    
    // Libera estruturas auxiliares
    free(buckets);
    free(tamanhos);
    free(capacidades);
    
    // Atualiza métricas finais
    metricas->comparacoes = comparacoes_count;
    metricas->trocas = trocas_count;
    metricas->memoria_gasta = (n * sizeof(player) + memoria_buckets) / 1024.0 / 1024.0;
}

// ============================================================================
// FUNÇÕES DE ARQUIVO E INTERFACE
// ============================================================================

/**
 * Função para salvar o vetor ordenado em arquivo CSV
 * 
 * @param players Vetor ordenado
 * @param total Número total de jogadores
 * @param metodo Nome do método de ordenação usado
 */
void salvarCSV(player *players, int total, const char *metodo) {
    char filename[100];
    snprintf(filename, sizeof(filename), "jogadores_ordenados_%s.csv", metodo);
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao criar arquivo %s\n", filename);
        return;
    }
    
    // Escreve cabeçalho do CSV
    fprintf(file, "Nome,Posição,Naturalidade,Clube,Idade\n");
    
    // Escreve dados dos jogadores
    for (int i = 0; i < total; i++) {
        fprintf(file, "%s,%s,%s,%s,%d\n", 
                players[i].name, 
                players[i].posicion, 
                players[i].nationalite, 
                players[i].team, 
                players[i].age);
    }
    
    fclose(file);
    printf("Arquivo salvo com sucesso: %s\n", filename);
}

/**
 * Função para exibir o menu principal
 * Interface textual para interação com o usuário
 */
void exibirMenu() {
    printf("\n=== MENU DE ORDENAÇÃO ===\n");
    printf("1 - Ordenação Simples (Bubble Sort)\n");
    printf("2 - Ordenação Ótima (Merge Sort)\n");
    printf("3 - Ordenação Linear (Bucket Sort)\n");
    printf("4 - Sair\n");
    printf("Escolha uma opção: ");
}

/**
 * Função principal que processa a ordenação selecionada
 * Coordena todo o processo: cópia, ordenação, exibição e salvamento
 * 
 * @param jogadores Vetor original de jogadores
 * @param total Número total de jogadores
 * @param opcao Opção de ordenação selecionada
 */
void processarOrdenacao(player *jogadores, int total, int opcao) {
    char *nomeMetodo;
    char *nomeDisplay;
    clock_t inicio, fim;
    Metricas metricas;
    
    // Cria cópia do vetor original para não modificar os dados originais
    player *copia = (player*)malloc(total * sizeof(player));
    if (copia == NULL) {
        printf("Erro ao alocar memória para cópia\n");
        return;
    }
    memcpy(copia, jogadores, total * sizeof(player));
    
    printf("\nOrdenando...\n");
    inicio = clock();  // Marca início do tempo
    
    // Executa algoritmo selecionado
    switch (opcao) {
        case 1:
            bubbleSort(copia, total, &metricas);
            nomeMetodo = "bubble_sort";
            nomeDisplay = "BUBBLE SORT";
            break;
        case 2:
            mergeSort(copia, total, &metricas);
            nomeMetodo = "merge_sort";
            nomeDisplay = "MERGE SORT";
            break;
        case 3:
            bucketSort(copia, total, &metricas);
            nomeMetodo = "bucket_sort";
            nomeDisplay = "BUCKET SORT";
            break;
        default:
            free(copia);
            return;
    }
    
    fim = clock();  // Marca fim do tempo
    metricas.tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    // Exibe resultados: primeiro o vetor ordenado, depois as métricas
    imprimirTodosJogadores(copia, total);
    exibirMetricas(metricas, nomeDisplay);
    
    // Oferece opção de salvar resultados
    printf("Deseja salvar o vetor ordenado? (s/n): ");
    char resposta;
    scanf(" %c", &resposta);
    
    if (resposta == 's' || resposta == 'S') {
        salvarCSV(copia, total, nomeMetodo);
    } else {
        printf("Arquivo não salvo.\n");
    }
    
    free(copia);  // Libera memória da cópia
}

// ============================================================================
// FUNÇÕES DE CARREGAMENTO DE DADOS
// ============================================================================

/**
 * Função para ler dados de jogadores a partir de arquivo CSV
 * 
 * @param filename Nome do arquivo CSV
 * @param total_players Ponteiro para variável que receberá o total de jogadores
 * @return Ponteiro para vetor alocado com os jogadores, ou NULL em caso de erro
 */
player *lerCSV(const char *filename, int *total_players)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return NULL;
    }

    int count = 0;
    char linha[500];

    // Pula linha de cabeçalho
    if (fgets(linha, sizeof(linha), file) == NULL) {
        printf("Erro: arquivo vazio ou inválido\n");
        fclose(file);
        return NULL;
    }

    // Conta número de linhas de dados
    while (fgets(linha, sizeof(linha), file) != NULL) {
        count++;
    }
    
    if (count == 0) {
        printf("Nenhum dado encontrado no arquivo\n");
        fclose(file);
        return NULL;
    }
    
    // Retorna ao início do arquivo para ler os dados
    rewind(file);
    
    // Aloca memória para o vetor de jogadores
    player* players = (player*)malloc(count * sizeof(player));
    if (players == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(file);
        return NULL;
    }
    
    // Pula cabeçalho novamente
    fgets(linha, sizeof(linha), file);
    
    // Lê e processa cada linha de dados
    int index = 0;
    while (fgets(linha, sizeof(linha), file) != NULL && index < count) {
        // Remove caracteres de nova linha
        linha[strcspn(linha, "\n")] = 0;
        linha[strcspn(linha, "\r")] = 0;

        char *token;
        int campo = 0;

        // Cria cópia da linha para tokenização (strtok modifica a string original)
        char linha_copia[500];
        strcpy(linha_copia, linha);
        
        // Divide a linha em tokens separados por vírgula
        token = strtok(linha_copia, ",");
        while (token != NULL && campo < 5)
        {
            // Remove espaços em branco do início e fim do token
            while (*token == ' ') token++;
            char *end = token + strlen(token) - 1;
            while (end > token && *end == ' ') end--;
            *(end + 1) = '\0';

            // Distribui tokens nos campos correspondentes da estrutura
            switch (campo)
            {
            case 0: // Nome
                strncpy(players[index].name, token, sizeof(players[index].name) - 1);
                players[index].name[sizeof(players[index].name) - 1] = '\0';
                break;
            case 1: // Posição
                strncpy(players[index].posicion, token, sizeof(players[index].posicion) - 1);
                players[index].posicion[sizeof(players[index].posicion) - 1] = '\0';
                break;
            case 2: // Naturalidade
                strncpy(players[index].nationalite, token, sizeof(players[index].nationalite) - 1);
                players[index].nationalite[sizeof(players[index].nationalite) - 1] = '\0';
                break;
            case 3: // Clube
                strncpy(players[index].team, token, sizeof(players[index].team) - 1);
                players[index].team[sizeof(players[index].team) - 1] = '\0';
                break;
            case 4: // Idade
                players[index].age = atoi(token);  // Converte string para inteiro
                break;
            }
            campo++;
            token = strtok(NULL, ",");
        }

        players[index].prox = NULL;
        index++;
    }
    
    *total_players = count;
    fclose(file);
    return players;
}

/**
 * Função para liberar memória alocada para o vetor de jogadores
 * 
 * @param players Ponteiro para o vetor a ser liberado
 */
void liberarPlayers(player *players) {
    free(players);
}

/**
 * Função para verificar se um arquivo existe
 * 
 * @param filename Nome do arquivo
 * @return 1 se existe, 0 se não existe
 */
int arquivoExiste(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================

/**
 * Função principal do programa
 * Coordena todo o fluxo de execução
 */
int main() {
    // Configura locale para suporte a caracteres acentuados
    setlocale(LC_ALL, "pt_BR.UTF-8");
    printf("Locale configurado para: %s\n", setlocale(LC_ALL, NULL));
    
    printf("Carregando dados do arquivo...\n");
    
    const char* caminho_arquivo = "../jogadores.csv";
    
    // Verifica se arquivo existe
    if (!arquivoExiste(caminho_arquivo)) {
        printf("ERRO: Arquivo '%s' não encontrado!\n", caminho_arquivo);
        printf("Certifique-se de que o arquivo está no diretório correto.\n");
        return 1;
    }
    
    int total;
    player *jogadores = lerCSV(caminho_arquivo, &total);

    if (jogadores == NULL) {
        printf("Falha ao carregar dados.\n");
        return 1;
    }
    
    printf("Dados carregados com sucesso! Total de jogadores: %d\n", total);
    
    // Loop principal do menu
    int opcao;
    do {
        exibirMenu();
        scanf("%d", &opcao);
        
        if (opcao >= 1 && opcao <= 3) {
            processarOrdenacao(jogadores, total, opcao);
        } else if (opcao != 4) {
            printf("Opção inválida! Tente novamente.\n");
        }
        
    } while (opcao != 4);  // Repete até usuário escolher sair
    
    // Libera memória e encerra programa
    liberarPlayers(jogadores);
    printf("Programa encerrado.\n");
    
    return 0;
}