#include "catch.hpp"
#include "Trie.hpp"
#include "Tokenizer.hpp"
#include <random>

using address_recognition::Trie;
using address_recognition::Token;
using address_recognition::Tokenizer;


class RandomNumberGenerator {
    static std::default_random_engine m_rd;
public:
    static int getRandomNumber(int _lower, int _upper) {
        std::uniform_int_distribution<> randomizer(_lower, _upper);
        return randomizer(m_rd);
    }
};

std::default_random_engine   RandomNumberGenerator::m_rd{static_cast<long unsigned int>(time(0))};

std::wstring getRandomString(size_t _length) {
    auto randchar = []() -> wchar_t {
        const wchar_t charset[] =
                L"0123456789"
                        L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        L"abcdefghijklmnopqrstuvwxyz";
        auto charsetSize = wcslen(charset);
        return charset[RandomNumberGenerator::getRandomNumber(0, charsetSize - 1)];
    };

    std::wstring str(_length, L'\0');
    std::generate_n(str.begin(), _length, randchar);
    return str;
}

std::wstring getRandomStringExtra(size_t _length) {
    auto randchar = []() -> wchar_t {
        const wchar_t charset[] =
                L"0123456789"
                        L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        L"ěščřžýáíéůúň"
                        L"abcdefghijklmnopqrstuvwxyz";
        auto charsetSize = wcslen(charset);
        return charset[RandomNumberGenerator::getRandomNumber(0, charsetSize - 1)];
    };

    std::wstring str(_length, L'\0');
    std::generate_n(str.begin(), _length, randchar);
    return str;
}

TEST_CASE("TrieTest.empty", "[Trie][generate][empty]") {
    Trie t;
    vector<wstring> data = {};

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
        t.addString(_input);
    });
    REQUIRE(true);
}

TEST_CASE("TrieTest.basic", "[Trie][generate][basic]") {
    Trie t;
    const vector<wstring> data = {L"foo",
                                  L"fooz",
                                  L"foob",
                                  L"foobar",
                                  L"foobaz",
                                  L"bar",
                                  L"baz",
                                  L"baa",
                                  L"bab",
                                  L"ba1",
                                  L"baA"};

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
        t.addString(_input);
    });

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
        REQUIRE(t.contains(_input));
    });
}

TEST_CASE("TrieTest.uppCase_with_numeric", "[Trie][generate][up_num]") {
    Trie t;
    const vector<wstring> data = {L"FoO",
                                  L"fOo3",
                                  L"1oo2",
                                  L"foobar",
                                  L"foobaz",
                                  L"b4r",
                                  L"BAZaz",
                                  L"BAA",
                                  L"baB",
                                  L"bA111",
                                  L"3aA"};

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
        t.addString(_input);
    });

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
        REQUIRE(t.contains(_input));
    });
}

TEST_CASE("TrieTest.random_gen", "[Trie][generate][random]") {
    Trie t;
    vector<wstring> data = {};

    size_t val = 0;
    const int max_iter = 255;
    int ctr = 0;
    int threshold = 128;
    while (true) {
        data.push_back(getRandomString(val));
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

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
        t.addString(_input);
    });

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
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

    tok.getNexToken(L" #\n", addString);
    REQUIRE(callbackCalled);
    t.save("../../output/dummyTestOut.txt");
}

TEST_CASE("TrieTest.trie-save-no-output", "[Trie][save][zip]") {
    Trie t;
    bool callbackCalled = false;

    auto addString = [&](const Token &_token) {
        callbackCalled = true;
        t.addString(_token.getValue());
    };

    Tokenizer tok("../../test/data/dummyTestInput.txt");
    REQUIRE(tok.isValid());

    tok.getNexToken(L" #\n", addString);
    REQUIRE(callbackCalled);

    auto res = t.save("");
    REQUIRE(res == 1);
}

TEST_CASE("TrieTest.random-trie-save-load", "[Trie][save][load][CZ][zip]") {
    Trie trie;
    vector<wstring> data = {};

    auto addStringToTrie = [&trie](const wstring &_value) {
        trie.addString(_value);
    };

    auto checkIfStringInTrie = [&trie](const wstring &_value) {
        REQUIRE(trie.contains(_value));
    };

    const size_t numOfString = 5;
    const size_t lenOfStrings = 5;
    for (size_t i = 0; i < numOfString; i++) {
        data.push_back(getRandomString(lenOfStrings));
    }

    string path("../../output/randomTestOut.txt");

    std::for_each(data.begin(), data.end(), addStringToTrie);
    std::for_each(data.begin(), data.end(), checkIfStringInTrie);
    trie.save(path);

    Trie t2;
    auto res = t2.load(path);
    REQUIRE(res == 0);

    std::for_each(data.begin(), data.end(), [&t2](const wstring &_value) {
        REQUIRE(t2.contains(_value));
    });
}

