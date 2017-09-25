#pragma once

#include "reference.hpp"
#include "Token.hpp"

using address_recognition::Token;

namespace address_recognition {
    class Tokenizer {
    public:
        Tokenizer(const string &_fileName);

        void getNexToken(std::function<void(const Token &_token)> _callback);

    private:
        string m_fileName;
        ifstream m_inputFile;
    };
}