#ifndef FUNCOES_HPP
#define FUNCOES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

struct Def {
    string var;
    size_t bloco;
    size_t linha;

    bool operator<(const Def& other) const {
        if (var != other.var) return var < other.var;
        if (bloco != other.bloco) return bloco < other.bloco;
        return linha < other.linha;
    }
};

inline bool operator==(const Def& a, const Def& b) {
    return a.var == b.var && a.bloco == b.bloco && a.linha == b.linha;
}

vector<string> lerInstrucoes(int M);
map<int, vector<int>> lerCFG(int N);
vector<vector<string>> dividirBlocos(int N, int M, const vector<string>& instructions);
map<string, vector<pair<int, int>>> coletarDefinicoes(const vector<vector<string>>& blocos);
void construirGenKill(const vector<vector<string>>& blocos, const map<string, vector<pair<int, int>>>& definicoes, map<int, set<Def>>& GEN, map<int, set<Def>>& KILL);
map<int, set<int>> construirPredecessores(const map<int, vector<int>>& cfg);
void analiseFluxo(map<int, set<Def>>& IN, map<int, set<Def>>& OUT, const map<int, set<Def>>& GEN, const map<int, set<Def>>& KILL, const map<int, set<int>>& preds);
void imprimirResultados(const map<int, set<Def>>& IN, const map<int, set<Def>>& OUT);

#endif
