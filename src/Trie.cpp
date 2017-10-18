#include "Trie.hpp"
#include "Tokenizer.hpp"

#include <chrono>

using address_recognition::Trie;
using address_recognition::Tokenizer;

void Trie::TrieNode::print() {
    for (int i = 0; i < ALPHBT_SIZE; ++i) {
        if (this->m_sons[i] != nullptr) {
            std::cout << (char) handleIndex(i) << "";
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

long Trie::handleIndex(long _in, bool _normalize) {
    if (_normalize) {
        if (_in >= '0' && _in <= '9') {
            return _in - '0';
        } else if (_in >= 'a' && _in <= 'a') {
            return _in - 'a' + CPHR_SIZE;
        } else if (_in >= 'A' && _in <= 'Z') {
            return _in - 'A' + CPHR_SIZE + LWR_C_SIZE;
        } else {
            throw string("Character: " + std::to_string(_in) + " is not supported!");
        }
    } else {
        if (_in >= 0 && _in < CPHR_SIZE) {
            return _in + '0';
        } else if (_in >= CPHR_SIZE && _in < LWR_C_SIZE + CPHR_SIZE) {
            return _in + 'a' - CPHR_SIZE;
        } else if (_in >= LWR_C_SIZE && _in < UPPR_C_SIZE + LWR_C_SIZE + CPHR_SIZE) {
            return _in + 'A' - CPHR_SIZE - LWR_C_SIZE;
        } else {
            throw string("Character: " + std::to_string(_in) + " is not supported!");
        }
    }
}

void Trie::print() {
    this->m_head->print();
}

bool Trie::contains(const string &_query) {
    TrieNode *curr = this->m_head.get();
    for (int i = 0; i < _query.size(); ++i) {
        long letIdx = handleIndex(_query[i], true);
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
        long letIdx = handleIndex(_newString[i]);
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
