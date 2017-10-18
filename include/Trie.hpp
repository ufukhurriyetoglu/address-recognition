#pragma once

#include "reference.hpp"
#include <enums.hpp>

#define ENG_LET 26

namespace address_recognition {
    class Trie {
        class TrieNode {
        public:
            void print();

            explicit TrieNode();

            TrieNode *getSon(long _idx) const;

            void addSon(long _idx);

            bool &isEndOfStr() { return this->m_isEndOfStr; }

        private:
            std::unique_ptr<TrieNode> m_sons[ENG_LET];
            bool m_isEndOfStr;
        };

        std::unique_ptr<TrieNode> m_head;
    public:
        Trie();

        void print();

        bool contains(const string &_query);

        void addString(const string &_newString);
    };
}