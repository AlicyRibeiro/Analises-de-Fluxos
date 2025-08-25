# Analises-de-Fluxos

# Trabalho II – Análise de Fluxo de Dados

##  Descrição do Projeto

Este repositório contém as implementações de três algoritmos clássicos de análise de fluxo de dados, desenvolvidos para a disciplina de Compiladores da Universidade Federal do Ceará (UFC) - Campus Quixadá. O objetivo do trabalho é aplicar os conceitos teóricos de otimização de código, calculando os conjuntos IN e OUT para cada bloco básico de um grafo de fluxo de controle, conforme a análise específica.

As soluções foram implementadas em C++ e se baseiam nas metodologias descritas no livro "Compiladores: Princípios e Práticas" de Kenneth C. Louden e nos materiais de aula.

### Autoras
* Ana Alicy Ribeiro dos Santos 
* Ana Beatriz Leite Damascena 
* Kaylane Castro Evangelista 

### Professor
* LUCAS ISMAILY BEZERRA FREITAS 

##  Estrutura do Projeto

O projeto está organizado com os códigos-fonte na pasta `src/`, relatórios explicativos em `relatorios/` e um arquivo de instruções detalhado.


* ├── instrucoes para execucao.txt
* ├── relatorios/
* │   ├── Relatório - Analise de Longevidade
* │   ├── Relatório - Available Expressions.txt
* │   └── Relatório - Reaching Definitions.pdf
* └── src/
* ├── Analise de Longevidade/  
* │   ├── analise_longevidade.cpp
* │   ├── entrada.txt
* │   ├── Exemplos_testes.txt
* │   └── Makefile
* │
* ├── Available Expressions/  
* │   ├── available_expressions.cpp
* │   ├── entrada.txt
* │   ├── outras entradas.txt
* │   └── Makefile
* │
* └── Reaching Definitions/  
* ├── inc/
* ├── obj/
* ├── src/
* ├── tests/
* ├── exe
* └── Makefile


## Análises Implementadas (Opção 3) 

Foram implementados três algoritmos de análise de fluxo de dados:

### 1. Análise de Longevidade (Liveness Analysis) 
* **Objetivo**: Determinar, para cada ponto do programa, quais variáveis ainda terão seus valores utilizados no futuro (variáveis "vivas").
* **Diretório**: `src/Analise de Longevidade/`.

### 2. Definições Alcançantes (Reaching Definitions) 
* **Objetivo**: Identificar, para cada ponto do programa, o conjunto de definições (atribuições a variáveis) que podem "alcançar" aquele ponto.
* **Diretório**: `src/Reaching Definitions/`.

### 3. Expressões Disponíveis (Available Expressions) 
* **Objetivo**: Determinar quais expressões já foram calculadas e cujos operandos não foram alterados, permitindo a reutilização do resultado para evitar recálculos (Eliminação de Subexpressão Comum).
* **Diretório**: `src/Available Expressions/`.

## 🚀 Compilação e Execução

Cada análise possui seu próprio diretório com um `Makefile` para automatizar o processo.

### Questão 1 – Análise de Longevidade
* **Diretório**: `src/Analise de Longevidade` 
* **Compilação**:
    ```bash
    make
    ```
* **Execução**:
    ```bash
    ./analise_longevidade < entrada.txt
    ```
* *Exemplos de entrada e saída podem ser encontrados no arquivo `Exemplos_testes.txt`*.

### Questão 2 – Reaching Definitions
* **Diretório**: `src/Reaching Definitions` 
* **Compilação**:
    ```bash
    make
    ```
* **Execução Automatizada (testes pré-definidos)**:
    ```bash
    make test
    ```
* **Execução Manual (arquivo específico)**:
    ```bash
    ./exe < tests/test1.in
    ```

  ### Questão 3 – Available Expressions
* **Diretório**: `src/Available Expressions` 
* **Compilação**:
    ```bash
    make
    ```
* **Execução**:
    ```bash
    ./available_expr < entrada.txt
    ```
* *Outros exemplos de teste estão disponíveis em `outras entradas.txt`*.

##  Formato de Entrada e Saída

### Entrada
A entrada para os algoritmos é um grafo de fluxo de controle, onde a primeira linha contém o número de blocos (N) e o número de instruções (M). Em seguida, vêm as M instruções em código de três endereços e, por fim, as listas de sucessores para cada bloco.

### Saída
Para todas as implementações, a saída exibe os conjuntos `IN` e `OUT` calculados para cada bloco básico, seguindo o formato padrão:
* OUT[1] = { ... }
* IN[1] = { ... }

* OUT[2] = { ... }
* IN[2] = { ... }

## 📚 Relatórios e Referências

### Relatórios
Explicações detalhadas sobre a implementação de cada algoritmo, as estruturas de dados utilizadas e as lógicas das equações de fluxo de dados podem ser encontradas na pasta `relatorios/`.

### Referências
* LOUDEN, Kenneth C. *Compiladores: Princípios e Práticas*. 2ª ed.
* Materiais didáticos fornecidos pela disciplina.
