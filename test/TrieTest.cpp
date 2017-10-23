#include "catch.hpp"
#include "Trie.hpp"
#include "Tokenizer.hpp"

using address_recognition::Trie;
using address_recognition::Token;
using address_recognition::Tokenizer;

std::string random_string(size_t length) {
    auto randchar = []() -> char {
        const char charset[] =
                "0123456789"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

TEST_CASE("TrieTest.empty", "[Trie][generate][empty]") {
    Trie t;
    vector<string> data = {};

    std::for_each(data.begin(), data.end(), [&t](const string &_input) {
        t.addString(_input);
    });
    REQUIRE(true);
}

TEST_CASE("TrieTest.basic", "[Trie][generate][basic]") {
    Trie t;
    vector<string> data = {"foo",
                           "fooz",
                           "foob",
                           "foobar",
                           "foobaz",
                           "bar",
                           "baz",
                           "baa",
                           "bab",
                           "ba1",
                           "baA"};

    std::for_each(data.begin(), data.end(), [&t](const string &_input) {
        t.addString(_input);
    });

    std::for_each(data.begin(), data.end(), [&t](const string &_input) {
        REQUIRE(t.contains(_input));
    });

    t.print();
}

TEST_CASE("TrieTest.uppCase_with_numeric", "[Trie][generate][up_num]") {
    Trie t;
    vector<string> data = {"FoO",
                           "fOo3",
                           "1oo2",
                           "foobar",
                           "foobaz",
                           "b4r",
                           "BAZaz",
                           "BAA",
                           "baB",
                           "bA111",
                           "3aA"};

    std::for_each(data.begin(), data.end(), [&t](const string &_input) {
        t.addString(_input);
    });

    std::for_each(data.begin(), data.end(), [&t](const string &_input) {
        REQUIRE(t.contains(_input));
    });
}

TEST_CASE("TrieTest.random_gen", "[Trie][generate][random]") {
    Trie t;
    vector<string> data = {};

    size_t val = 0;
    const int max_iter = 255;
    int ctr = 0;
    int threshold = 128;
    while (true) {
        data.push_back(random_string(val));
        if (ctr < threshold) {
            val++;
        } else {
            val--;
        }
        ctr++;
        if (ctr >= max_iter || val <= 0) {
            break;
        }
    }

    std::for_each(data.begin(), data.end(), [&t](const string &_input) {
        t.addString(_input);
    });

    std::for_each(data.begin(), data.end(), [&t](const string &_input) {
        REQUIRE(t.contains(_input));
    });
}

TEST_CASE("TrieTest.none-load", "[Trie][load][none]") {
    Trie t;
    bool callbackCalled = false;

    auto addString = [&](const Token &_token) {
        callbackCalled = true;
        t.addString(_token.getValue());
    };

    Tokenizer tok("");
    tok.getNexToken(addString);

    REQUIRE(!tok.isValid());
    REQUIRE(!callbackCalled);
}

TEST_CASE("TrieTest.dummy-trie-save", "[Trie][save][CZ][zip]") {
    Trie t;
    bool callbackCalled = false;

    auto addString = [&](const Token &_token) {
        callbackCalled = true;
        t.addString(_token.getValue());
    };

    Tokenizer tok("../../test/data/dummyTestInput.txt");
    REQUIRE(tok.isValid());

    tok.getNexToken(" #\n", addString);
    REQUIRE(callbackCalled);
    t.print();
    t.save("../../output/dummyTestOut.txt");
}

TEST_CASE("TrieTest.random-trie-save-load", "[Trie][save][load][CZ][zip]") {
    Trie trie;
    vector<string> data = {};

    auto addStringToTrie = [&trie](const string &_value) {
        trie.addString(_value);
    };

    auto checkIfStringInTrie = [&trie](const string &_value) {
        REQUIRE(trie.contains(_value));
    };

    const size_t numOfString = 5;
    const size_t lenOfStrings = 5;
    for (size_t i = 0; i < numOfString; i++) {
        data.push_back(random_string(lenOfStrings));
    }

    string path("../../output/randomTestOut.txt");

    std::for_each(data.begin(), data.end(), addStringToTrie);
    std::for_each(data.begin(), data.end(), checkIfStringInTrie);
    trie.save(path);

    Trie t2;
    auto res = t2.load(path);
    REQUIRE(res == 0);

    std::for_each(data.begin(), data.end(), [&t2](const string &_value) {
        REQUIRE(t2.contains(_value));
    });
}

TEST_CASE("TrieTest.simple-trie-save-and-load", "[Trie][save]") {
    Trie t;
    vector<string> data = {"FoO",
                           "fOo3",
                           "1oo2",
                           "foobar",
                           "foobaz",
                           "b4r",
                           "BAZaz",
                           "BAA",
                           "baB",
                           "bA111",
                           "3aA"};

    std::for_each(data.begin(), data.end(), [&t](const string &_input) {
        t.addString(_input);
    });

    std::for_each(data.begin(), data.end(), [&t](const string &_input) {
        REQUIRE(t.contains(_input));
    });

    string path = "../../output/simpleTestOut.txt";
    t.save(path);

    Trie t2;
    auto res = t2.load(path);
    REQUIRE(res == 0);

    std::for_each(data.begin(), data.end(), [&t2](const string &_input) {
        REQUIRE(t2.contains(_input));
    });
}

TEST_CASE("TrieTest.dummy-trie-save-and-load", "[Trie][save][CZ][zip]") {
    Trie t;
    vector<string> content;

    auto addString = [&](const Token &_token) {
        t.addString(_token.getValue());
        content.push_back(_token.getValue());
    };

    SECTION("Create and Save trie") {
        Tokenizer tok("../../test/data/sampleTestInput.txt");
        REQUIRE(tok.isValid());

        tok.getNexToken(" \n", addString);
        t.save("../../output/sampleTestOut.txt");
    }

    SECTION("Load trie") {
        Trie t2;
        auto res = t2.load("../../output/sampleTestOut.txt");
        REQUIRE(res == 0);

        std::for_each(content.begin(), content.end(), [&t2](const string &_input) {
            REQUIRE(t2.contains(_input));
        });
    }
}
