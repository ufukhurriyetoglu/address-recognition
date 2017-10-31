#include "Tokenizer.hpp"
#include <TrieManager.hpp>
#include "Parser.hpp"

#include "reference.hpp"
#include <unistd.h>

using std::string;
using address_recognition::Tokenizer;
using address_recognition::Parser;
using address_recognition::TrieManager;

int main(int _argc, char **_argv) {
    int opt;
    string inFilePath;
    string triePath;
    bool load = false;
    while ((opt = getopt(_argc, _argv, "f:t:hg:")) != -1) {
        switch (opt) {
            case 'f':
                inFilePath = string(optarg);
                break;
            case 't':
                load = true;
                triePath = string(optarg);
                break;
            case 'g':
                triePath = string(optarg);
                break;
            case '?':
                logError(__FILE__, __LINE__, string(":Unknown option: '") + char(optopt) + string("'!"));
                break;
            case 'h':
                std::cout << "-f for input file to parse\n" \
                             "-t for input triepath (load)\n" \
                             "-g for output trie path (generate)\n" \
                             "-h for help" << std::endl;
                break;
            default:
                break;
        }
    }

//    if (!load) {
//        std::cout << "Running with -g -> generating trie from: " << triePath << std::endl;
//        return 0;
//    }

//    Tokenizer t(inFilePath);
//    Parser p(t);
//    p.run();

    return 0;
}