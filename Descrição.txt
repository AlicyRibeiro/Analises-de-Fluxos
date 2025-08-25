	
UNIVERSIDADE FEDERAL DO CEARÁ – CAMPUS QUIXADÁ
CURSO DE ENGENHARIA DE COMPUTAÇÃO
DISCIPLINA: COMPILADORES
PROFESSOR: LUCAS ISMAILY BEZERRA FREITAS
ALUNA:  Ana Alicy Ribeiro dos Santos	
	Ana Beatriz Leite Damascena  
	Kaylane Castro Evangelista

TRABALHO II – ANÁLISE DE FLUXO DE DADOS

------------------------------------------------------------
ESTRUTURA DO PROJETO
------------------------------------------------------------

trabalho2/
├── integrantes.txt                -> Identificação das alunas
├── instrucoes para execucao.txt   -> Orientações sobre compilação e uso dos códigos
├── relatorios/                    -> Relatórios explicativos de cada questão
├── src/                           -> Diretório com os códigos-fonte das 3 análises
│   ├── Analise de Longevidade/
│   │   ├── analise_longevidade.cpp
│   │   ├── analise_longevidade     -> binário gerado
│   │   ├── Analise_Longevidade     -> binário alternativo
│   │   ├── analises_fluxo          -> binário alternativo
│   │   ├── entrada.txt             -> arquivo de entrada local
│   │   ├── Exemplos_testes.txt     -> exemplos ou instruções de uso
│   │   └── Makefile
│   │
│   ├── Available Expressions/
│   │   ├── available_expressions.cpp
│   │   ├── entrada.txt             -> arquivo de entrada local
│   │   ├── outras entradas.txt     -> arquivo com outras entradas para teste do codigo
│   │   ├── Makefile
│   │   └── available_expr          -> binário gerado
│   │
│   └── Reaching Definitions/
│       ├── inc/                    -> arquivos de cabeçalho (headers)
│       ├── obj/                    -> arquivos objeto (.o)
│       ├── src/                    -> arquivos .cpp
│       ├── tests/                  -> arquivos .in (entrada) e .out (saída)
│       ├── exe                     -> binário gerado
│       └── Makefile

------------------------------------------------------------
OBJETIVO DO TRABALHO
------------------------------------------------------------

Este trabalho tem como objetivo implementar três análises clássicas
de fluxo de dados para compiladores, com base no livro:

"Compiladores: Princípios e Práticas", de Kenneth C. Louden (2ª edição),
e nos slides da disciplina.

Cada análise foi desenvolvida em um diretório próprio dentro de src/,
com entrada formatada conforme o enunciado e saída contendo os conjuntos
IN e OUT de cada bloco básico.

------------------------------------------------------------
QUESTÕES IMPLEMENTADAS
------------------------------------------------------------

1. Analise de Longevidade/
   -> Implementa a Análise de Longevidade (Liveness Analysis)
   -> Detecta variáveis que ainda serão usadas no futuro em um ponto do programa

2. Reaching Definitions/
   -> Implementa o algoritmo de Definições Alcançantes
   -> Detecta quais atribuições podem ter alcançado um ponto de uso da variável

3. Available Expressions/
   -> Implementa o algoritmo de Expressões Disponíveis
   -> Detecta expressões que já foram avaliadas e não foram invalidadas,
      podendo ser reutilizadas sem reavaliação

------------------------------------------------------------
PADRÃO DE ENTRADA E SAÍDA
------------------------------------------------------------

A entrada é composta por blocos rotulados (ex: B1:), com instruções
em código de três endereços. Ao final, os sucessores de cada bloco
são indicados por linha, ou a entrada é lida de arquivos .in.

Exemplo de saída no terminal:

OUT[1] = { a+b c+d }
IN[1] = { a+b c+d t1+t2 }

Os conjuntos são calculados com base nas fórmulas de propagação até ponto fixo
utilizando GEN, KILL, IN e OUT conforme o livro de Louden.

------------------------------------------------------------
RELATÓRIOS
------------------------------------------------------------

Os relatórios contidos em `relatorios/` explicam:

- Como cada algoritmo funciona
- Como os blocos e conjuntos foram estruturados
- Capturas de tela, testes e justificativa do código conforme slides e livro

------------------------------------------------------------
ARQUIVO integrantes.txt
------------------------------------------------------------

Contém o nome completo das alunas responsáveis pelo desenvolvimento
do trabalho e entrega.

------------------------------------------------------------
REFERÊNCIAS
------------------------------------------------------------

- Kenneth C. Louden – Compiladores: Princípios e Práticas (2ª edição)
- Slides e PDFs fornecidos pelo professor:
  - Conceitos de Otimização
  - Análise de Fluxo de Dados
  - Representação Intermediária
  - Alocação de Registradores

