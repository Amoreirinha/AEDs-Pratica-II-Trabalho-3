# ⚽ Sistema de Ordenação de Jogadores de Futebol

## 🧠 Descrição do Projeto

Este projeto tem como objetivo **implementar e comparar diferentes algoritmos de ordenação** aplicados a um dataset de jogadores de futebol. O sistema permite ao usuário escolher entre três métodos de ordenação (**Bubble Sort**, **Merge Sort** e **Bucket Sort**) para ordenar os jogadores por nome, com suporte a caracteres acentuados.

Foi desenvolvido como parte das atividades práticas da disciplina **AEDS II - Prática**, sob orientação do professor **Iago**.

O sistema realiza o seguinte fluxo de execução:

1. **Carregamento de dados** a partir de um arquivo CSV contendo informações de jogadores
2. **Menu interativo** com três algoritmos de ordenação disponíveis
3. **Execução da ordenação** selecionada com exibição do vetor completo ordenado
4. **Apresentação de métricas detalhadas** de desempenho (tempo, comparações, trocas, memória)
5. **Opção de salvar** o resultado em arquivo CSV

---

## ⚙️ Estrutura do Projeto

```
├── main.c                    # Programa principal com todos os algoritmos
├── jogadores.csv            # Arquivo de dados dos jogadores (base de dados)
├── jogadores_ordenados_*.csv # Arquivos gerados com resultados ordenados
└── README.md                # Este arquivo
```

---

## 🧩 Funcionalidades

### 🔹 Carregamento de Dados
- Lê dados de jogadores a partir de arquivo CSV
- Suporte a caracteres acentuados através do locale `pt_BR.UTF-8`
- Processa campos: Nome, Posição, Nacionalidade, Clube, Idade

### 🔹 Algoritmos de Ordenação Implementados

#### 1. **Bubble Sort** (`bubbleSort()`)
- Algoritmo de ordenação simples
- Complexidade: O(n²) no pior caso
- Estável e in-place
- Ideal para conjuntos pequenos de dados

#### 2. **Merge Sort** (`mergeSort()`)
- Algoritmo de ordenação ótimo (divisão e conquista)
- Complexidade: O(n log n) em todos os casos
- Estável mas não in-place (requer memória auxiliar)
- Eficiente para grandes volumes de dados

#### 3. **Bucket Sort** (`bucketSort()`)
- Algoritmo de ordenação linear por distribuição
- Complexidade: O(n + k) no melhor caso
- Utiliza normalização de strings para lidar com acentos
- Distribui jogadores em buckets por primeira letra do nome

### 🔹 Sistema de Métricas
- **Tempo de execução** em milissegundos
- **Número de comparações** realizadas
- **Número de trocas/operações** de movimentação
- **Consumo de memória** em MB

### 🔹 Interface do Usuário
- Menu interativo para seleção do algoritmo
- Exibição do vetor completo ordenado em formato tabular
- Opção de salvar resultados em arquivo CSV
- Feedback visual durante o processamento

---

## 🏗️ Estruturas de Dados

### 🔸 Estrutura `player`
```c
typedef struct p {
    char name[100];          // Nome do jogador
    char posicion[100];      // Posição em campo
    char nationalite[100];   // Nacionalidade
    char team[100];          // Clube atual
    int age;                 // Idade
    struct p *prox;          // Ponteiro para próximo
} player;
```

### 🔸 Estrutura `Metricas`
```c
typedef struct {
    double tempo_execucao;   // Tempo total em segundos
    long long comparacoes;   // Número de comparações
    long long trocas;        // Número de trocas
    double memoria_gasta;    // Memória utilizada em MB
} Metricas;
```

---

## 🚀 Como Executar

### 1️⃣ Compilar o programa
```bash
gcc main.c -o ordenar_jogadores
./ordenar_jogadores
```

### 2️⃣ Requisitos
- Arquivo `jogadores.csv` no diretório pai (`../jogadores.csv`)
- Sistema com locale `pt_BR.UTF-8` para suporte a acentos

