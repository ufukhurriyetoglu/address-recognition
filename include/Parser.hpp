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

        void run(const std::function<void(const wstring &_token)> &_callback = nullptr);

        void run(const wstring &_seps, const std::function<void(const wstring &_token)> &_callback = nullptr);

        void addSection(const string &_parserSectionName,
                        const string &_trieMgrSectionName,
                        const string &_path);

        bool isValid() const {
            return this->m_valid && this->m_tokenizer.isValid();
        }

        bool contains(const wstring &_query);

        bool containsInSection(const wstring &_sectionName, const wstring &_query);

        void setSeparators(const wstring &_newSeps);

    private:
        Tokenizer &m_tokenizer;
        std::map<string, unique_ptr<TrieManager>> m_parserSections;
        wstring m_separators = L" ,.:;\n\r";
        bool m_valid = false;
    };
}