TEST_CASE("TrieTest.simple-trie-save-and-load", "[Trie][save]") {
    Trie t;
    vector<wstring> data = {L"FoO",
                            L"fOo3",
                            L"1oo2",
                            L"foobar",
                            L"foobaz",
                            L"b4r",
                            L"BAZaz",
                            L"BAA",
                            L"baB",
                            L"bA111",
                            L"3aA"};

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
        t.addString(_input);
    });

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
        REQUIRE(t.contains(_input));
    });

    string path = "../../output/simpleTestOut.txt";
    t.save(path);

    Trie t2;
    auto res = t2.load(path);
    REQUIRE(res == 0);

    std::for_each(data.begin(), data.end(), [&t2](const wstring &_input) {
        REQUIRE(t2.contains(_input));
    });
}

TEST_CASE("TrieTest.sample-trie-save-and-load", "[Trie]") {
    Trie t;
    vector<wstring> content;

    auto addString = [&](const wstring &_token) {
        t.addString(_token);
        content.push_back(_token);
    };

    Tokenizer tok("../../test/data/sampleTestInput.txt");
    REQUIRE(tok.isValid());

    tok.getNexToken(L" \n", addString);
    t.save("../../output/sampleTestOut.txt");

    Trie t2;
    auto res = t2.load("../../output/sampleTestOut.txt");
    REQUIRE(res == 0);

    std::for_each(content.begin(), content.end(), [&t2](const wstring &_input) {
        REQUIRE(t2.contains(_input));
    });
}

TEST_CASE("TrieTest.PartialMatch", "[Trie]") {
    Trie t;

    const vector<wstring> data = {
            L"foo",
            L"foob",
            L"fooba",
            L"foobar",
            L"foobaz",
    };
    auto addString = [&](const wstring &_token) {
        t.addString(_token);
    };

    std::for_each(data.begin(), data.end(), addString);

    Tokenizer tok("../../test/data/sampleTestInput.txt");
    REQUIRE(tok.isValid());

    tok.getNexToken(L" \n", addString);

    t.addString(L"foobar");

    REQUIRE(!t.contains(L"Pra"));
    REQUIRE(t.contains(L"foo"));
}

TEST_CASE("TrieTest.PartialMatchLoad", "[Trie]") {
    Trie t;

    auto addString = [&](const wstring &_token) {
        t.addString(_token);
    };

    Tokenizer tok("../../test/data/sampleTestInput.txt");
    REQUIRE(tok.isValid());

    tok.getNexToken(L" \n", addString);
    t.save("../../output/sampleTestOut.txt");

    Trie t2;
    auto res = t2.load("../../output/sampleTestOut.txt");
    REQUIRE(res == 0);

    REQUIRE(!t2.contains(L"Pra"));
}

TEST_CASE("TrieTest.CaseInsensitiveBehavior", "[Trie]") {
    const vector<wstring> data = {
            L"foobar",
            L"fooBar",
            L"fobar",
            L"foObar",
            L"foobaR",
            L"FOOBAR",
            L"foobarz",
            L"foobarZ",
            L"foobaRZ",
            L"foa",
    };

    Trie t;

    auto addString = [&](const wstring &_token) {
        t.addString(_token);
    };

    std::for_each(data.begin(), data.end(), addString);

    REQUIRE(t.contains(L"foobar"));
    REQUIRE(t.contains(L"FOOBAR"));
    REQUIRE(t.contains(L"FOa"));
}

TEST_CASE("TrieTest.randomExtraGen", "[Trie][generate][random]") {
    Trie t;
    vector<wstring> data = {};

    size_t val = 0;
    const int max_iter = 64;
    int ctr = 0;
    int threshold = 32;
    while (true) {
        data.push_back(getRandomStringExtra(val));
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

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
        t.addString(_input);
    });

    std::for_each(data.begin(), data.end(), [&t](const wstring &_input) {
        REQUIRE(t.contains(_input));
    });
}
