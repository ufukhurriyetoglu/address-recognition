#pragma once

#include "reference.hpp"
#include "Token.hpp"


using address_recognition::Token;

namespace address_recognition {
    class Tokenizer {
    public:

        Tokenizer(const string &_fileName);

        int parseFile();

    private:
        string m_fileName;
        ifstream m_inputFile;
        vector<Token> m_tokens;

        string readNext();
    };
}