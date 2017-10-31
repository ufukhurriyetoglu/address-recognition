#pragma once

#include "reference.hpp"
#include "Token.hpp"

using address_recognition::Token;

namespace address_recognition {
    class Tokenizer {
    public:
        explicit Tokenizer(const string &_fileName);

        ~Tokenizer();

        void getNexToken(const std::function<void(const string &_token)> &_callback);

        void getNexToken(const string &_separators, const std::function<void(const string &_token)> &_callback);

        bool isValid() const { return this->m_valid; }

    private:
        string m_fileName;
        mapped_file_source m_inputFile;
        boost::iostreams::stream<mapped_file_source> m_is;
        string m_separators = " ;\n\r";
        bool m_valid = false;
    };
}