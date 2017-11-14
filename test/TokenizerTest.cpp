#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <reference.hpp>

#include "Tokenizer.hpp"

using address_recognition::Tokenizer;

TEST_CASE("Tokenizer - not existing input file", "[Tokenizer]") {
    Tokenizer t("");
    bool callbackCalled = false;
    auto callback = [&](const wstring &_token) {
        callbackCalled = true;
    };
    t.getNexToken(callback);
    REQUIRE(!callbackCalled);
    REQUIRE(!t.isValid());
}

TEST_CASE("Tokenizer - existing input file", "[Tokenizer]") {
    vector<wstring> tokens;
    auto handler = [&](const wstring &_token) {
        tokens.push_back(_token);
    };

    unique_ptr<Tokenizer> t;
    t = std::make_unique<Tokenizer>("../../test/data/dummyTestInput.txt");
    t->getNexToken(handler);
    REQUIRE(tokens.size() == 5);

    tokens.clear();
    t = std::make_unique<Tokenizer>("../../test/data/emptyTestInput.txt");
    t->getNexToken(handler);
    REQUIRE(tokens.size() == 0);

    tokens.clear();
    t = std::make_unique<Tokenizer>("../../test/data/mtpleTestInput.txt");
    t->getNexToken(handler);
    REQUIRE(tokens.size() == 3);

    tokens.clear();
    t = std::make_unique<Tokenizer>("../../test/data/nospacesTestInput.txt");
    t->getNexToken(handler);
    REQUIRE(tokens.size() == 1);
}

TEST_CASE("Tokenizer.empty_separators", "[Tokenizer]") {
    Tokenizer t("../../test/data/dummyTestInput.txt");
    REQUIRE(t.isValid());

    bool callbackCalled = false;
    unsigned numOfTokens = 0;
    auto handler = [&](const wstring &_token) {
        callbackCalled = true;
        numOfTokens++;
    };
    wstring seps;
    t.getNexToken(seps, handler);

    REQUIRE(callbackCalled);
    REQUIRE(numOfTokens == 1);
}

TEST_CASE("Tokenizer.set_separators", "[Tokenizer]") {
    Tokenizer t("../../test/data/dummyTestInput.txt");
    REQUIRE(t.isValid());

    bool callbackCalled = false;
    unsigned numOfTokens = 0;
    auto handler = [&](const wstring &_token) {
        callbackCalled = true;
        numOfTokens++;
    };

    SECTION("separators are present in file") {
        wstring seps = L" ";
        t.getNexToken(seps, handler);

        REQUIRE(callbackCalled);
        REQUIRE(numOfTokens == 5);
    }

    callbackCalled = false;
    numOfTokens = 0;

    SECTION("separators are not in file") {
        wstring seps = L"#;(";
        t.getNexToken(seps, handler);

        REQUIRE(callbackCalled);
        REQUIRE(numOfTokens == 1);
    }
}

TEST_CASE("Tokenizer.separators_mixed", "[Tokenizer]") {
    Tokenizer t("../../test/data/separatorTestInput.txt");
    REQUIRE(t.isValid());

    unsigned numOfTokens = 0;
    auto handler = [&](const wstring &_token) {
        numOfTokens++;
    };

    SECTION("default separators") {
        t.getNexToken(handler);
        REQUIRE(numOfTokens == 1);
    }

    numOfTokens = 0;
    SECTION("empty separators") {
        wstring seps;
        t.getNexToken(seps, handler);
        REQUIRE(numOfTokens == 1);
    }

    numOfTokens = 0;
    SECTION("all used separators") {
        wstring seps(L"#!/");
        t.getNexToken(seps, handler);
        REQUIRE(numOfTokens == 4);
    }

    numOfTokens = 0;
    SECTION("one of the used separators") {
        wstring seps(L"#");
        t.getNexToken(seps, handler);
        REQUIRE(numOfTokens == 2);
    }

    numOfTokens = 0;
    SECTION("two of the used separators") {
        wstring seps(L"#!");
        t.getNexToken(seps, handler);
        REQUIRE(numOfTokens == 3);
    }
}

TEST_CASE("Tokenizer.no_tokens_just_separators", "[Tokenizer]") {
    Tokenizer t("../../test/data/noTokensJustSeps.txt");
    REQUIRE(t.isValid());

    unsigned numOfTokens = 0;
    auto handler = [&](const wstring &_token) {
        numOfTokens++;
    };
    wstring seps(L"!@#$%");
    t.getNexToken(seps, handler);

    REQUIRE(numOfTokens == 0);
}
