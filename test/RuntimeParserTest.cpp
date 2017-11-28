#include "catch.hpp"

#include "Parser.hpp"
#include "Tokenizer.hpp"
#include "TrieManager.hpp"
#include "reference.hpp"

#include <boost/circular_buffer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

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

inline bool isStreetNum(const wstring &_query) {
    std::wregex r(LR"(([0-9]{1,}[\/]*[a-zA-Z]*[0-9]*[a-zA-Z]*))");
    return std::regex_match(boost::trim_copy(_query), r);
}

inline bool isStreet(const wstring &_query) {
    return boost::all(_query, boost::is_alpha());
}

void parseTokenGroups(const vector<vector<wstring>> &_tokensOfInterest, const Parser &_parser) {
    for (const vector<wstring> &tokenGroup : _tokensOfInterest) {
        int score = 0, city = 0, zip = 0, streetName = 0, streetNum = 0;
        for (const wstring &groupElem : tokenGroup) {
            if (_parser.containsInSection("city", groupElem)) {
                logInfo(L"Got elem of city", groupElem, "\n");
                city++;
            } else {
                if (isStreet(groupElem)) {
                    logInfo(L"Got street name", groupElem, "\n");
                    streetName++;
                }
            }
            if (_parser.containsInSection("zip", groupElem)) {
                logInfo(L"Got elem of zip", groupElem, "\n");
                zip++;
            } else {
                if (isStreetNum(groupElem)) {
                    logInfo(L"Got street num", groupElem, "\n");
                    streetNum++;
                }
            }
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
