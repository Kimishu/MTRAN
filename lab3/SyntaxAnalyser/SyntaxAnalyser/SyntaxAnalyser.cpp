//
// Created by Kimihito on 24.04.2023.
//

#include "SyntaxAnalyser.h"
#include "StatementsNode.h"

SyntaxAnalyser::SyntaxAnalyser(LexicalAnalyser lexer, vector<Token> tokens) {
    this->lexer = lexer;
    this->tokens = tokens;
    pos = 0;
}

unique_ptr<Token> SyntaxAnalyser::Match(vector<string> tokenTypes) {
    if(pos < tokens.size()){
        unique_ptr<Token> token = make_unique<Token>(tokens[pos]);

        if(find(tokenTypes.begin(), tokenTypes.end(), token->value) != tokenTypes.end()){
            return token;
        }
    }

    return nullptr;
}

unique_ptr<Token> SyntaxAnalyser::Require(vector<string> tokenTypes) {
    unique_ptr<Token> token = Match(tokenTypes);

    if(!token){
        throw ("на позиции " + to_string(pos) + " ожидается " + tokenTypes[0]);
    }

    return token;
}

vector<string> SyntaxAnalyser::getVector(map<string, string> pattern) {

    vector<string> result;

    for(const pair<string,string>& pr: pattern){
        result.push_back(pr.first);
    }

    return result;
}

//Node SyntaxAnalyser::ParseCode() {
//
//    StatementsNode root;
//
//    while (pos < tokens.size()){
//
//    }
//
//}
