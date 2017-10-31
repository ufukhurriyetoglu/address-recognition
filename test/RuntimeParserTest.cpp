#include "catch.hpp"

#include "Parser.hpp"
#include "Tokenizer.hpp"
#include "TrieManager.hpp"
#include "reference.hpp"

using address_recognition::Parser;
using address_recognition::Tokenizer;

std::map<string, string> paths = {
        {"../../data/extracted/zip_town/cz.txt", "../../output/tries/zip_town_cz.txt"}
};

void generateTries() {
    auto errorHandler = [](int _errNum) {
    };

    TrieManager::createTries(paths, errorHandler);
}

TEST_CASE("RuntimeParser.BasicRead", "[Parser][Runtime]") {
    generateTries();
    Tokenizer tok("../../data/txt/loremIpsum1.txt");
    REQUIRE(tok.isValid());
    Parser p(tok);
    p.addTriePath("../../output/tries/zip_town_cz.txt");
    p.loadTries();
    REQUIRE(p.isValid());
    p.run();
}
