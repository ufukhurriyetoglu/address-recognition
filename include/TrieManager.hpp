#pragma once

#include "Trie.hpp"
#include "reference.hpp"

namespace address_recognition {
    class TrieManager {
        typedef address_recognition::Trie Trie;

    public:
        static void createTries(
                const std::map<string, string> &_paths,
                const std::function<void(int _errNo)> &_callbackError);

        int loadTriesFromFiles(const vector<string> &_files,
                               const std::function<void()> &_callbackError);

        bool isTokenIn(const string &_query);

        const string &getLastError() const { return m_lastError; }

        const vector<unique_ptr<Trie>> &getTries() const { return this->m_tries; }

        bool empty() const { return this->m_tries.empty(); }

    private:
        static int createTrie(const string &_inPath, const string &_outPath);

        vector<unique_ptr<Trie>> m_tries;

        string m_lastError;
    };
}