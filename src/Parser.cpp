#include "Parser.hpp"

using address_recognition::Parser;
using address_recognition::enums::TOKEN_TYPE;

Parser::Parser(Tokenizer &_tokenizer) :
	m_tokenizer(_tokenizer) {
}

void Parser::run(const std::function<void(const wstring &_token)> &_callback) {
//	vector<wstring> tokensOfInterest;
//	const int threshold = 4;
//	int threshCtr = 0;

	this->m_tokenizer.getNexToken(_callback);

//		if (this->m_trieMgr.isTokenIn(_token)) {
//			tokensOfInterest.push_back(_token);
//		} else {
//			threshCtr++;
//			if (!tokensOfInterest.empty()) {
//				this->m_tokens.push_back(tokensOfInterest);
//				tokensOfInterest.clear();
//			}
//		}
//});
}

void Parser::addTriePath(const string &_path) {
	this->m_triePaths.push_back(_path);
}

void Parser::addTriePaths(const vector<string> &_paths) {
	for (const auto &elem:_paths) {
		std::cout << "adding: " << elem << std::endl;
		this->m_triePaths.push_back(elem);
	}
}

void Parser::loadTries() {
	bool status = true;
	auto errorHandler = [&status]() {
		logError(__FILE__, __LINE__, L"error loading tries");
		status = false;
	};
	this->m_trieMgr.loadTriesFromFiles(this->m_triePaths, errorHandler);
	this->m_valid = status;
}

//void runCallback(const std::function<void(const wstring &_token)> &_callback) {
//}
