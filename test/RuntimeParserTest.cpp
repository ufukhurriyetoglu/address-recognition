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


TEST_CASE("RuntimeParser.GrammarParse", "[Parser][Runtime]") {
	generateTries();

	Tokenizer tok("../../data/txt/loremIpsum1.txt");
	REQUIRE(tok.isValid());

	Parser p(tok);

	p.addTriePath("../../output/tries/zip_town_cz.txt");
	p.loadTries();

	REQUIRE(p.isValid());

	{
		vector<vector<wstring>> tokensOfInterest;
		vector<wstring> tokenGroup;
		const int THRESHOLD = 3;
		const int MIN_GROUP_SIZE = 2;
		int thrCtr = 0;

		auto handler = [&](const wstring &_token) {
			if(p.contains(_token)) {
				tokenGroup.push_back(_token);
			} else {
				thrCtr++;
				if(thrCtr > THRESHOLD) {
					thrCtr = 0;
					if(!tokenGroup.empty()) {
						if(tokenGroup.size() >= MIN_GROUP_SIZE) {
							tokensOfInterest.push_back(tokenGroup);
						}
						tokenGroup.clear();
					}
				}
			}
		};

		p.run(handler);

		logInfoLn(L"Tokens groups size: ", tokensOfInterest.size());

		int i = 0;
		for(auto &elem : tokensOfInterest) {
			logInfoLn(L"Group: ", i);
			for(auto &elem2 : elem) {
				logInfoLn(L"Elem: ", elem2);
			}
			logInfoLn(L"____");
			i++;
		}
	}
}
