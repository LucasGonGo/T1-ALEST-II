#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void loadFile(const string &filename, int &tamVet, vector<int> &chave)
{ // acho que ta pronto

    ifstream file(filename); // abrir arquivo usando a biblioteca ifstream

    if (!file.is_open()) // se não estiver aberto, deu erro
    {
        throw runtime_error("Erro ao abrir o arquivo: " + filename);
    }

    string line; // string para armazenar as linhas temporariamente

    if (getline(file, line)) // pega uma linha do "file" e coloca em "linha"
    {
        stringstream streamline(line); // cria um streamline com a linha lida
        if (!(streamline >> tamVet))   // armazena a linha na variavel tamVet
        {
            throw runtime_error("Erro lendo tamVet"); // msg de erro se não conseguir colocar a linha em tamVet
        }
    }
    else
        throw runtime_error("Não conseguiu pegar primeira linha"); // msg de erro se não conseguir pegar a linha

    if (getline(file, line)) // pega a segunda linha
    {
        stringstream streamline(line); // msm coisa da outra
        int aux;                       // variavel vetiliar para colocar os valores que tirarmos
                                       // da linha

        while (streamline >> aux) // enquanto tiver numeros para colocar, de push_back no vector
        {
            chave.push_back(aux);
        }
    }
    else
        throw runtime_error("Não conseguiu pegar segunda linha"); // msg de erro

    file.close(); // fecha o arquivo
}

bool compare(const vector<int> &vet, const vector<vector<int>> &res) //ridiculo
{
    for (const auto &v : res)
    {
        if (v == vet)
            return true; // se achou um igual retorna verdadeiro
    }
    return false;
}

int makeItDance(const int tamVet, const vector<int> chave)
{

    vector<vector<int>> res(tamVet);
    vector<int> vet(tamVet);

    for (int i = 0; i < tamVet; i++)
    {
        vet[i] = i; 
    }
    res.push_back(vet); 

    vet = chave;        
    res.push_back(vet); 
    bool deuCerto = false;

    while (!deuCerto)
    {
            vector<int> tmp(tamVet);

        for (int i = 0; i < tamVet - 1; i++)
        {
            tmp[i] = vet[chave[i]];

            if (!compare(tmp, res))
            {
                res.push_back(tmp);
            }
            else
                deuCerto = true;
        }
        vet = tmp;
    }
    return res.size();
}

int main()
{
    int tamVet;
    vector<int> chave;

    for(int i = 7; i<20; i++){
    loadFile("caso"+to_string(i)+"1.txt", tamVet, chave);
    cout << makeItDance(tamVet, chave)<<endl;
    }
}
