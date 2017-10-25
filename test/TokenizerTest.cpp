#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include <reference.hpp>

#include "Tokenizer.hpp"
#include "Token.hpp"

using address_recognition::Tokenizer;
using address_recognition::Token;

TEST_CASE("Tokenizer - not existing input file", "[Tokenizer]") {
    Tokenizer t("");
    bool callbackCalled = false;
    auto callback = [&](const Token &_token) {
        callbackCalled = true;
    };
    t.getNexToken(callback);
    REQUIRE(!callbackCalled);
    REQUIRE(!t.isValid());
}

TEST_CASE("Tokenizer - existing input file", "[Tokenizer]") {
    vector<Token> tokens;
    auto handler = [&](const Token &_token) {
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

TEST_CASE("Tokenizer.empty_separators") {
    Tokenizer t("../../test/data/dummyTestInput.txt");
    REQUIRE(t.isValid());

    bool callbackCalled = false;
    unsigned numOfTokens = 0;
    auto handler = [&](const Token &_token) {
        callbackCalled = true;
        numOfTokens++;
    };
    string seps;
    t.getNexToken(seps, handler);

    REQUIRE(callbackCalled);
    REQUIRE(numOfTokens == 1);
}

TEST_CASE("Tokenizer.set_separators") {
    Tokenizer t("../../test/data/dummyTestInput.txt");
    REQUIRE(t.isValid());

    bool callbackCalled = false;
    unsigned numOfTokens = 0;
    auto handler = [&](const Token &_token) {
        callbackCalled = true;
        numOfTokens++;
    };

    SECTION("separators are present in file") {
        string seps = " ";
        t.getNexToken(seps, handler);

        REQUIRE(callbackCalled);
        REQUIRE(numOfTokens == 5);
    }

    callbackCalled = false;
    numOfTokens = 0;

    SECTION("separators are not in file") {
        string seps = "#;(";
        t.getNexToken(seps, handler);

        REQUIRE(callbackCalled);
        REQUIRE(numOfTokens == 1);
    }
}

TEST_CASE("Tokenizer.separators_mixed") {
    Tokenizer t("../../test/data/separatorTestInput.txt");
    REQUIRE(t.isValid());

    unsigned numOfTokens = 0;
    auto handler = [&](const string &_token) {
        numOfTokens++;
    };

    SECTION("default separators") {
        t.getNexToken(handler);
        REQUIRE(numOfTokens == 1);
    }

    numOfTokens = 0;
    SECTION("empty separators") {
        string seps;
        t.getNexToken(seps, handler);
        REQUIRE(numOfTokens == 1);
    }

    numOfTokens = 0;
    SECTION("all used separators") {
        string seps("#!/");
        t.getNexToken(seps, handler);
        REQUIRE(numOfTokens == 4);
    }

    numOfTokens = 0;
    SECTION("one of the used separators") {
        string seps("#");
        t.getNexToken(seps, handler);
        REQUIRE(numOfTokens == 2);
    }

    numOfTokens = 0;
    SECTION("two of the used separators") {
        string seps("#!");
        t.getNexToken(seps, handler);
        REQUIRE(numOfTokens == 3);
    }
}

TEST_CASE("Tokenizer.no_tokens_just_separators") {
    Tokenizer t("../../test/data/noTokensJustSeps.txt");
    REQUIRE(t.isValid());

    unsigned numOfTokens = 0;
    auto handler = [&](const string &_token) {
        numOfTokens++;
    };
    string seps("!@#$%");
    t.getNexToken(seps, handler);

    REQUIRE(numOfTokens == 0);
}
