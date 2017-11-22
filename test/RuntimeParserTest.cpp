#include "catch.hpp"

#include "Parser.hpp"
#include "Tokenizer.hpp"
#include "TrieManager.hpp"
#include "reference.hpp"

#include <boost/circular_buffer.hpp>

using address_recognition::Parser;
using address_recognition::Tokenizer;
using boost::circular_buffer;

std::map<string, string> paths = {
        {"../../data/extracted/zip/CZ.txt",  "../../data/tries/zip/CZ.trie"},
        {"../../data/extracted/zip/DE.txt",  "../../data/tries/zip/DE.trie"},
        {"../../data/extracted/city/DE.txt", "../../data/tries/city/DE.trie"},
        {"../../data/extracted/city/CZ.txt", "../../data/tries/city/CZ.trie"}
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

    p.addSection("zipTown", "CZ", {"../../output/tries/zip_town_cz.txt"});

    REQUIRE(p.isValid());
    p.run();
}

void parseTokenGroups(const vector<vector<wstring>> &_tokensOfInterest, const Parser &_parser) {
    for (const vector<wstring> &tokenGroup : _tokensOfInterest) {
        int score = 0;
        for (const wstring &groupElem : tokenGroup) {
//            logInfoLn(L"elem: ", groupElem);
            if (_parser.containsInSection("city", groupElem)) {
                logInfo(L"Got elem of city", groupElem, "\n");
                score++;
            }
            if (_parser.containsInSection("zip", groupElem)) {
                logInfo(L"Got elem of zip", groupElem, "\n");
                score++;
            }
            //some number not zip
            //some text not city
        }
        logInfoLn(L"Group score: ", score, "\n");
    }
}

TEST_CASE("RuntimeParser.GrammarParse", "[Parser][Runtime]") {
    generateTries();

    Tokenizer tok("../../data/txt/loremIpsum1.txt");
    REQUIRE(tok.isValid());

    Parser p(tok);

    p.addSection("zip", "CZ", {"../../data/tries/zip/CZ.trie"});
    p.addSection("zip", "DE", {"../../data/tries/zip/DE.trie"});
    p.addSection("city", "CZ", {"../../data/tries/city/CZ.trie"});
    p.addSection("city", "DE", {"../../data/tries/city/DE.trie"});

    REQUIRE(p.isValid());

    {
        vector<vector<wstring>> tokensOfInterest;
        vector<wstring> tokenGroup;
        const int THRESHOLD = 5;
        const int MIN_GROUP_SIZE = 3;
        int thrCtr = 0;
        circular_buffer<wstring> cb(THRESHOLD);

        auto handler = [&](const wstring &_token) {
            if (p.contains(_token)) {
                tokenGroup.push_back(_token);
            } else {
                thrCtr++;
                if (!tokenGroup.empty()) {
                    tokenGroup.push_back(_token);
                } else {
                    cb.push_back(_token);
                }
                if (thrCtr > THRESHOLD) {
                    thrCtr = 0;
                    if (!tokenGroup.empty()) {
                        if (tokenGroup.size() > MIN_GROUP_SIZE) {
                            tokenGroup.insert(tokenGroup.begin(), cb.begin(), cb.end());
                            tokensOfInterest.push_back(tokenGroup);
//                            cb.clear();
                        }
                        tokenGroup.clear();
                    }
                }
            }
        };

        p.run(L" ,\n", handler);

        parseTokenGroups(tokensOfInterest, p);
    }
}
