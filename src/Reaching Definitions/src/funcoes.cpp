#include "funcoes.hpp"

inline bool operator==(const Def& a, const Def& b);

// Ler instruções e o grafo de fluxo de controle
// Lê M instruções do padrão de entrada e retorna um vetor de strings
// Cada string representa uma linha de instrução
// Se ocorrer um erro ao ler uma linha, uma mensagem de erro é exibida no stderr
vector<string> lerInstrucoes(int M) {
    vector<string> instructions;
    instructions.reserve(M); //reserva espaço para evitar realocações
    for (int i = 0; i < M; ++i) {
        string linha;
        if (!getline(cin, linha)) {
            cerr << "Erro ao ler instrução na linha " << i << ".\n";
            continue;
        }
        instructions.push_back(linha);
    }
    if (instructions.size() < static_cast<size_t>(M)) {
        cerr << "Nem todas as instruções foram lidas.\n";
    }
    return instructions;
}

// Lê N blocos do padrão de entrada, onde cada bloco contém seus sucessores
// e retorna um mapa onde cada chave é o índice do bloco e o valor é um vetor de sucessores
map<int, vector<int>> lerCFG(int N) {
    map<int, vector<int>> cfg;
    for (int i = 0; i < N; ++i) {
        string linha;
        if (!getline(cin, linha)) {
            cerr << "Erro ao ler linha para o bloco " << i << ".\n";
            continue;
        }

        stringstream ss(linha);
        int s;
        while (ss >> s) {
            if (s != 0) {
                cfg[i].push_back(s);
            }
        }

        if (cfg[i].empty()) {
            cerr << "Bloco " << i << " não possui sucessores.\n";
        }
    }
    return cfg;
}

// Divide M instruções em N blocos, onde cada bloco recebe aproximadamente M/N instruções
// As instruções são distribuídas de forma que os primeiros blocos recebam uma instrução a mais se M não for divisível por N
vector<vector<string>> dividirBlocos(int N, int M, const vector<string>& instructions) {
    vector<vector<string>> blocos(N);
    int instr_por_bloco = M / N;
    int restante = M % N;
    int idx = 0;

    for (int b = 0; b < N; ++b) {
        int qtd = instr_por_bloco + (b < restante ? 1 : 0);
        blocos[b].reserve(qtd); //reserva espaço para evitar realocações
        for (int i = 0; i < qtd; ++i) {
            blocos[b].push_back(instructions[idx++]);
        }
    }

    if (idx != M) {
        cerr << "Nem todas as instrucoes foram atribuidas aos blocos.\n";
    }

    return blocos;
}

// Coleta todas as definições de variáveis em cada bloco
// Ela retorna um mapa onde a chave é o nome da variável e o valor é um vetor de pares (bloco, linha)
map<string, vector<pair<int, int>>> coletarDefinicoes(const vector<vector<string>>& blocos) {
    map<string, vector<pair<int, int>>> definicoes;
    for (size_t b = 0; b < blocos.size(); ++b) {
        for (size_t i = 0; i < blocos[b].size(); ++i) {
            string instr = blocos[b][i];
            size_t pos = instr.find('=');
            if (pos == string::npos) continue;

            //extrai o nome da variável e limpa os espaços em branco
            string var = instr.substr(0, pos);
            var.erase(remove_if(var.begin(), var.end(), ::isspace), var.end());
            definicoes[var].emplace_back(static_cast<int>(b), static_cast<int>(i));
        }
    }
    return definicoes;
}

