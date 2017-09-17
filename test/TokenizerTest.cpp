#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Tokenizer.hpp"

using address_recognition::Tokenizer;

TEST_CASE("Tokenizer - not existing input file")
{
    Tokenizer t("");
    REQUIRE(t.parseFile() == 1);

    Tokenizer t2("");
    REQUIRE(t.parseFile() == 1);
}

TEST_CASE("Tokenizer - existing input file"){
    Tokenizer t("../../test/data/dummyTestInput.txt");
    REQUIRE(t.parseFile() == 0);
}

TEST_CASE("Tokenizer - empty input file"){
    Tokenizer t("../../test/data/emptyTestInput.txt");
    REQUIRE(t.parseFile() == 0);
}

TEST_CASE("Tokenizer - multiple spaces input file"){
    Tokenizer t("../../test/data/mtpleTestInput.txt");
    REQUIRE(t.parseFile() == 0);
}

TEST_CASE("Tokenizer - no spaces input file"){
    Tokenizer t("../../test/data/nospacesTestInput.txt");
    REQUIRE(t.parseFile() == 0);
}