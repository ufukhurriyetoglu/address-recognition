#pragma once

#include "reference.hpp"
#include <enums.hpp>

namespace address_recognition {
    class Trie {
    public:
        explicit Trie();

        void print();

        bool contains(const string &_query);

        void addString(const string &_newString);

    private:
        static const int UPPR_C_SIZE = 26;
        static const int LWR_C_SIZE = 26;
        static const int CPHR_SIZE = 10;
        static const int ALPHBT_SIZE = (UPPR_C_SIZE + LWR_C_SIZE + CPHR_SIZE);

        class TrieNode {
        public:
            explicit TrieNode();

            void print();

            TrieNode *getSon(long _idx) const;

            void addSon(long _idx);

            bool &isEndOfStr() { return this->m_isEndOfStr; }

        private:
            std::unique_ptr<TrieNode> m_sons[ALPHBT_SIZE];
            bool m_isEndOfStr;
        };

        static inline long handleIndex(long _in, bool _normalize = false);

        std::unique_ptr<TrieNode> m_head;
    };
}