#include "catch.hpp"
#include "Trie.hpp"

using address_recognition::Trie;

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
//
//TEST_CASE("TrieTest.none-load", "[Trie][load][none]") {
//    Trie t;
//    REQUIRE(t.loadTrie("none") == 1);
//}
//
//TEST_CASE("TrieTest.cz-zip-trie-create", "[Trie][create][CZ][zip]") {
//    Trie t;
//    t.setOutFilePath("cz-zip-trie");
//
//    auto res = t.addToTrie("../../data/extracted/zip/CZ.txt");
//    REQUIRE(res == 0);
//
//    t.saveTrie();
//}
//
//TEST_CASE("TrieTest.cz-zip-trie-load", "[Trie][load][CZ][zip]") {
//    Trie t;
//    t.loadTrie("cz-zip-trie");
//
//    REQUIRE(t.getSet().size() > 1000);
//}