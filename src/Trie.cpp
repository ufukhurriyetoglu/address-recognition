#include "Trie.hpp"
#include "Tokenizer.hpp"

#include <chrono>

using address_recognition::Trie;
using address_recognition::Tokenizer;

void Trie::TrieNode::print() {
    static size_t lineLen = 0;
    const size_t lineMax = 140;
    for (const auto &elem : this->m_sons) {
        std::cout << (char) elem.first;
        elem.second->print();
    }
    std::cout << "#";
    if (lineLen >= lineMax) {
        lineLen = 0;
        std::cout << "\n";
    } else {
        lineLen++;
    }
}

Trie::TrieNode::TrieNode() {
//    this->m_isEndOfStr = false;
}

Trie::TrieNode *Trie::TrieNode::getSon(int _keyValue) const {
    auto it = this->m_sons.find(_keyValue);
    if (it == this->m_sons.end()) {
        return nullptr;
    } else {
        return it->second.get();
    }
}

void Trie::TrieNode::addSon(int _charVal) {
    this->m_sons.insert(std::make_pair(_charVal, std::make_unique<TrieNode>()));
}

void Trie::TrieNode::save(ofstream &_fileOut) {
    static size_t lineLen = 0;
    const size_t lineMax = 140;
    for (const auto &elem : this->m_sons) {
        _fileOut << (char) elem.first;
        elem.second->save(_fileOut);
    }
    _fileOut << "#";
    if (lineLen >= lineMax) {
        lineLen = 0;
        _fileOut << "\n";
    } else {
        lineLen++;
    }
}

void Trie::print() {
    this->m_head->print();
}

bool Trie::contains(const string &_query) {
    TrieNode *curr = this->m_head.get();
    for (int i = 0; i < _query.size(); ++i) {
        auto son = curr->getSon(_query[i]);
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
        auto son = curr->getSon(_newString[i]);
        if (son == nullptr) {
            curr->addSon(_newString[i]);
        }
        curr = curr->getSon(_newString[i]);
    }
//    curr->isEndOfStr() = true;
}

Trie::Trie() {
    this->m_head = std::make_unique<TrieNode>();
}

int Trie::save(const string &_filePath) {
    ofstream fileOut(_filePath);
    if (!fileOut.is_open()) {
        logError(__FILE__, __LINE__, "Unable to open: '" + _filePath + "' to save trie");
        return 1;
    }
    this->m_head->save(fileOut);
}

int Trie::load(const string &_filePath) {
    mapped_file inputFile;

    try {
        inputFile.open(_filePath, boost::iostreams::mapped_file::readonly);
    } catch (std::exception &ex) {
        return 1;
    }

    auto data = inputFile.const_data();
    auto size = inputFile.size();
    iterativeStep(data, size);
    return 0;
}

void Trie::iterativeStep(const char *_data, size_t _size) {
    vector<TrieNode *> queue;
    queue.push_back(new TrieNode());

    size_t ctr = 0;
    while (ctr < _size) {
        char data = _data[ctr];
        if (data != '#' && data != '\n') {  // TODO use isspace?
            queue.back()->addSon(data);
            queue.push_back(queue.back()->getSon(data));
        } else {
            queue.pop_back();
        }
        ctr++;
    }

    this->m_head.reset(queue[0]);
}
