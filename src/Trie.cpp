#include "Trie.hpp"
#include "Tokenizer.hpp"

#include <chrono>

using address_recognition::Trie;
using address_recognition::Tokenizer;

void Trie::TrieNode::print() {
    for (int i = 0; i < ENG_LET; ++i) {
        if (this->m_sons[i] != nullptr) {
            std::cout << (char) ('a' + i) << "";
            this->m_sons[i]->print();
        }
    }
    std::cout << "#";
}

Trie::TrieNode::TrieNode() {
    this->m_isEndOfStr = false;
}

Trie::TrieNode *Trie::TrieNode::getSon(long _idx) const {
    return this->m_sons[_idx].get();
}

void Trie::TrieNode::addSon(long _idx) {
    this->m_sons[_idx] = std::make_unique<TrieNode>();
}

void Trie::print() {
    this->m_head->print();
}

bool Trie::contains(const string &_query) {
    TrieNode *curr = this->m_head.get();
    for (int i = 0; i < _query.size(); ++i) {
        long letIdx = _query[i] - 'a';
        auto son = curr->getSon(letIdx);
        if (son == nullptr) {
            return false;
        }
        curr = son;
    }

    return curr->isEndOfStr();
}

void Trie::addString(const string &_newString) {
    if (this->contains(_newString)) {
        return;
    }
    TrieNode *curr = this->m_head.get();
    for (int i = 0; i < _newString.size(); ++i) {
        long letIdx = _newString[i] - 'a';
        auto son = curr->getSon(letIdx);
        if (son == nullptr) {
            curr->addSon(letIdx);
        }
        curr = curr->getSon(letIdx);
    }
    curr->isEndOfStr() = true;
}

Trie::Trie() {
    this->m_head = std::make_unique<TrieNode>();
}