### 3️⃣ Fluxo de Execução
1. O programa carrega automaticamente os dados do arquivo CSV
2. Menu interativo é exibido com as opções de ordenação
3. Selecionar uma opção (1-3) executa a ordenação correspondente
4. Resultados e métricas são exibidos
5. Opção de salvar em arquivo CSV
6. Retorno ao menu principal até selecionar saída (4)

---

## 📊 Exemplo de Saída

```
=== MENU DE ORDENAÇÃO ===
1 - Ordenação Simples (Bubble Sort)
2 - Ordenação Ótima (Merge Sort)
3 - Ordenação Linear (Bucket Sort)
4 - Sair
Escolha uma opção: 2

Ordenando...

=== VETOR COMPLETO ORDENADO (850 jogadores) ===
  1. Adriano                  | Atacante       | Brasil         | Flamengo               | 35 anos
  2. Alexandre Pato           | Atacante       | Brasil         | São Paulo              | 31 anos
  ...
=== FIM DO VETOR ORDENADO ===

=== MÉTRICAS DO MERGE SORT ===
Tempo de execução:        15.2340 milissegundos
Operações de comparação:  12589
Operações de troca:       8450
Memória gasta:           0.065000 MB
==============================

Deseja salvar o vetor ordenado? (s/n): s
Arquivo salvo com sucesso: jogadores_ordenados_merge_sort.csv
```

---

## ⚡ Comparação de Algoritmos

| Algoritmo   | Complexidade | Estável | In-Place | Memória | Melhor Caso |
|-------------|--------------|---------|----------|---------|-------------|
| Bubble Sort | O(n²)        | ✅ Sim  | ✅ Sim   | O(1)    | O(n)        |
| Merge Sort  | O(n log n)   | ✅ Sim  | ❌ Não   | O(n)    | O(n log n)  |
| Bucket Sort | O(n + k)     | ✅ Sim  | ❌ Não   | O(n + k)| O(n + k)    |

---

## 🎯 Características Especiais

### 🔹 Suporte a Caracteres Acentuados
- Utiliza `strcoll()` com locale `pt_BR.UTF-8`
- Normalização de strings no Bucket Sort para distribuição correta
- Compatível com nomes em português e outros idiomas

### 🔹 Sistema de Métricas Avançado
- Contadores globais de operações
- Cálculo preciso de memória utilizada
- Medição de tempo com alta precisão

### 🔹 Manipulação de Arquivos
- Leitura robusta de CSV com tratamento de erros
- Geração de arquivos de saída formatados
- Verificação de existência de arquivos

---

## 👩‍💻 Autores

- **Joaquim Pedro do Nascimento Moreira de Jesus**  
- **Victória Almeida Tambasco**  
- **Isabela Mageste de Andrade**

---

## 📘 Disciplina

**Algoritmos e Estruturas de Dados II - Prática (AEDS II - Prática)**  
Professor: **Iago**  
Instituição: **UNIFAL - Universidade Federal de Alfenas**

---

## 🏁 Observações

- Certifique-se de que o arquivo `jogadores.csv` existe no diretório correto
- O programa foi desenvolvido e testado em ambiente Linux
- Para Windows, ajustes no locale podem ser necessários
- O tamanho do dataset afeta significativamente o desempenho dos algoritmos

---

## 📚 Referências Bibliográficas

- CORMEN, T. H.; LEISERSON, C. E.; RIVEST, R. L.; STEIN, C. **Introduction to Algorithms.** 3. ed. MIT Press, 2009.  
- KNUTH, D. E. **The Art of Computer Programming, Volume 3: Sorting and Searching.** Addison-Wesley, 1998.  
- TANENBAUM, A. S.; BOS, H. **Modern Operating Systems.** 4. ed. Pearson, 2014.  
- KING, K. N. **C Programming: A Modern Approach.** 2. ed. W. W. Norton & Company, 2008.  
- Documentação oficial do GNU C Library (glibc)

---

🧩 *Projeto desenvolvido para fins didáticos, com foco em implementação de algoritmos de ordenação, manipulação de estruturas de dados e análise de desempenho computacional.*
