#include "Parser.hpp"

using address_recognition::Parser;
using address_recognition::enums::TOKEN_TYPE;

Parser::Parser(Tokenizer &_tokenizer) :
        m_tokenizer(_tokenizer) {
}

void Parser::run() {
    this->m_tokenizer.getNexToken([&](const string &_token) {
        this->m_tokens.push_back(_token);
    });
}
