#include "TrieManager.hpp"
#include "Tokenizer.hpp"

using address_recognition::TrieManager;
using address_recognition::Trie;

using boost::chrono::high_resolution_clock;
using boost::chrono::duration_cast;
using boost::chrono::milliseconds;
using boost::chrono::nanoseconds;


int TrieManager::createTrie(const string &_inPath, const string &_outPath) {
    std::cout << "creating: " << _outPath << " from " << _inPath << std::endl;

    Tokenizer tok(_inPath);
    if (!tok.isValid()) {
        logError(__FILE__, __LINE__, "Unable to load file: " + _inPath);
        return 1;
    }

    if (ifstream(_outPath).good()) {
        logError(__FILE__, __LINE__, "Already exists: " + _outPath);
        return 2;
    }

    Trie t;

    high_resolution_clock::time_point start = high_resolution_clock::now();
    tok.getNexToken(" \n", [&t](const string &_token) {
        t.addString(_token);
    });
    high_resolution_clock::time_point end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    std::cout << "parsing took: " << duration << "ms" << std::endl;

    int res = t.save(_outPath);
    if (res != 0) {
        logError(__FILE__, __LINE__, "failed saving '" + _outPath + "'");
        return 3;
    }
    return 0;
}

void TrieManager::createTries(const std::map<string, string> &_paths,
                              const std::function<void(int _errNo)> &_callbackError) {
    std::for_each(_paths.begin(),
                  _paths.end(),
                  [&_callbackError](const std::pair<string, string> _pathPair) {
                      auto res = createTrie(_pathPair.first, _pathPair.second);
                      if (res != 0) {
                          _callbackError(res);
                      }
                  });
}

int TrieManager::loadTriesFromFiles(const vector<string> &_files,
                                    const std::function<void()> &_callbackError) {
    std::for_each(_files.begin(), _files.end(), [&](const string &_path) {
        auto trie = std::make_unique<Trie>();
        auto res = trie->load(_path);
        if (res == 0) {
            this->m_tries.push_back(std::move(trie));
        } else {
            _callbackError();
            this->m_lastError = "unable to load: " + _path;
            logError(__FILE__, __LINE__, this->getLastError());
        }
    });
    return 0;
}

bool TrieManager::isTokenIn(const string &_query) {
    for (const auto &elem:this->m_tries) {
        if (elem->contains(_query)) {
            return true;
        }
    }
    return false;
}
