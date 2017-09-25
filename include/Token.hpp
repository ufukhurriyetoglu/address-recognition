#pragma once

#include "reference.hpp"

namespace address_recognition {
    class Token {
    public:
        Token();

        Token(const string &_value);

        bool isZIP() const;

        string getValue() const { return this->m_value; }

    private:
        string m_value;
    };
}