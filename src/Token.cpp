#include "Token.hpp"

using address_recognition::Token;

Token::Token() {}

Token::Token(const string &_value) {
    this->m_value = _value;
}

bool Token::isZIP() const {
    auto isXDigitZip = [&](int x) -> bool {
        std::regex xDigitZip("(^[0-9]{" + std::to_string(x) + "}$)");
        return std::regex_match(this->m_value, xDigitZip);
    };

    return (isXDigitZip(3) ||
            isXDigitZip(4) ||
            isXDigitZip(5) ||
            isXDigitZip(6));
}