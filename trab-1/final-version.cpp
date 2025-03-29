/*
Versão final do código.

Este programa utiliza o conceito de permutação cíclica para calcular quantos ciclos são necessários até a repetição da sequência inicial.
A repetição de uma sequência só será possível ao retornar à configuração inicial.
Para determinar quantos ciclos são necessários, encontramos o tamanho dos ciclos individuais dentro da permutação
 e calculamos o MMC (mínimo múltiplo comum) desses tamanhos.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Função para carregar o arquivo "filename" e armazenar a segunda linha em um vetor "chave".
// A primeira linha indica o tamanho da permutação e não precisa ser armazenada, pois usamos "size()" do vetor.
void loadFile(const string &filename, vector<int> &chave)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Erro ao abrir arquivo: " << filename << endl;
        return;
    }

    int N;
    file >> N;
    chave.resize(N);
    for (int i = 0; i < N; i++)
    {
        file >> chave[i];
    }

    file.close();
}

// Algoritmo de Euclides para calcular o MDC (máximo divisor comum)
long long mdc(long long a, long long b)
{
    while (b != 0)
    {
        long long tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

// Cálculo do MMC (mínimo múltiplo comum) baseado na relação MMC(a, b) = (a * b) / MDC(a, b)
long long mmc(long long a, long long b)
{
    return (a / mdc(a, b)) * b;
}

// Função que encontra os ciclos na permutação e retorna seus tamanhos
vector<int> findCycle(const vector<int> &chave)
{
    int n = chave.size();
    vector<bool> visited(n, false); // Vetor para marcar os números já visitados
    vector<int> cycles;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i]) // Se o número ainda não foi processado, iniciamos um novo ciclo
        {
            int aux = i;
            int tamCycle = 0;

            // Percorremos o ciclo até retornarmos ao número inicial
            while (!visited[aux])
            {
                visited[aux] = true;
                aux = chave[aux]; // Segue a permutação
                tamCycle++;
            }
            cycles.push_back(tamCycle); // Armazena o tamanho do ciclo encontrado
        }
    }
    return cycles;
}

// Função que calcula o MMC dos tamanhos dos ciclos encontrados
long long calculateOrder(const vector<int> &chave)
{
    vector<int> cycles = findCycle(chave);
    long long res = 1;

    // Percorre os vector com os tamanhos usando o iterador size e armazena o resultado dos MMCs em res
    for (int size : cycles)
    {
        res = mmc(res, size);
    }

    return res;
}

int main()
{
    vector<int> chave;

    for (int i = 7; i < 20; i++)
    {
        string filename = "caso" + to_string(i) + "1.txt";
        loadFile(filename, chave);
        cout << "Caso " << i << "1: " << calculateOrder(chave) << endl;
    }

    return 0;
}
