#include <iostream>
#include <string>
#include <unistd.h>

#include "Tokenizer.hpp"
#include "Parser.hpp"

using std::string;
using address_recognition::Tokenizer;
using address_recognition::Parser;

int main(int _argc, char **_argv) {
    int opt;
    string inFilePath;
    while ((opt = getopt(_argc, _argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                inFilePath = optarg;
                break;
            case '?':
                std::cerr << "Unknown option: '" << char(optopt) << "'!" << std::endl;
                break;
        }
    }

    Tokenizer t(inFilePath);
    Parser p(t);
    p.run();

    return 0;
}