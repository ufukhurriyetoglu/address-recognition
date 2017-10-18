#include <iostream>

#include "Tokenizer.hpp"

using address_recognition::Tokenizer;
using address_recognition::Token;

Tokenizer::Tokenizer(const string &_fileName) {
    this->m_fileName = _fileName;

    try {
        this->m_inputFile.open(this->m_fileName);
        this->m_is.open(this->m_inputFile, std::ios::in);
    } catch (std::exception &ex) {}

    this->m_valid = this->m_is.is_open();
}

void Tokenizer::getNexToken(const std::function<void(const Token &_token)> &_callback) {
    getNexToken(_callback, this->m_separators);
}

void Tokenizer::getNexToken(const std::function<void(const Token &_token)> &_callback, const string &_separators) {
    if (!this->m_valid) {
        std::cerr << "unable to open: " << this->m_fileName << std::endl;
        return;
    }

    string line;
    boost::char_separator<char> sep{_separators.c_str(), "", boost::drop_empty_tokens};
    while (std::getline(this->m_is, line)) {
        boost::tokenizer<boost::char_separator<char>> tok{line, sep};
        for (auto &elem : tok) {
            _callback(Token(elem));
        }
    }

    this->m_is.clear();
    this->m_is.seekg(0, std::ios::beg);
}
