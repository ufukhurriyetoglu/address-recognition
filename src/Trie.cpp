#include "Trie.hpp"
#include "Tokenizer.hpp"

#include <chrono>

using address_recognition::Trie;
using address_recognition::Tokenizer;

size_t lineLen = 0;
const size_t lineMax = 140;

void Trie::TrieNode::print(bool _formatted) {
    for (const auto &elem : this->m_sons) {
        std::wcout << elem.first;
        if (elem.second->isLast()) {
            std::wcout << '*';
        }
        elem.second->print(_formatted);
    }
    std::wcout << '#';
    if (_formatted) {
        if (lineLen >= lineMax) {
            lineLen = 0;
            std::wcout << '\n';
        } else {
            lineLen++;
        }
    }
}

Trie::TrieNode *Trie::TrieNode::getSon(wchar_t _keyValue) const {
    auto it = this->m_sons.find(_keyValue);
    if (it == this->m_sons.end()) {
        return nullptr;
    } else {
        return it->second.get();
    }
}

void Trie::TrieNode::addSon(wchar_t _charVal) {
    this->m_sons.insert(std::make_pair(_charVal, std::make_unique<TrieNode>()));
}

void Trie::TrieNode::save(wofstream &_fileOut) {
    for (const auto &elem : this->m_sons) {
        _fileOut << elem.first;
        if (elem.second->isLast()) {
            _fileOut << '*';
        }
        elem.second->save(_fileOut);
    }
    _fileOut << '#';
}

void Trie::print(bool _formatted) {
    this->m_head->print(_formatted);
}

bool Trie::contains(const wstring &_query) {
    TrieNode *curr = this->m_head.get();
    for (int i = 0; i < _query.size(); ++i) {
        auto son = curr->getSon(_query[i]);
        if (son == nullptr) {
            return false;
        }
        curr = son;
    }

    return curr->isLast();
}

void Trie::addString(const wstring &_newString) {
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
    curr->setIsLast(true);
}

Trie::Trie() {
    this->m_head = std::make_unique<TrieNode>();
}

int Trie::save(const string &_filePath) {
    try {
        wofstream fileOut(_filePath, std::ios::binary);
        if (!fileOut.is_open()) {
            logError(__FILE__, __LINE__,
                     "Unable to open: '" + _filePath + "' to save "
                             "trie");
            return 1;
        }
        this->m_head->save(fileOut);
    } catch (std::exception &ex) {
        return 1;
    }
}

int Trie::load(const string &_filePath) {
    wifstream inputFile;
    try {
        inputFile.open(_filePath, std::ios::binary);
    } catch (std::exception &ex) {
        return 1;
    }

    if (!inputFile.is_open()) {
        return 1;
    }

    std::vector<wchar_t> fileContents((std::istreambuf_iterator<wchar_t>(inputFile)),
                                      std::istreambuf_iterator<wchar_t>());

    iterativeStep(fileContents.data(), fileContents.size());
    return 0;
}

void Trie::iterativeStep(const wchar_t *_data, size_t _size) {
    vector<TrieNode *> queue;
    queue.push_back(new TrieNode());

    size_t ctr = 0;
    while (ctr < _size) {
        wchar_t data = _data[ctr];
        if (data == '#') {
            queue.pop_back();
        } else if (data == '*') {
            queue.back()->setIsLast(true);
        } else if (data != '\n') {  // TODO use isspace?
            queue.back()->addSon(data);
            queue.push_back(queue.back()->getSon(data));
        }
        ctr++;
    }

    this->m_head.reset(queue[0]);
}
