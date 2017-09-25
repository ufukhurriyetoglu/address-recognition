#pragma once

#include "reference.hpp"
#include <enums.hpp>

namespace address_recognition {
    class Token {
        typedef address_recognition::enums::TOKEN_TYPE TOKEN_TYPE;
    public:
        Token();

        Token(const string &_value);

        TOKEN_TYPE getTokeType() const { return this->m_type; }

        string getValue() const { return this->m_value; }

    private:
        string m_value;
        TOKEN_TYPE m_type;

        bool isZIP() const;

        bool isComma() const;

        bool capitalAtBeginning() const;

        bool isNumber() const;
    };
}