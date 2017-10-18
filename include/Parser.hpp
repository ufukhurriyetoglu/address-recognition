#pragma once

#include "reference.hpp"
#include "Tokenizer.hpp"
#include "Token.hpp"

using address_recognition::Tokenizer;

namespace address_recognition {
    class Parser {

    public:
        Parser(Tokenizer &_tokenizer);

        void run();

        const vector<Token> &getTokens() const { return this->m_tokens; }

    private:
        Tokenizer &m_tokenizer;
        vector<Token> m_possibleZip;
        vector<Token> m_tokens;
    };
}