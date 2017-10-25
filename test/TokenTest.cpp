#include "catch.hpp"

#include "Token.hpp"
#include <enums.hpp>

using address_recognition::Token;
using address_recognition::enums::TOKEN_TYPE;

TEST_CASE("Token - basic parse ability") {
//    Token t("");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::NONE);
//
//    t = Token("foo");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::NONE);
//
//    t = Token("6870");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::ZIP);
//
//    t = Token("68707");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::ZIP);
//
//    t = Token("687070");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::ZIP);
//
//    t = Token(",");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::COMMA);
//
//    t = Token("Foo");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::CAPITAL_AT_BEG);
//
//    t = Token("123");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::NUMBER);
//
//    t = Token("a1");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::NONE);   // TODO
//
//    t = Token("1a");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::NONE);   // TODO
//
//    t = Token("13/1");
//    REQUIRE(t.getTokeType() == TOKEN_TYPE::NONE);   // TODO
}
