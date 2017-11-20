#include "Parser.hpp"

using address_recognition::Parser;
using address_recognition::enums::TOKEN_TYPE;

Parser::Parser(Tokenizer &_tokenizer) :
        m_tokenizer(_tokenizer) {
}

void Parser::run(const std::function<void(const wstring &_token)> &_callback) {
    this->m_tokenizer.getNexToken(this->m_separators, _callback);
}


void Parser::addSection(const string &_parserSectionName,
                        const string &_trieMgrSectionName,
                        const string &_path) {
    bool status = true;
    auto errorHandler = [&status]() {
        logError(__FILE__, __LINE__, L"error loading tries");
        status = false;
    };

    auto it = this->m_parserSections.find(_parserSectionName);
    if (it != this->m_parserSections.end()) {
        it->second->addSectionFromFile(_trieMgrSectionName, _path, errorHandler);
    } else {
        unique_ptr<TrieManager> tmgr = std::make_unique<TrieManager>();
        tmgr->addSectionFromFile(_trieMgrSectionName, _path, errorHandler);
        this->m_parserSections.insert(std::make_pair(_parserSectionName, std::move(tmgr)));
    }

    this->m_valid = status;
}


void Parser::run(const wstring &_seps, const std::function<void(const wstring &)> &_callback) {
    this->m_tokenizer.getNexToken(_seps, _callback);
}

void Parser::setSeparators(const wstring &_newSeps) {
    this->m_separators = _newSeps;
}

bool Parser::contains(const wstring &_query) {
    for(const auto &elem : this->m_parserSections){
        if(elem.second->contains(_query)){
            return true;
        }
    }
    return false;
}
