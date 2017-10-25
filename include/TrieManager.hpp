#pragma once

#include "reference.hpp"

namespace address_recognition {
    class TrieManager {
    public:
        static void createDefaultTries();

        static void createCustomTries(const std::map<string, string> &_paths);

        int loadTriesFromFiles(const vector<string> &_files);

        bool isTokenIn(const string &_query);

    private:
        static void createTrie(const string &_inPath, const string &_outPath);

        static void createTries(const std::map<string, string> &_paths);
    };
}