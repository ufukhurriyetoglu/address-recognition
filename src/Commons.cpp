#include "Commons.hpp"

void address_recognition::logging::logError(const char *_file, int _line, const wstring &_message) {
    string tmp(_file);
    std::wcerr << L"[" << wstring(tmp.begin(), tmp.end()) << L":" << _line << L"] error -> "
               << _message
               << std::endl;
}

void ::address_recognition::logging::logError(const char *_file, int _line, const string &_message) {
    std::cerr << "[" << _file << ":" << _line << "] error -> "
               << _message
               << std::endl;
}
