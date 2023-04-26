//
// Created by Kimihito on 24.04.2023.
//

#include "SyntaxAnalyser.h"

SyntaxAnalyser::SyntaxAnalyser(LexicalAnalyser lexer, list<Token> tokens) {
    this->lexer = lexer;
    this->tokens = tokens;
    pos = 0;
}

Token SyntaxAnalyser::Match(list<string> tokenTypes) {
    if(pos < tokens.size()){

    }
    return nullptr;
}

Token SyntaxAnalyser::Require(list<string> tokenTypes) {
    return Token(__cxx11::basic_string(), __cxx11::basic_string());
}

list<string> SyntaxAnalyser::getList(map<string, string> pattern) {

    list<string> result;

    for(const pair<string,string>& pr: pattern){
        result.push_back(pr.first);
    }

    return list<string>();
}
