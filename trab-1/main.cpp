#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

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

/*bool compare(const vector<int> &vet, const vector<vector<int>> &res) //ridiculo //v1.0
{
    for (const auto &v : res)
    {
        if (v == vet)
            return true; // se achou um igual retorna verdadeiro
    }
    return false;
}*/

// bool compare(const vector<int> &vet, const vector<vector<int>> &res) //v1.5
// {
//     for (const auto &v : res)
//     {
//         if(v[0] == vet[0])
//         {
//             if (v == vet)
//             {
//             return true;        // se achou um igual retorna verdadeiro
//             }
//         }
//     }                    
//     return false;
// }

//v2.0, usando unordered_set no lugar de vector<vector<int>>.

string vectorToString(const vector<int> &vet)
{
    string s;
    for (int num : vet)
    {
        s += to_string(num) + ",";
    }
    return s;
}

int makeItDance(const int tamVet, const vector<int> &chave) //quebrou, arruma
{
    vector<int> vet(tamVet);
    for (int i = 0; i < tamVet; i++)                //necessario.
    {                                               
        vet[i] = i; 
    }

    //vector<vector<int>> res;                
    //res.push_back(vet);                             //necessario.
   
    unordered_set<string> estadosVistos;
    estadosVistos.insert(vectorToString(vet));

    long rodadas = 0;                                //não crtz

    while (true)                                    //necessario.
    {
        vector<int> tmp(tamVet);                    

        for (int i = 0; i < tamVet; i++)            //necessario.
        {
            tmp[i] = vet[chave[i]];                 //necessario.
        }

        rodadas++;                                  //...

        string tmpStr = vectorToString(tmp);
        if (estadosVistos.count(tmpStr))
        {
            return rodadas;
        }

        estadosVistos.insert(tmpStr);
        vet = move(tmp);

        // if(compare(tmp, res))                       //necessario.
        // {
        //     return rodadas;
        // }

        //res.push_back(tmp);                         //necessario.
        //vet = tmp;                                  //necessario.
    }
}

int main()
{
    int tamVet;
    vector<int> chave;

    loadFile("caso7.txt", tamVet, chave);
    cout <<  makeItDance(tamVet, chave)<<endl;
    for(int i = 7; i<20; i++)
    {
        chave.clear();
        loadFile("caso"+to_string(i)+"1.txt", tamVet, chave);
        cout <<"caso "+to_string(i)+"1: "<< makeItDance(tamVet, chave)<<endl;
    }

    /*loadFile("caso7.txt", tamVet, chave);
    cout << makeItDance(tamVet, chave) << endl;*/
}
