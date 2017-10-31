#pragma once

#include "reference.hpp"
#include <enums.hpp>

namespace address_recognition {
    class Trie {
    public:
        explicit Trie();

        void print();

        int save(const string &_filePath);

        int load(const string &_filePath);

        bool contains(const string &_query);

        void addString(const string &_newString);

    private:
        class TrieNode;

        void iterativeStep(const char *_data, size_t _size);

        class TrieNode {
        public:
            explicit TrieNode();

            void print();

            void save(ofstream &_fileOut);

            TrieNode *getSon(int _keyValue) const;

            void addSon(int _charVal);

            bool isEndOfStr() const { return this->m_sons.empty(); }

        private:
            std::map<int, unique_ptr<TrieNode >> m_sons;
        };

        std::unique_ptr<TrieNode> m_head;
    };
}