#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

void loadFile(const string &filename, int &tamVet, vector<int> &chave)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Erro ao abrir o arquivo: " + filename);
    }

    string line;

    if (getline(file, line))
    {
        stringstream streamline(line);
        if (!(streamline >> tamVet))
        {
            throw runtime_error("Erro lendo tamVet");
        }
    }
    else
        throw runtime_error("Não conseguiu pegar primeira linha");

    if (getline(file, line))
    {
        stringstream streamline(line);
        int aux;
        while (streamline >> aux)
        {
            chave.push_back(aux);
        }
    }
    else
        throw runtime_error("Não conseguiu pegar segunda linha");

    file.close();
}

bool compare(const vector<int> &vet, const vector<vector<int>> &res, long long &operacoes)
{
    for (const auto &v : res)
    {
        for (int i = 0; i < vet.size(); i++)
        {
            operacoes++; // comparação entre inteiros
            if (v[i] != vet[i])
                break;
        }
        if (v == vet)
            return true;
    }
    return false;
}

int makeItDance(const int tamVet, const vector<int> &chave, long long &operacoes)
{
    vector<int> vet(tamVet);
    for (int i = 0; i < tamVet; i++)
    {
        vet[i] = i;
        operacoes++; // atribuição
    }

    vector<int> aux(tamVet);
    aux = move(vet);
    operacoes += tamVet; // cópia com move

    vector<vector<int>> res;
    res.push_back(aux);
    operacoes++; // push_back

    long long rodadas = 0;

    while (true)
    {
        vector<int> tmp(tamVet);
        operacoes++; // alocação do vetor tmp

        for (int i = 0; i < tamVet; i++)
        {
            tmp[i] = vet[chave[i]];
            operacoes += 3; // 2 acessos e 1 atribuição
        }

        rodadas++;

        if (compare(tmp, res, operacoes))
        {
            return rodadas;
        }

        res.push_back(tmp);
        operacoes++; // push_back

        vet = move(tmp);
        operacoes += tamVet; // cópia por move
    }
}

int main()
{
    ofstream csv("resultados.csv");
    csv << "caso,tamVet,rodadas,operacoes,memoria_MB\n";

    int tamVet;
    vector<int> chave;

    for (int i = 7; i < 20; i++)
    {
        chave.clear();
        loadFile("caso" + to_string(i) + "1.txt", tamVet, chave);

        long long operacoes = 0;
        long long rodadas = makeItDance(tamVet, chave, operacoes);

        size_t memoria = rodadas * tamVet * sizeof(int); // estimativa grosseira
        double memoriaMB = memoria / (1024.0 * 1024.0);

        cout << fixed << setprecision(2);
        cout << "caso" << i << "1: " << rodadas << " rodadas, "
             << operacoes << " operações, "
             << memoriaMB << " MB\n";

        csv << "caso" << i << "1," << tamVet << "," << rodadas << "," << operacoes << "," << memoriaMB << "\n";
    }

    csv.close();
}
