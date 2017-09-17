#pragma once

#include "reference.hpp"
#include "Token.hpp"


using address_recognition::Token;

namespace address_recognition {
    class Tokenizer {
    public:
        Tokenizer(const string &_fileName);

        int parseFile();

        unsigned getTokensSize() {
            return this->m_tokens.size();
        }

        const vector<Token> &getTokens() {
            return this->m_tokens;
        }

    private:
        string m_fileName;
        ifstream m_inputFile;
        vector<Token> m_tokens;
        bool fileRead = false;
    };
}