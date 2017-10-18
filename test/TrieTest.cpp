#include "catch.hpp"
#include "Trie.hpp"
#include "Tokenizer.hpp"

using address_recognition::Trie;
using address_recognition::Token;
using address_recognition::Tokenizer;

TEST_CASE("TrieTest.empty", "[Trie][generate][empty]") {
    Trie t;
    t.addString("foo");
    t.addString("fooz");
    t.addString("foob");
    t.addString("foobar");
    t.addString("foobaz");
    t.addString("bar");
    t.addString("baz");
    t.print();

    REQUIRE(t.contains("foo"));
}

TEST_CASE("TrieTest.none-load", "[Trie][load][none]") {
    Trie t;
    bool callbackCalled = false;

    auto addString = [&](const Token &_token) {
        callbackCalled = true;
        t.addString(_token.getValue());
    };

    Tokenizer tok("");
    tok.getNexToken(addString);

    REQUIRE(!tok.isValid());
    REQUIRE(!callbackCalled);
}

TEST_CASE("TrieTest.cz-zip-trie-create", "[Trie][create][CZ][zip]") {
    Trie t;
    bool callbackCalled = false;

    auto addString = [&](const Token &_token) {
        callbackCalled = true;
//        t.addString(_token.getValue());
    };

    Tokenizer tok("../../data/extracted/zip/CZ.txt");
    REQUIRE(tok.isValid());

    tok.getNexToken(addString, " #\n");
    REQUIRE(callbackCalled);

//    t.setOutFilePath("cz-zip-trie");
//    REQUIRE(res == 0);
//    t.saveTrie();
}
//
//TEST_CASE("TrieTest.cz-zip-trie-load", "[Trie][load][CZ][zip]") {
//    Trie t;
//    t.loadTrie("cz-zip-trie");
//
//    REQUIRE(t.getSet().size() > 1000);
//}