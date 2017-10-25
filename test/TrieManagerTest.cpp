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

TEST_CASE("TrieManagerTest.LoadTriesFromFile", "[TrieManager]") {
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
    REQUIRE(mgr.isTokenIn("Krhanice"));
    REQUIRE(mgr.getLastError().empty());

    remove(paths.begin()->second);
}
