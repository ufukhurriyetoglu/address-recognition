#include "catch.hpp"
#include "Parser.hpp"
#include "Tokenizer.hpp"

using address_recognition::Parser;
using address_recognition::Tokenizer;

TEST_CASE("Parser.BasicRead", "[Parser]") {
    Tokenizer t("../../data/extracted/zip/CZ.txt");
    Parser p(t);
    p.addTriePath({"../../data/tries/CZ.trie",
                   "../../data/tries/DE.trie",
                   "../../data/tries/FR.trie"});
    p.loadTries();
    REQUIRE(p.isValid());
    p.run();
    REQUIRE(p.getTokens().size() == 2694);
}

TEST_CASE("Parser.TokenizerInvalid", "[Parser]") {
    Tokenizer t("../../data/extracted/zip/.txt");
    Parser p(t);
    p.addTriePath({"../../data/tries/CZ.trie",
                   "../../data/tries/DE.trie",
                   "../../data/tries/FR.trie"});
    p.loadTries();
    REQUIRE(!p.isValid());
}

TEST_CASE("Parser.TriePathsInvalid", "[Parser]") {
    Tokenizer t("../../data/extracted/zip/.txt");
    Parser p(t);
    p.addTriePath({"../../data/tries/.trie",
                   "../../data/tries/DE.trie",
                   "../../data/tries/FR.trie"});
    p.loadTries();
    REQUIRE(!p.isValid());
}