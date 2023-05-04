//
// Created by Kimihito on 24.04.2023.
//

#include "SyntaxAnalyser.h"
#include "StatementsNode.h"

SyntaxAnalyser::SyntaxAnalyser(LexicalAnalyser lexer) {
    this->lexer = lexer;
    this->tokens = lexer.tokens;
    pos = 0;
}

shared_ptr<Token> SyntaxAnalyser::Match(vector<string> tokenTypes) {
    if(pos < tokens.size()){
        shared_ptr<Token> token = tokens[pos];

        if(find(tokenTypes.begin(), tokenTypes.end(), token->value) != tokenTypes.end()){
            return token;
        }
    }

    return nullptr;
}

shared_ptr<Token> SyntaxAnalyser::Require(vector<string> tokenTypes) {
    shared_ptr<Token> token = Match(tokenTypes);

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

//Function parsing block

FunctionNode SyntaxAnalyser::ParseFunction(){

    return FunctionNode()

}

vector<Token> SyntaxAnalyser::ParseFunctionDefinition() {
    vector<Token> parameters;

    if
}

shared_ptr<Node> SyntaxAnalyser::ParseExpression() {

    if(Match(getVector(lexer.variablesTypesTable)) != nullptr){

        shared_ptr<Token> variablesToken = Match(getVector(lexer.variablesTable));

        if(Match(vector<string>{"("}) != nullptr){

            vector<Token> parameters = ParseFunctionDefinition();

        } else{

        }

    }

    return shared_ptr<Node>();
}

void SyntaxAnalyser::PrintTree() {

}

Node SyntaxAnalyser::ParseCode() {

    StatementsNode root;

    while (pos < tokens.size()){
        if(Match(vector<string>{"}"}) != nullptr){
            return root;
        }
        pos--;
        shared_ptr<Node> statementNode = ParseExpression();

        if(statementNode != nullptr){
            root.AddNode(statementNode.operator*());
        }
    }

    return root;
}
