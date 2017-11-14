#pragma once

#include "reference.hpp"
#include <enums.hpp>

namespace address_recognition {
    class Trie {
    public:
        explicit Trie();

        void print(bool _formatted = false);

        int save(const string &_filePath);

        int load(const string &_filePath);

        bool contains(const wstring &_query);

        void addString(const wstring &_newString);

    private:
        class TrieNode;

        void iterativeStep(const wchar_t *_data, size_t _size);

        class TrieNode {
        public:

            void print(bool _formatted = false);

            void save(wofstream &_fileOut);

            TrieNode *getSon(wchar_t _keyValue) const;

            void addSon(wchar_t _charVal);

            bool isLast() const { return this->m_isLast; }

            void setIsLast(bool _last) { this->m_isLast = _last; }

        private:
            std::map<wchar_t, unique_ptr<TrieNode >> m_sons;

            bool m_isLast = false;
        };

        std::unique_ptr<TrieNode> m_head;
    };
}