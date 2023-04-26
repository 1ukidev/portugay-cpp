// Copyright (c) 1ukidev <leo.monteiro06@live.com>. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

void printHelp() {
    using namespace std;

    cout << "Uso: portugay [-h/--help] [-o NOME_ARQUIVO] ARQUIVO_ENTRADA\n";
    cout << "Um programa inspirado no Portugol para fins educacionais.\n";
    cout << "O programa recebe o texto, traduz para C em um novo arquivo e por fim compila-o usando o GCC.\n\n";
    cout << "Opções:\n";
    cout << "  -h, --help       Exibe esta ajuda.\n";
    cout << "  -o NOME_ARQUIVO  Especifica o nome do arquivo de saída.\n";
    cout << "  -n               Faz com que o arquivo gerado não seja compilado.\n";
}

int main(int argc, char* argv[]) {
    using namespace std;

    if (argc < 2) {
        cout << "Erro: Nenhum arquivo de entrada fornecido.\n\n";
        printHelp();
        return 1;
    }

    string inputFileName;
    string outputFileName = "out.c";
    bool compileOnly = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h" || arg ==  "--help") {
            printHelp();
            return 0;
        } else if (arg == "-o") {
            if (i + 1 < argc) {
                outputFileName = argv[i + 1];
                ++i;
            } else {
                cout << "Erro: Nome do arquivo de saída não fornecido.\n\n";
                printHelp();
                return 1;
            }
        } else if (arg == "-n") {
            compileOnly = true;
        } else {
            inputFileName = arg;
        }
    }

    if (inputFileName.empty()) {
        cout << "Erro: Nenhum arquivo de entrada fornecido.\n\n";
        printHelp();
        return 1;
    }

    ifstream inputFile(inputFileName);
    if (!inputFile) {
        cout << "Erro: Não foi possível abrir o arquivo de entrada.\n";
        return 1;
    }

    ofstream outputFile(outputFileName);
    if (!outputFile) {
        cout << "Erro: Não foi possível abrir o arquivo de saída.\n";
        return 1;
    }

    unordered_map<string, string> keywords {
        { "principal", "main" },
        { "incluir", "#include" },
        { "inteiro", "int" },
        { "real", "float" },
        { "vazio", "void" },
        { "caractere", "char" },
        { "escrever", "printf" },
        { "leia", "scanf" },
        { "para", "for" },
        { "enquanto", "while" },
        { "faca", "do" },
        { "se", "if" },
        { "senao", "else" },
        { "escolha", "switch" },
        { "caso", "case" },
        { "outrocaso", "default" },
        { "retornar", "return" },
        { "pausar", "break" },
        { "continuar", "continue" },
        { "sistema", "system" },
    };

    string line;
    while (getline(inputFile, line)) {
        if (line.find("//") == 0 || line.find("/*") == 0) {
            continue;
        }
        for (auto const& [key, value] : keywords) {
            size_t pos = 0;
            while ((pos = line.find(key, pos)) != string::npos) {
                line.replace(pos, key.length(), value);
                pos += value.length();
            }
        }
        outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();

    if (!compileOnly) {
        const string compilerCommand = "gcc -x c -O2 -pipe " + outputFileName;
        const int result = system(compilerCommand.c_str());

        if(result == 0) {
            return 0;
        } else {
            return 1;
        }
    }

    return 0;
}