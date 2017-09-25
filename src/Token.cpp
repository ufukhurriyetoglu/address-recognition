#include "Token.hpp"

using address_recognition::Token;
using address_recognition::enums::TOKEN_TYPE;

Token::Token() {}

Token::Token(const string &_value) {
    this->m_value = _value;
    this->m_type = TOKEN_TYPE::NONE;

    if (this->isZIP()) {
        this->m_type = TOKEN_TYPE::ZIP;
        return;
    }
    if (this->isComma()) {
        this->m_type = TOKEN_TYPE::COMMA;
        return;
    }
    if (this->capitalAtBeginning()) {
        this->m_type = TOKEN_TYPE::CAPITAL_AT_BEG;
        return;
    }
    if (this->isNumber()) {
        this->m_type = TOKEN_TYPE::NUMBER;
        return;
    }
}

bool Token::isZIP() const {
    auto isXDigitZip = [&](int x) -> bool {
        std::regex xDigitZip("(^[0-9]{" + std::to_string(x) + "}$)");
        return std::regex_match(this->m_value, xDigitZip);
    };

    return (isXDigitZip(4) ||
            isXDigitZip(5) ||
            isXDigitZip(6));
}

bool Token::isComma() const {
    return (this->m_value.compare(",") == 0);
}

bool Token::capitalAtBeginning() const {
    std::regex re("(^[A-Z].*)");
    return std::regex_match(this->m_value, re);
}

bool Token::isNumber() const {
    std::regex re("(^[0-9]+$)");
    return std::regex_match(this->m_value, re);
}
