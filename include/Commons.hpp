#pragma once

#include <string>
#include <iostream>

using std::string;

namespace address_recognition {
    namespace logging {
        void logError(const char *_file, int _line, const string &_message);
    }
}
