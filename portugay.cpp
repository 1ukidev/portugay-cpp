// Copyright (c) 1ukidev <leo.monteiro06@live.com>. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

void printHelp() {
    std::cout << "Uso: portugay [-h/--help] [-o NOME_ARQUIVO] ARQUIVO_ENTRADA" << std::endl;
    std::cout << "Um programa inspirado no Portugol para fins educacionais." << std::endl;
    std::cout << "O programa recebe o texto, traduz para C em um novo arquivo e por fim compila-o usando o GCC." << std::endl << std::endl;
    std::cout << "Opções:" << std::endl;
    std::cout << "  -h, --help       Exibe esta ajuda." << std::endl;
    std::cout << "  -o NOME_ARQUIVO  Especifica o nome do arquivo de saída." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Erro: Nenhum arquivo de entrada fornecido." << std::endl << std::endl;
        printHelp();
        return 1;
    }

    std::string inputFileName;
    std::string outputFileName = "out.c";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg ==  "--help") {
            printHelp();
            return 0;
        } else if (arg == "-o") {
            if (i + 1 < argc) {
                outputFileName = argv[i + 1];
                ++i;
            } else {
                std::cout << "Erro: Nome do arquivo de saída não fornecido." << std::endl << std::endl;
                printHelp();
                return 1;
            }
        } else {
            inputFileName = arg;
        }
    }

    if (inputFileName.empty()) {
        std::cout << "Erro: Nenhum arquivo de entrada fornecido." << std::endl << std::endl;
        printHelp();
        return 1;
    }

    std::ifstream inputFile(inputFileName);
    if (!inputFile) {
        std::cout << "Erro: Não foi possível abrir o arquivo de entrada." << std::endl;
        return 1;
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile) {
        std::cout << "Erro: Não foi possível abrir o arquivo de saída." << std::endl;
        return 1;
    }

    std::unordered_map<std::string, std::string> keywords {
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

    std::string line;
    while (std::getline(inputFile, line)) {
        for (auto const& [key, value] : keywords) {
            size_t pos = 0;
            while ((pos = line.find(key, pos)) != std::string::npos) {
                line.replace(pos, key.length(), value);
                pos += value.length();
            }
        }
        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::string compilerCommand = "gcc -x c -O2 -pipe " + outputFileName;
    int result = std::system(compilerCommand.c_str());

    if(result == 0) {
        return 0;
    } else {
        return 1;
    }
}