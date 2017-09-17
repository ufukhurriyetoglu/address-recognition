#pragma once

#include "reference.hpp"

namespace address_recognition{
    class Token{
    public:
        Token(const string &_value);

    private:
        string m_value;
    };
}