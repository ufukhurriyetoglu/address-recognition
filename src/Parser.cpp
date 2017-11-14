#include "Parser.hpp"

using address_recognition::Parser;
using address_recognition::enums::TOKEN_TYPE;

Parser::Parser(Tokenizer &_tokenizer) :
        m_tokenizer(_tokenizer) {
}

void Parser::run() {
    vector<int> consecutiveMatches;
    int counter = 0;

    this->m_tokenizer.getNexToken([&](const wstring &_token) {
        this->m_tokens.push_back(_token);
        if (this->m_trieMgr.isTokenIn(_token)) {
            if (_token.size() > 2) {
                counter++;
                std::wcout << L"found match: " << _token << std::endl;
            }
        } else {
            if (counter > 0) {
                consecutiveMatches.push_back(counter);
                counter = 0;
            }
        }
    });

    for (auto elem:consecutiveMatches) {
        std::cout << "found: " << elem << " in a row" << std::endl;
    }
}

void Parser::addTriePath(const string &_path) {
    this->m_triePaths.push_back(_path);
}

void Parser::addTriePath(const vector<string> &_paths) {
    for (const auto &elem:_paths) {
        this->m_triePaths.push_back(elem);
    }
}

void Parser::loadTries() {
    bool status = true;
    auto errorHandler = [&status]() {
        logError(__FILE__, __LINE__, L"error loading tries");
        status = false;
    };
    this->m_trieMgr.loadTriesFromFiles(this->m_triePaths, errorHandler);
    this->m_valid = status;
}
