#include "funcoes.hpp"

int main() {

    // 1. Receber as informações
    int N, M;
    cin >> N >> M;
    cin.ignore();

    // Leitura das M instruções
    auto instructions = lerInstrucoes(M);

 
    // Leitura do grafo de fluxo de controle
    auto cfg = lerCFG(N);

    // 2. Divisão das instruções em blocos
    auto blocos = dividirBlocos(N, M, instructions);

    // 3. Coletar todas as definições
    auto definicoes = coletarDefinicoes(blocos);

    // 4. Construir conjuntos GEN e KILL
    map<int, set<Def>> GEN, KILL;
    construirGenKill(blocos, definicoes, GEN, KILL);

    // 5. Construir predecessores
    auto preds = construirPredecessores(cfg);
    // 6. Análise de fluxo
    map<int, set<Def>> IN, OUT;
    analiseFluxo(IN, OUT, GEN, KILL, preds);

    // 7. Impressão dos resultados
    imprimirResultados(IN, OUT);
    return 0;
}
