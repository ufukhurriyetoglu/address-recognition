#include <iostream>


#include "Tokenizer.hpp"

using address_recognition::Tokenizer;
using address_recognition::Token;

Tokenizer::Tokenizer(const string &_fileName) {
    this->m_fileName = _fileName;
    m_inputFile.open(this->m_fileName.c_str());
}

int Tokenizer::parseFile() {
    if (!m_inputFile.is_open()) {
        std::cerr << "unable to open: " << this->m_fileName << std::endl;
        return 1;
    }

    auto handleToken = [&](string &_token) {
        if (!_token.empty()) {
            this->m_tokens.push_back(Token(_token));
            if (this->m_tokens.back().isZIP()) {
                this->m_possibleZIPs.push_back(this->m_tokens.size() - 1);
            }
            _token.clear();
        }
    };

    auto isSeparator = [&](char c) -> bool {
        return (c == ' ' ||
                c == '\n' ||
                c == ',');
    };

    string token;
    char c;
    while (this->m_inputFile.get(c)) {
        if (isSeparator(c)) {
            handleToken(token);
        } else {
            token += c;
        }
    }
    handleToken(token);

    return 0;
}
