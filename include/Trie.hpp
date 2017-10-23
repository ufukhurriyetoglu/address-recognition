#pragma once

#include "reference.hpp"
#include <enums.hpp>

namespace address_recognition {
    class Trie {
    public:
        explicit Trie();

        void print();

        void save(const string &_filePath);

        int load(const string &_filePath);

        bool contains(const string &_query);

        void addString(const string &_newString);

    private:
//        static const int UPPR_C_SIZE = 26;
//        static const int LWR_C_SIZE = 26;
//        static const int CPHR_SIZE = 10;
//        static const int ALPHBT_SIZE = (UPPR_C_SIZE + LWR_C_SIZE + CPHR_SIZE);

        class TrieNode;

        void recursionStep(TrieNode *_root, const char *_data, int _idx, size_t _size);

        void iterativeStep(const char *_data, size_t _size);

        class TrieNode {
        public:
            explicit TrieNode();

            void print();

            void save(ofstream &_fileOut);

            TrieNode *getSon(int _keyValue) const;

            void addSon(int _charVal);

            bool &isEndOfStr() { return this->m_isEndOfStr; }

        private:
            std::map<int, unique_ptr<TrieNode >> m_sons;
            bool m_isEndOfStr;
        };

        std::unique_ptr<TrieNode> m_head;
    };
}