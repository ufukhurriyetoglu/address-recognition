#include "TrieManager.hpp"
#include "Tokenizer.hpp"
#include "Trie.hpp"

using address_recognition::TrieManager;
using boost::chrono::high_resolution_clock;
using boost::chrono::duration_cast;
using boost::chrono::milliseconds;
using boost::chrono::nanoseconds;

void TrieManager::createTrie(const string &_inPath, const string &_outPath) {
    std::cout << "creating: " << _outPath << " from " << _inPath << std::endl;

    Tokenizer tok(_inPath);
    if (!tok.isValid()) {
        std::cerr << "unable to load file: " << _inPath << std::endl;
        return;
    }

    Trie t;

    high_resolution_clock::time_point start = high_resolution_clock::now();
    tok.getNexToken(" \n", [&t](const string &_token) {
        t.addString(_token);
    });
    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "parsing took: " << duration << "ms" << std::endl;
}

void TrieManager::createTries(const std::map<string, string> &_paths) {
    std::for_each(_paths.begin(), _paths.end(), [](std::pair<string, string> _pathPair) {
        createTrie(_pathPair.first, _pathPair.second);
    });
}

void TrieManager::createDefaultTries() {
    std::map<string, string> paths = {
            {"../data/extracted/zip/FR.txt", ""},
            {"../data/extracted/zip/CZ.txt", ""},
            {"../data/extracted/zip/DE.txt", ""}
    };
    TrieManager::createTries(paths);
}

void TrieManager::createCustomTries(const std::map<string, string> &_paths) {
    TrieManager::createTries(_paths);
}
