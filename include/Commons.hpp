#pragma once

#include <string>
#include <iostream>

using std::string;
using std::wstring;



namespace address_recognition {
    namespace logging {
        template<typename T>
        void logInfo(T v) {
            std::wcout << v << L" ";
        }

        template<typename T, typename... Args>
        void logInfo(T first, Args... args) {
            logInfo(first);
            logInfo(args...);
        }

        template<typename T, typename... Args>
        void logInfoLn(T first, Args... args) {
            logInfo(first);
            logInfo(args...);
            logInfo<const wstring &>(L"\n");
        }

        void logError(const char *_file, int _line, const wstring &_message);

        void logError(const char *_file, int _line, const string &_message);
    }
}
