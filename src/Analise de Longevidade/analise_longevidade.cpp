#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

struct Bloco {
    int id;
    vector<string> instrucoes;
    vector<int> prox_bloco;
    vector<string> def;
    vector<string> use;
    vector<string> in;
    vector<string> out;
};

bool contem(const vector<string>& v, const string& s) {
    for (const string& x : v) {
        if (x == s) return true;
    }
    return false;
}

int main() {
    vector<Bloco> grafo_fluxo;
    string linha;

    while (getline(cin, linha)) {
        if (linha.empty()) continue;

        int id, qtd;
        sscanf(linha.c_str(), "%d %d", &id, &qtd);

        Bloco b;
        b.id = id;

        for (int j = 0; j < qtd; j++) {
            getline(cin, linha);
            b.instrucoes.push_back(linha);
        }

        getline(cin, linha);
        string temp = "";
        for (char c : linha) {
            if (c == ' ') {
                if (!temp.empty() && temp != "0") {
                    b.prox_bloco.push_back(stoi(temp));
                }
                temp = "";
            } else {
                temp += c;
            }
        }
        if (!temp.empty() && temp != "0") {
            b.prox_bloco.push_back(stoi(temp));
        }

        for (const string& inst : b.instrucoes) {
            vector<string> tokens;
            string p = "";
            for (char c : inst) {
                if (c == ' ' || c == ';') {
                    if (!p.empty()) tokens.push_back(p);
                    p = "";
                } else {
                    p += c;
                }
            }
            if (!p.empty()) tokens.push_back(p);

            if (!tokens.empty()) {
                string destino = tokens[0];
                if (!contem(b.def, destino)) b.def.push_back(destino);
            }

            for (size_t i = 2; i < tokens.size(); i++) {
                string variavel = tokens[i];
                if (variavel != "+" && variavel != "-" && variavel != "*" && variavel != "/") {
                    if (!isdigit(variavel[0]) && !contem(b.def, variavel) && !contem(b.use, variavel)) {
                        b.use.push_back(variavel);
                    }
                }
            }
        }

        grafo_fluxo.push_back(b);
    }

    bool alterado;
    do {
        alterado = false;
        for (Bloco& b : grafo_fluxo) {
            vector<string> Prox_saida;
            for (int idSucessor : b.prox_bloco) {
                for (const Bloco& bb : grafo_fluxo) {
                    if (bb.id == idSucessor) {
                        for (const string& x : bb.in) {
                            if (!contem(Prox_saida, x)) Prox_saida.push_back(x);
                        }
                    }
                }
            }

            if (Prox_saida != b.out) {
                b.out = Prox_saida;
                alterado = true;
            }

            vector<string> Prox_entrada = b.use;
            for (const string& x : b.out) {
                if (!contem(b.def, x) && !contem(Prox_entrada, x)) {
                    Prox_entrada.push_back(x);
                }
            }

            if (Prox_entrada != b.in) {
                b.in = Prox_entrada;
                alterado = true;
            }
        }
    } while (alterado);

    for (const Bloco& b : grafo_fluxo) {
        cout << "OUT[ " << b.id << " ] = { ";
        for (size_t j = 0; j < b.out.size(); j++) {
            cout << b.out[j];
            if (j < b.out.size() - 1) cout << ", ";
        }
        cout << " }\n";

        cout << "IN[ " << b.id << " ] = { ";
        for (size_t j = 0; j < b.in.size(); j++) {
            cout << b.in[j];
            if (j < b.in.size() - 1) cout << ", ";
        }
        cout << " }\n\n";
    }

    return 0;
}
