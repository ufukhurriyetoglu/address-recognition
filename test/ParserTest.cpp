#include "catch.hpp"
#include "Parser.hpp"
#include "Tokenizer.hpp"

using address_recognition::Parser;
using address_recognition::Tokenizer;

TEST_CASE("Parser.BasicRead", "[Parser]") {
    Tokenizer t("../../test/data/sampleTestInput.txt");
    Parser p(t);

    p.addTriePaths({"../../data/tries/zip/CZ.trie"});
    p.loadTries();

    REQUIRE(p.isValid());
    p.run();

    REQUIRE(p.getTokens().size() == 352);
}

TEST_CASE("Parser.TokenizerInvalid", "[Parser]") {
    Tokenizer t("../../data/extracted/zip/.txt");
    Parser p(t);
    p.addTriePaths({"../../data/tries/CZ.trie",
                    "../../data/tries/DE.trie",
                    "../../data/tries/FR.trie"});
    p.loadTries();
    REQUIRE(!p.isValid());
}

TEST_CASE("Parser.TriePathsInvalid", "[Parser]") {
    Tokenizer t("../../data/extracted/zip/.txt");
    Parser p(t);
    p.addTriePaths({"../../data/tries/.trie",
                    "../../data/tries/DE.trie",
                    "../../data/tries/FR.trie"});
    p.loadTries();
    REQUIRE(!p.isValid());
}