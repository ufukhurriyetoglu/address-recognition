#pragma once

#include "reference.hpp"
#include "Tokenizer.hpp"
#include "TrieManager.hpp"

using address_recognition::Tokenizer;
using address_recognition::TrieManager;

namespace address_recognition {
    class Parser {

    public:
        explicit Parser(Tokenizer &_tokenizer);

        void run();

        const vector<string> &getTokens() const { return this->m_tokens; }

        void addTriePath(const string &_path);

        void addTriePath(const vector<string> &_paths);

        void loadTries();

        bool isValid() const { return this->m_valid && this->m_tokenizer.isValid(); }

    private:
        Tokenizer &m_tokenizer;
        vector<string> m_tokens;
        TrieManager m_trieMgr;
        vector<string> m_triePaths;
        bool m_valid = false;
    };
}