#pragma once

#include "reference.hpp"
#include "Tokenizer.hpp"
#include "TrieManager.hpp"

using address_recognition::Tokenizer;
using address_recognition::TrieManager;

namespace address_recognition {
    class Parser {

    public:
        Parser(Tokenizer &_tokenizer);

        void run();

        const vector<string> &getTokens() const { return this->m_tokens; }

    private:
        Tokenizer &m_tokenizer;
        vector<string> m_tokens;
        TrieManager m_trieMgr;
    };
}