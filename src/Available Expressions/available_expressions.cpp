#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// Normaliza expressões comutativas como a+b ≡ b+a
string normaliza_expr(string a, string op, string b) {
    if ((op == "+" || op == "*") && b < a) swap(a, b);
    return a + op + b;
}

// Extrai expressões do tipo x = y op z
set<string> extrair_exprs(const vector<string>& bloco) {
    set<string> exprs;
    for (const auto& linha : bloco) {
        istringstream ss(linha);
        string dst, eq, op1, op, op2;
        ss >> dst >> eq >> op1;
        if (ss >> op >> op2) {
            exprs.insert(normaliza_expr(op1, op, op2));
        }
    }
    return exprs;
}

// Extrai variáveis definidas no bloco (lado esquerdo de atribuição)
set<string> variaveis_definidas(const vector<string>& bloco) {
    set<string> vars;
    for (const auto& linha : bloco) {
        istringstream ss(linha);
        string dst, eq;
        ss >> dst >> eq;
        vars.insert(dst);
    }
    return vars;
}

// Retorna expressões do universo que usam a variável
set<string> exprs_que_usam(const string& var, const set<string>& universo) {
    set<string> usadas;
    for (const auto& expr : universo) {
        size_t op_pos = expr.find_first_of("+-*/");
        if (op_pos != string::npos) {
            string op1 = expr.substr(0, op_pos);
            string op2 = expr.substr(op_pos + 1);
            if (op1 == var || op2 == var) {
                usadas.insert(expr);
            }
        }
    }
    return usadas;
}

// Impressão formatada
void imprimir_conjunto(const string& nome, int bloco, const set<string>& conjunto) {
    cout << nome << "[" << bloco + 1 << "] = { ";
    for (const auto& e : conjunto)
        cout << e << " ";
    cout << "}\n";
}

int main() {
    ifstream fin("entrada.txt");
    if (!fin) {
        cerr << "Erro ao abrir 'entrada.txt'\n";
        return 1;
    }

    string linha;
    vector<vector<string>> blocos;
    vector<vector<int>> sucessores;

    // Lê blocos rotulados (ex: B1:, B2:)
    while (getline(fin, linha)) {
        if (linha.empty()) continue;
        if (linha[0] == 'B') {
            blocos.emplace_back();
            continue;
        }
        if (isdigit(linha[0]) || linha[0] == '0') break;
        blocos.back().push_back(linha);
    }

    // Lê os sucessores
    int N = blocos.size();
    sucessores.resize(N);
    int bloco_idx = 0;
    do {
        istringstream ss(linha);
        int s;
        while (ss >> s && s != 0)
            sucessores[bloco_idx].push_back(s - 1); // de 1-based para 0-based
        bloco_idx++;
    } while (getline(fin, linha) && bloco_idx < N);

    // Universo de expressões
    set<string> universo;
    for (const auto& bloco : blocos) {
        auto exprs = extrair_exprs(bloco);
        universo.insert(exprs.begin(), exprs.end());
    }

    // Geração de GEN e KILL
    vector<set<string>> GEN(N), KILL(N);
    for (int i = 0; i < N; ++i) {
        GEN[i] = extrair_exprs(blocos[i]);
        auto defs = variaveis_definidas(blocos[i]);
        for (const auto& var : defs) {
            auto afetadas = exprs_que_usam(var, universo);
            KILL[i].insert(afetadas.begin(), afetadas.end());
        }
    }

    // Inicialização de IN/OUT
    vector<set<string>> IN(N, universo), OUT(N);

    // Iteração até ponto fixo
    bool mudou = true;
    while (mudou) {
        mudou = false;
        for (int i = 0; i < N; ++i) {
            // IN[B] = interseção dos OUT dos predecessores
            set<string> new_in = universo;
            bool first = true;
            for (int j = 0; j < N; ++j) {
                for (int s : sucessores[j]) {
                    if (s == i) {
                        if (first) {
                            new_in = OUT[j];
                            first = false;
                        } else {
                            set<string> inter;
                            set_intersection(new_in.begin(), new_in.end(),
                                             OUT[j].begin(), OUT[j].end(),
                                             inserter(inter, inter.begin()));
                            new_in = inter;
                        }
                    }
                }
            }

            // OUT[B] = GEN[B] ∪ (IN[B] − KILL[B])
            set<string> new_out = GEN[i];
            for (const auto& e : IN[i])
                if (KILL[i].find(e) == KILL[i].end())
                    new_out.insert(e);

            if (new_in != IN[i] || new_out != OUT[i]) {
                IN[i] = new_in;
                OUT[i] = new_out;
                mudou = true;
            }
        }
    

    // Impressão final
    for (int i = 0; i < N; ++i) {
        imprimir_conjunto("OUT", i, OUT[i]);
        imprimir_conjunto("IN", i, IN[i]);
    }

    return 0;
}

}