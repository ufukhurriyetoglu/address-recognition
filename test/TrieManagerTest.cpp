#include "catch.hpp"
#include <boost/filesystem.hpp>

#include "TrieManager.hpp"

using address_recognition::TrieManager;

using boost::filesystem::exists;
using boost::filesystem::remove;

TEST_CASE("TrieManagerTest.InvalidFiles", "[TrieManager]") {
    bool error = false;
    int errNo = -1;
    auto errorHandler = [&error, &errNo](int _errNo) {
        error = true;
        errNo = _errNo;
    };

    std::map<string, string> paths = {
            {"../../test/data/sampleTestInput.txt", ""}
    };

    TrieManager::createTries(paths, errorHandler);
    REQUIRE(error);
    REQUIRE(errNo == 3);

    error = false;
    paths = {
            {"", "foo"}
    };

    TrieManager::createTries(paths, errorHandler);
    REQUIRE(error);
    REQUIRE(errNo == 1);
}

TEST_CASE("TrieManagerTest.AlreadyExisting", "[TrieManager]") {
    std::map<string, string> paths = {
            {"../../test/data/sampleTestInput.txt", "../../output/test/tries/sampleTrie"}
    };

    bool error = false;
    int errNo = -1;
    auto errorHandler = [&error, &errNo](int _errNo) {
        error = true;
        errNo = _errNo;
    };

    TrieManager::createTries(paths, errorHandler);
    REQUIRE(!error);
    REQUIRE(errNo == -1);

    error = false;

    TrieManager::createTries(paths, errorHandler);
    REQUIRE(error);
    REQUIRE(errNo == 2);

    remove(paths.begin()->second);
}

TEST_CASE("TrieManager.Create and Load one trie", "[TrieManager]") {
    std::map<string, string> paths = {
            {"../../test/data/sampleTestInput.txt", "../../output/test/tries/sampleTrie"}
    };

    bool error = false;
    auto errHandler = [&error](int _errNo) {
        error = true;
    };

    TrieManager::createTries(paths, errHandler);
    REQUIRE(!error);

    error = false;
    auto errHandler2 = [&error]() {
        error = true;
    };

    TrieManager mgr;
    mgr.loadTriesFromFiles({paths.begin()->second}, errHandler2);

    REQUIRE(!error);
    REQUIRE(mgr.getTries().size() == 1);
    REQUIRE(mgr.isTokenIn(L"Krhanice"));
    REQUIRE(mgr.getLastError().empty());

    remove(paths.begin()->second);
}

TEST_CASE("TrieManager.Load one invalid trie", "[TrieManager]") {
    std::map<string, string> paths = {
            {"../../test/data/nonExistingFile.txt", "../../output/test/tries/nonExistingFile"}
    };

    bool error = false;
    auto errHandler = [&error]() {
        error = true;
    };

    TrieManager mgr;
    mgr.loadTriesFromFiles({paths.begin()->second}, errHandler);
    REQUIRE(error);
    REQUIRE(mgr.getTries().size() == 0);
    REQUIRE(!mgr.isTokenIn(L"Krhanice"));
    REQUIRE(!mgr.getLastError().empty());
}

TEST_CASE("TrieManager.Create and Load more tries", "[TrieManager]") {
    std::map<string, string> paths = {
            {"../../test/data/dummyTestInput.txt",  "../../output/test/tries/dummyTestTrie"},
            {"../../test/data/sampleTestInput.txt", "../../output/test/tries/sampleTestTrie"},
            {"../../test/data/mtpleTestInput.txt",  "../../output/test/tries/mtpleTestTrie"}
    };

    bool error = false;
    auto errHandler = [&error](int _errNo) {
        error = true;
    };

    TrieManager::createTries(paths, errHandler);
    REQUIRE(!error);

    int numErrors = 0;
    auto errHandler2 = [&error, &numErrors]() {
        error = true;
        numErrors++;
    };

    error = false;
    TrieManager mgr;

    vector<string> triePaths;
    for (auto it = paths.begin(); it != paths.end(); it++) {
        triePaths.push_back(it->second);
    }
    mgr.loadTriesFromFiles(triePaths, errHandler2);

    REQUIRE(!error);
    REQUIRE(numErrors == 0);
    REQUIRE(mgr.getTries().size() == 3);
    REQUIRE(mgr.isTokenIn(L"Krhanice"));
    REQUIRE(mgr.isTokenIn(L"bar"));
    REQUIRE(mgr.isTokenIn(L"mtple"));
    REQUIRE(mgr.getLastError().empty());

    for (const auto &path:triePaths) {
        remove(path);
    }
}

TEST_CASE("TrieManager.Load more invalid tries", "[TrieManager]") {
    std::map<string, string> paths = {
            {"../../test/data/dummyTestInput.txt", "../../output/test/tries/dummyTestTrie"},
            {"../../test/data/nonsense.txt",       "../../output/test/tries/sampleTestTrie"},
            {"../../test/data/nonsense2.txt",      "../../output/test/tries/mtpleTestTrie"}
    };

    int numErrors = 0;
    bool error = false;

    auto errHandler = [&error, &numErrors](int _errNo) {
        error = true;
        numErrors++;
    };

    TrieManager::createTries(paths, errHandler);
    REQUIRE(error);
    REQUIRE(numErrors == 2);

    vector<string> triePaths;
    for (auto it = paths.begin(); it != paths.end(); it++) {
        triePaths.push_back(it->second);
    }

    numErrors = 0;
    error = false;
    auto errHandler2 = [&error, &numErrors]() {
        error = true;
        numErrors++;
    };

    TrieManager mgr;
    mgr.loadTriesFromFiles(triePaths, errHandler2);

    REQUIRE(error);
    REQUIRE(numErrors == 2);
    REQUIRE(mgr.getTries().size() == 1);
    REQUIRE(!mgr.getLastError().empty());

    for (const auto &path:triePaths) {
        remove(path);
    }
}


