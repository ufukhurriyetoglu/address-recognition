#include "Commons.hpp"

void address_recognition::logging::logError(const char *_file, int _line, const string &_message) {
    std::cerr << "[" << _file << ":" << _line << "] error -> " << _message << std::endl;
}