// Constrói os conjuntos GEN e KILL para cada bloco
// GEN contém as definições de variáveis que são geradas no bloco
// KILL contém as definições de variáveis que são sobrescrtas no bloco
void construirGenKill(const vector<vector<string>>& blocos, const map<string, vector<pair<int, int>>>& definicoes, map<int, set<Def>>& GEN, map<int, set<Def>>& KILL) {
    for (size_t b = 0; b < blocos.size(); ++b) {
        set<string> processed_vars; // evitar operações redundantes
        for (size_t i = 0; i < blocos[b].size(); ++i) {
            string instr = blocos[b][i];
            size_t pos = instr.find('=');
            if (pos == string::npos) continue;

            string var = instr.substr(0, pos);
            var.erase(remove_if(var.begin(), var.end(), ::isspace), var.end());

            if (processed_vars.find(var) != processed_vars.end()) continue; // ignora variáveis ​​já processadas
            processed_vars.insert(var);

            Def current_def{var, b, i};
            GEN[b].insert(current_def);

            auto it_def = definicoes.find(var);
            if (it_def != definicoes.end()) {
                for (const auto& d : it_def->second) {
                    if (d.first != static_cast<int>(b) || d.second != static_cast<int>(i)) {
                        KILL[b].insert(Def{var, static_cast<size_t>(d.first), static_cast<size_t>(d.second)});
                    }
                }
            }
        }
    }
}

// 6. Construir predecessores
// Constrói um mapa de predecessores para cada bloco no gráfico de fluxo de controle (CFG)
// Cada bloco é mapeado para um conjunto de blocos que o precefem no CFG
map<int, set<int>> construirPredecessores(const map<int, vector<int>>& cfg) {
    map<int, set<int>> predecessores;
    for (const auto& [b, succ] : cfg) {
        for (int successor : succ) {
            predecessores[successor].insert(b);
        }
    }
    return predecessores;
}

// 7. Análise de fluxo
// Tealiza a análise de fluxo de dados usando o algoritmo de iteração
// sobre os blocos do CFG. Ela calcula os conjuntos IN e OUT para cada bloco
// IN[b] contém as definições que entram no bloco b
// OUT[b] contém as definições que saem do bloco b
void analiseFluxo(map<int, set<Def>>& IN, map<int, set<Def>>& OUT, const map<int, set<Def>>& GEN, const map<int, set<Def>>& KILL, const map<int, set<int>>& predecessores) {
    // inicializar OUT com valores GEN
    for (const auto& [b, gen_set] : GEN) {
        OUT[b] = gen_set;
    }

    bool mudou;
    do {
        mudou = false;

        for (const auto& [b, gen_set] : GEN) {
            // Calcula o novo IN[b] como a união de OUT dos predecessores
            set<Def> nova_IN;
            if (auto it_predecessores = predecessores.find(b); it_predecessores != predecessores.end()) {
                for (int p : it_predecessores->second) {
                    if (OUT.count(p)) {
                        nova_IN.insert(OUT.at(p).begin(), OUT.at(p).end());
                    }
                }
            }

            //verifica se IN[b] mudou
            if (auto it_IN = IN.find(b); it_IN != IN.end()) {
                for (const auto& d : it_IN->second) {
                    if (!nova_IN.count(d)) {
                        nova_IN.insert(d);
                    }
                }
            }
            if (nova_IN != IN[b]) {
                IN[b] = nova_IN;
                mudou = true;
            }

            //valcula novo OUT[b] usando GEN[b] e IN[b] - KILL[b]
            set<Def> nova_OUT = gen_set;
            if (auto it_KILL = KILL.find(b); it_KILL != KILL.end()) {
                for (const auto& d : IN[b]) {
                    if (!it_KILL->second.count(d)) {
                        nova_OUT.insert(d);
                    }
                }
            }

            //cerifica se OUT[b] mudou
            if (nova_OUT != OUT[b]) {
                OUT[b] = nova_OUT;
                mudou = true;
            }
        }
    } while (mudou);
}

void imprimirResultados(const map<int, set<Def>>& IN, const map<int, set<Def>>& OUT) {
    for (auto& [b, _] : IN) {
        cout << "Bloco " << b << ":\n  IN : { ";
        for (auto& d : IN.at(b)) {
            cout << "(" << d.var << "," << d.bloco << "," << d.linha << ") ";
        }
        cout << "}\n  OUT: { ";
        for (auto& d : OUT.at(b)) {
            cout << "(" << d.var << "," << d.bloco << "," << d.linha << ") ";
        }
        cout << "}\n";
    }
}
