#include "Tokenizer.hpp"

#include <iostream>
#include <boost/algorithm/string.hpp>

using address_recognition::Tokenizer;
using address_recognition::Token;

Tokenizer::Tokenizer(const string &_fileName) {
    this->m_fileName = _fileName;

    try {
        this->m_inputFile.open(this->m_fileName);
        this->m_is.open(this->m_inputFile, std::ios::in);
    } catch (std::exception &ex) {
        logError(__FILE__, __LINE__, "Tokenizer failed to load: " + _fileName);
    }

    this->m_valid = this->m_is.is_open();
}

void Tokenizer::getNexToken(const std::function<void(const string &_token)> &_callback) {
    getNexToken(this->m_separators, _callback);
}

void Tokenizer::getNexToken(const string &_separators, const std::function<void(const string &_token)> &_callback) {
    if (!this->m_valid) {
        logError(__FILE__, __LINE__, "unable to open: " + this->m_fileName);
        return;
    }

    static string line;
    line.reserve(512);
    static vector<std::pair<string::const_iterator, string::const_iterator> > tokens;
    while (std::getline(this->m_is, line)) {
        boost::split(tokens, line, boost::is_any_of(_separators.c_str()));
        for (const auto &elem : tokens) {
            if (elem.first != elem.second) {
                _callback(string(elem.first, elem.second));
            }
        }
    }

    this->m_is.clear();
    this->m_is.seekg(0, std::ios::beg);
}

Tokenizer::~Tokenizer() {
//    this->m_is.close();
//    this->m_inputFile.close();
}
