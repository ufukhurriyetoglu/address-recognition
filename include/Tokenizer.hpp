#pragma once

#include "reference.hpp"
#include "Token.hpp"


using address_recognition::Token;

namespace address_recognition {
    class Tokenizer {
    public:
        Tokenizer(const string &_fileName);

        int parseFile();

        const vector<Token> &getTokens() {
            return this->m_tokens;
        }

        const vector<unsigned> &getPossibleZIPs() {
            return this->m_possibleZIPs;
        }

    private:
        string m_fileName;
        ifstream m_inputFile;
        vector<Token> m_tokens;
        vector<unsigned> m_possibleZIPs;
        bool fileRead = false;
    };
}