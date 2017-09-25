#include "Parser.hpp"

using address_recognition::Parser;

Parser::Parser(Tokenizer &_tokenizer) :
        m_tokenizer(_tokenizer) {
}

void Parser::run() {
    this->m_tokenizer.getNexToken([&](const Token &_token){
        std::cout << "found: " << _token.getValue() << std::endl;
        this->m_tokens.push_back(_token);
        if(_token.isZIP()){
            this->m_possibleZip.push_back(_token);
        }
    });
}
