/*
Versão final do código.

Este programa utiliza o conceito de permutação cíclica para calcular quantos ciclos são necessários até a repetição da sequência inicial.
A repetição de uma sequência só será possível ao retornar à configuração inicial.
Para determinar quantos ciclos são necessários, encontramos o tamanho dos ciclos individuais dentro da permutação
 e calculamos o MMC (mínimo múltiplo comum) desses tamanhos. Para rodar a main sem contagem de operações, versão mais "limpa" do codigo
 é preciso ter o compilador C++17+ ou superior
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <numeric>

using namespace std;
using namespace std::chrono;

long long operacoes = 0; // contador global de operações

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
    operacoes++; // leitura do N
    chave.resize(N);
    operacoes += N; // resize

    for (int i = 0; i < N; i++)
    {
        file >> chave[i];
        operacoes++; // leitura e atribuição por iteração
    }

    file.close();
}

 // Algoritmo de Euclides para calcular o MDC
 /*long long mdc(long long a, long long b)
 {
     while (b != 0)
     {
         operacoes++; // comparação
        long long tmp = b;
         b = a % b;
                 a = tmp;
        operacoes += 3; // atribuições
     }
     return a;
 } */

/* MMC baseado em MDC
 long long mmc(long long a, long long b)
 {
      int resto;
     int i;
    for(i = 1; i>0; i++)
     {
         operacoes++;
         resto = (a*i) % b;
        if(resto == 0) break;
     }
     return (a*i);
 } */

long long mmc(long long a, long long b) {
    return lcm(a, b);
}

vector<int> findCycle(const vector<int> &chave)
{
    int n = chave.size();
    operacoes++; // chamada size

    vector<bool> visited(n, false);
    vector<int> cycles;

    operacoes += n; // inicialização do visited

    for (int i = 0; i < n; i++)
    {
        operacoes++; // comparação
        if (!visited[i])
        {
            int aux = i;
            int tamCycle = 0;
            operacoes += 2; // inicializações

            while (!visited[aux])
            {
                visited[aux] = true;
                aux = chave[aux];
                tamCycle++;
                operacoes += 4; // atribuição, acesso e incremento
            }

            cycles.push_back(tamCycle);
            operacoes++; // push_back
        }
    }

    return cycles;
}

long long calculateOrder(const vector<int> &chave)
{
    vector<int> cycles = findCycle(chave);
    long long res = 1;
    operacoes++; // inicialização de res

    for (int size : cycles)
    {
        res = mmc(res, size);
        operacoes++; // atribuição
    }

    return res;
}

/* int main() // main com contagem de ops
 {
     vector<int> chave;

     ofstream csv("resultadosV3.csv");
     csv << "Caso,Operacoes,Tempo(ms)\n"; // Cabeçalho

     for (int i = 7; i < 20; i++)
     {
         string filename = "caso" + to_string(i) + "1.txt";
         chave.clear();
         loadFile(filename, chave);

         long long operacoes = 0;
         auto start = high_resolution_clock::now();

         // Contagem de operações dentro de calculateOrder
         vector<int> cycles;
         int n = chave.size();
         vector<bool> visited(n, false);

         for (int i = 0; i < n; i++)         {
             operacoes++; // comparação visited[i]
            if (!visited[i])
             {
                int aux = i;
               int tamCycle = 0;
                while (!visited[aux])
                 {
                    operacoes += 2; // comparação e acesso
                    visited[aux] = true;
                   aux = chave[aux];
                    tamCycle++;
                    operacoes += 2; // atribuição e incremento
                }
                 cycles.push_back(tamCycle);
             }        }

        long long res = 1;
         for (int size : cycles)
         {
             operacoes += 3; // uma multiplicação, uma divisão e uma atribuição
             res = (res / mdc(res, size)) * size;
         }

         auto end = high_resolution_clock::now();
         auto duracao = duration_cast<nanoseconds>(end - start).count();

         cout << "caso " << i << "1: " << res << " operacoes: " << operacoes << " tempo: " << duracao << " ms\n";
         csv << i << "," << operacoes << "," << duracao << "\n";
     }

    csv.close();
     return 0;
} */

int main() // sem contagem de ops, só tempo
{
    vector<int> chave;
    ofstream csv("resultadosV3.csv");
    csv << "Caso,Tempo(ns)\n";

    for (int i = 7; i < 20; i++)
    {
        string filename = "caso" + to_string(i) + "1.txt";
        chave.clear();
        loadFile(filename, chave);

        auto start = high_resolution_clock::now();
        long long res = calculateOrder(chave);
        auto end = high_resolution_clock::now();
        auto duracao = duration_cast<nanoseconds>(end - start).count();

        cout << "caso " << i << "1: " << res << " tempo: " << duracao << " ns\n";
        csv << i << "," << duracao << "\n";
    }

    csv.close();
    return 0;
}