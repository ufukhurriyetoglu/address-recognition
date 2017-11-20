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

        int addSectionFromFile(const string &_sectionName,
                               const string &_file,
                               const std::function<void()> &_callbackError);

        bool contains(const wstring &_query);

        bool containsInSection(const string &_sectionName, const wstring &_query);

        const wstring &getLastError() const { return m_lastError; }

        const std::map<string, unique_ptr<Trie>> &getTries() const { return this->m_tries; }

        bool empty() const { return this->m_tries.empty(); }

    private:
        static int createTrie(const string &_inPath, const string &_outPath);

        std::map<string, unique_ptr<Trie>> m_tries{};

        wstring m_lastError;
    };
}