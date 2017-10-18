#include "catch.hpp"
#include "Parser.hpp"
#include "Tokenizer.hpp"

using address_recognition::Parser;
using address_recognition::Tokenizer;

TEST_CASE("Parser - basic read", "[Parser]") {
    Tokenizer t("../../test/data/mtpleTestInput.txt");
    Parser p(t);
    p.run();
    REQUIRE(p.getTokens().size() == 3);
}