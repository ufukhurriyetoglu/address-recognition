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

    Tokenizer t("../../test/data/dummyTestInput.txt");
    t.getNexToken(handler);
    REQUIRE(tokens.size() == 5);

    tokens.clear();
    t = Tokenizer("../../test/data/emptyTestInput.txt");
    t.getNexToken(handler);
    REQUIRE(tokens.size() == 0);

    tokens.clear();
    t = Tokenizer("../../test/data/mtpleTestInput.txt");
    t.getNexToken(handler);
    REQUIRE(tokens.size() == 3);

    tokens.clear();
    t = Tokenizer("../../test/data/nospacesTestInput.txt");
    t.getNexToken(handler);
    REQUIRE(tokens.size() == 1);
}

TEST_CASE("Tokenizer - 5 digit zip") {
//    Tokenizer t("../../test/data/5digit.txt");
//    REQUIRE(t.getNexToken() == 0);
//    REQUIRE(t.getTokens().size() == 3);
//    REQUIRE(t.getPossibleZIPs().size() == 1);
//
//    t = Tokenizer("../../test/data/5digit2.txt");
//    REQUIRE(t.getNexToken() == 0);
//    REQUIRE(t.getTokens().size() == 10);
//    REQUIRE(t.getPossibleZIPs().size() == 2);
}