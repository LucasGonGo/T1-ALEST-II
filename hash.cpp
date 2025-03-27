#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    ifstream file("DomCasmurro_utf8.txt");                  // abre arquivo e coloca em file

    if(!file.is_open()) throw runtime_error("Não abriu!");  // confere se ta aberto

    unordered_map<string, int> wordCount;                                         // cria o hash com unordered_map

    string line;                                            // aux
    while(getline(file, line, ' '))                         // enquanto tiver linha, pega até o ' ' e coloca em line
    {
        wordCount[line]++;
    }

    for(const auto entry : wordCount)
    {   
        cout << entry.first << " : " << entry.second << endl; 
    }

}
