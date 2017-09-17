#include <iostream>
#include <string>
#include <unistd.h>

#include "Tokenizer.hpp"

using std::string;
using address_recognition::Tokenizer;

int main(int _argc, char **_argv){
    int opt;
    string inFilePath;
    while ( (opt = getopt(_argc, _argv, "f:")) != -1 ) {
        switch ( opt ) {
            case 'f':
                inFilePath = optarg;
                break;
            case '?':
            std::cerr << "Unknown option: '" << char(optopt) << "'!" << std::endl;
                break;
        }
    }

    if(inFilePath.empty()){
        return 1;
    }

    Tokenizer t(inFilePath);
    if(t.parseFile()){
        return 1;
    }

    return 0;
}