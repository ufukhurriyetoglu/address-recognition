#include "catch.hpp"
#include "Parser.hpp"
#include "Tokenizer.hpp"

using address_recognition::Parser;
using address_recognition::Tokenizer;

TEST_CASE("Parser.BasicRead", "[Parser]") {
    Tokenizer t("../../test/data/sampleTestInput.txt");
    Parser p(t);

    p.addSection("zip", "CZ", {"../../data/tries/zip/CZ.trie"});

    REQUIRE(p.isValid());
    vector<wstring> tokens;
    p.run([&](const wstring &_token) {
        if (p.contains(_token)) {
            tokens.push_back(_token);
        }
    });

    REQUIRE(tokens.size() == 352);
}

TEST_CASE("Parser.TokenizerInvalid", "[Parser]") {
    Tokenizer t("../../data/extracted/zip/.txt");
    Parser p(t);
    p.addSection("tries", "CZ", {"../../data/tries/CZ.trie"});
    p.addSection("tries", "DE", {"../../data/tries/DE.trie"});
    p.addSection("triesF", "R", {"../../data/tries/FR.trie"});

    REQUIRE(!p.isValid());
}

TEST_CASE("Parser.TriePathsInvalid", "[Parser]") {
    Tokenizer t("../../data/extracted/zip/.txt");
    Parser p(t);

    p.addSection(".", "CZ", {"../../data/tries/.trie"});
    p.addSection("tries", "DE", {"../../data/tries/DE.trie"});
    p.addSection("tries", "FR", {"../../data/tries/FR.trie"});

    REQUIRE(!p.isValid());
}

TEST_CASE("Parser.Section", "[Parser]") {
    Tokenizer t("../../data/extracted/zip/CZ.txt");
    Parser p(t);

    p.addSection("zip", "CZ", {"../../data/tries/zip/CZ.trie"});
    p.addSection("zip", "DE", {"../../data/tries/zip/DE.trie"});

    REQUIRE(p.contains(L"68707"));
    REQUIRE(p.contains(L"01169"));

    REQUIRE(p.isValid());
}

TEST_CASE("Parser.DuplicateSection", "[Parser]") {
    Tokenizer t("../../data/extracted/zip/CZ.txt");
    Parser p(t);

    p.addSection("zip", "CZ", {"../../data/tries/zip/CZ.trie"});
    p.addSection("zip", "CZ", {"../../data/tries/zip/DE.trie"});

    REQUIRE(p.contains(L"68707"));
    REQUIRE(!p.contains(L"01169"));
}
