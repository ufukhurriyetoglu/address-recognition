#include <iostream>

#include "Tokenizer.hpp"

using address_recognition::Tokenizer;
using address_recognition::Token;

Tokenizer::Tokenizer(const string &_fileName) {
    this->m_fileName = _fileName;
    m_inputFile.open(this->m_fileName.c_str());
}

int Tokenizer::parseFile() {
    std::cout << "reading : " << this->m_fileName << std::endl;

    if (!m_inputFile.is_open()) {
        std::cerr << "unable to open: " << this->m_fileName << std::endl;
        return 1;
    }

    string token = this->readNext();
    while (!token.empty()) {
        this->m_tokens.push_back(Token(token));
        token = this->readNext();
    }

    return 0;
}

string Tokenizer::readNext() {
    string token;
    char c;
    while (this->m_inputFile.get(c)) {
        if (c != ' ' &&
            c != ';' &&
            c != '\n' &&
            c != ',' &&
            c != ':' &&
            c != EOF) {
            token += c;
        } else {
            return token;
        }
    }
    return token;
}
