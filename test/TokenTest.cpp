#include "catch.hpp"

#include "Token.hpp"

using address_recognition::Token;

TEST_CASE("Token - match czech ZIP") {
    Token t("");
    REQUIRE(!t.isZIP());

    t = Token("foo");
    REQUIRE(!t.isZIP());

    t = Token("68707");
    REQUIRE(t.isZIP());
}
