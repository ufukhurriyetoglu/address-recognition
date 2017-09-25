#include <iostream>

#include "Tokenizer.hpp"

using address_recognition::Tokenizer;
using address_recognition::Token;

Tokenizer::Tokenizer(const string &_fileName) {
    this->m_fileName = _fileName;
    m_inputFile.open(this->m_fileName.c_str());
}

void Tokenizer::getNexToken(std::function<void(const Token &_token)> _callback) {
    if (!m_inputFile.is_open()) {
        std::cerr << "unable to open: " << this->m_fileName << std::endl;
        return;
    }

    auto handleToken = [&](string &_data) {
        if (!_data.empty() && _callback != nullptr) {
            _callback(Token(_data));
        }
        _data.clear();
    };

    auto isSeparator = [&](char c) -> bool {
        return (c == ' ' ||
                c == '\n');
    };

    string input;
    char c;
    while (this->m_inputFile.get(c)) {
        if (isSeparator(c)) {
            handleToken(input);
        } else {
            input += c;
        }
    }
    handleToken(input);
}
