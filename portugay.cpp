// Copyright (c) 1ukidev <leo.monteiro06@live.com>. Licensed under the MIT Licence.
// See the LICENCE file in the repository root for full licence text.

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

void printHelp() {
    std::cout << "Uso: portugay [-h/--help] [-o NOME_ARQUIVO] ARQUIVO_ENTRADA\n";
    std::cout << "Um programa inspirado no Portugol para fins educacionais.\n";
    std::cout << "O programa recebe o texto, traduz para C em um novo arquivo e por fim compila-o usando o GCC.\n\n";
    std::cout << "Opções:\n";
    std::cout << "  -h, --help       Exibe esta ajuda.\n";
    std::cout << "  -o NOME_ARQUIVO  Especifica o nome do arquivo de saída.\n";
    std::cout << "  -n               Faz com que o arquivo gerado não seja compilado.\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Erro: Nenhum arquivo de entrada fornecido.\n\n";
        printHelp();
        return 1;
    }

    std::string inputFileName;
    std::string outputFileName = "out.c";
    bool compileOnly = false;

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
                std::cout << "Erro: Nome do arquivo de saída não fornecido.\n\n";
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
        std::cout << "Erro: Nenhum arquivo de entrada fornecido.\n\n";
        printHelp();
        return 1;
    }

    std::ifstream inputFile(inputFileName);
    if (!inputFile) {
        std::cout << "Erro: Não foi possível abrir o arquivo de entrada.\n";
        return 1;
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile) {
        std::cout << "Erro: Não foi possível abrir o arquivo de saída.\n";
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
        if (line.find("//") == 0 || line.find("/*") == 0) {
            continue;
        }
        for (auto const& [key, value] : keywords) {
            size_t pos = 0;
            while ((pos = line.find(key, pos)) != std::string::npos) {
                line.replace(pos, key.length(), value);
                pos += value.length();
            }
        }
        outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();

    if (!compileOnly) {
        const std::string compilerCommand = "gcc -x c -O2 -pipe " + outputFileName;
        const int result = std::system(compilerCommand.c_str());

        if(result == 0) {
            return 0;
        } else {
            return 1;
        }
    }

    return 0;
}