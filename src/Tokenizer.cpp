#include "Tokenizer.hpp"

#include <boost/algorithm/string.hpp>

using address_recognition::Tokenizer;
using address_recognition::Token;

Tokenizer::Tokenizer(const string &_fileName) {
    this->m_fileName = _fileName;

    try {
        this->m_inputFile.open(this->m_fileName, std::ios::binary);
    } catch (std::exception &ex) {
        logError(__FILE__, __LINE__, "Tokenizer failed to load: " + _fileName);
    }

    this->m_valid = this->m_inputFile.is_open();
}

void Tokenizer::getNexToken(const std::function<void(const wstring &_token)> &_callback) {
    getNexToken(this->m_separators, _callback);
}

void Tokenizer::getNexToken(const wstring &_separators, const std::function<void(const wstring &_token)> &_callback) {
    if (!this->m_valid) {
        logError(__FILE__, __LINE__, "unable to open: " + this->m_fileName);
        return;
    }

    static wstring wline;
    wline.reserve(512);
    static vector<std::pair<wstring::const_iterator, wstring::const_iterator> > tokens;

    while (std::getline(this->m_inputFile, wline)) {
        boost::split(tokens, wline, boost::is_any_of(_separators.c_str()));
        for (const auto &elem : tokens) {
            if (elem.first != elem.second) {
                _callback(wstring(elem.first, elem.second));
            }
        }
    }

}

