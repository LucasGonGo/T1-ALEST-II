#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <chrono> // Para medir tempo

using namespace std;
using namespace std::chrono;

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

long long makeItDance(const int tamVet, const vector<int> &chave, long long &operacoes)
{
    vector<int> vet(tamVet);
    for (int i = 0; i < tamVet; i++)
    {
        vet[i] = i;
        operacoes++; // atribuição
    }

    vector<int> aux = vet;
    operacoes += tamVet; // cópia de vetor

    long long rodadas = 0;

    while (true)
    {
        vector<int> tmp(tamVet);

        for (int i = 0; i < tamVet; i++)
        {
            tmp[i] = vet[chave[i]];
            operacoes += 2; // acesso a vet e chave + atribuição
        }

        rodadas++;
        operacoes++; // incremento de rodadas

        vet = move(tmp);
        operacoes += tamVet; // movimentação de vetor

        bool iguais = true;
        for (int i = 0; i < tamVet; i++)
        {
            operacoes++; // comparação
            if (vet[i] != aux[i])
            {
                iguais = false;
                break;
            }
        }
        operacoes += tamVet; // comparações feitas no for

        if (iguais)
            return rodadas;
    }
}

int main()
{
    int tamVet;
    vector<int> chave;
    
    ofstream csv("resultadosV2.csv");
    csv << "Caso,Operacoes,Tempo(ms)\n"; // Cabeçalho do CSV

    for (int i = 7; i < 13; i++)
    {
        chave.clear();
        loadFile("caso" + to_string(i) + "1.txt", tamVet, chave);

        long long operacoes = 0;
        auto start = high_resolution_clock::now();

        int rodadas = makeItDance(tamVet, chave, operacoes);

        auto end = high_resolution_clock::now();
        auto duracao = duration_cast<nanoseconds>(end - start).count();

        cout << "caso " << i << "1: " << rodadas << " rodadas, " << operacoes << " operacoes, " << duracao << " ns\n";

        csv << i << "," << operacoes << "," << duracao << "\n"; // Salva no arquivo
    }

    csv.close();
}