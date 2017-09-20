#pragma once

#include "reference.hpp"

namespace address_recognition{
    class Token{
    public:
        Token(const string &_value);

        bool isZIP();

    private:
        string m_value;
    };
}