#pragma once

#include <string>
#include <iostream>

using std::string;
using std::wstring;

namespace address_recognition {
    namespace logging {
        void logError(const char *_file, int _line, const wstring &_message);

        void logError(const char *_file, int _line, const string &_message);
    }
}
