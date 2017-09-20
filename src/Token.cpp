#include "Token.hpp"

using address_recognition::Token;

Token::Token(const string &_value) {
    this->m_value = _value;
}

bool Token::isZIP() {
    std::regex digit3zip("(^[0-9]{3}$)");
    std::regex digit4zip("(^[0-9]{4}$)");
    std::regex digit5zip("(^[0-9]{5}$)");
    std::regex digit6zip("(^[0-9]{6}$)");
    return (std::regex_match(this->m_value, digit3zip) ||
            std::regex_match(this->m_value, digit4zip) ||
            std::regex_match(this->m_value, digit5zip) ||
            std::regex_match(this->m_value, digit6zip));
}