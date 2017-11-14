#pragma once

#include "reference.hpp"
#include "Token.hpp"

using address_recognition::Token;

namespace address_recognition {
    class Tokenizer {
    public:
        explicit Tokenizer(const string &_fileName);

        void getNexToken(const std::function<void(const wstring &_token)> &_callback);

        void getNexToken(const wstring &_separators, const std::function<void(const wstring &_token)> &_callback);

        bool isValid() const { return this->m_valid; }

    private:
        string m_fileName;
        wifstream m_inputFile;
//        mapped_file_source m_inputFile;
//        boost::iostreams::stream<mapped_file_source> m_is;
        wstring m_separators = L" ;\n\r";
        bool m_valid = false;
    };
}