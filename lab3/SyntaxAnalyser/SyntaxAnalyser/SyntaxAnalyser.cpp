//
// Created by Kimihito on 24.04.2023.
//

#include "SyntaxAnalyser.h"
#include "StatementsNode.h"
#include "VariableNode.h"
#include "BinaryOperationNode.h"
#include "LiteralNode.h"
#include "UnaryOperationNode.h"

SyntaxAnalyser::SyntaxAnalyser(LexicalAnalyser lexer) {
    this->lexer = lexer;
    this->tokens = lexer.tokens;
    pos = 0;
}

shared_ptr<Token> SyntaxAnalyser::Match(vector<string> tokenTypes) {
    if(pos < tokens.size()){
        shared_ptr<Token> token = tokens[pos];

        if(find(tokenTypes.begin(), tokenTypes.end(), token->value) != tokenTypes.end()){
            pos++;
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

// Parse function block

FunctionNode SyntaxAnalyser::ParseFunctionDefinition(shared_ptr<Token> functionName) {
    vector<Token> parameters = ParseFunctionParameters();

    Require(vector<string>{")"});
    Require(vector<string>{"{"});
    Node body = ParseCode();
    Require(vector<string>{"}"});

    FunctionNode result(functionName.operator*(), parameters, body);
}

vector<Token> SyntaxAnalyser::ParseFunctionParameters() {

    vector<Token> parameters;

    if(Match(vector<string>{")"}) != nullptr){

        return parameters;

    } else {

        while (Match(vector<string>{")"}) != nullptr){

            if(Match(getVector(lexer.variablesTypesTable)) == nullptr){
                throw "Ожидался тип перменной перед " + tokens[pos]->value;
            }

            parameters.push_back(Match(getVector(lexer.variablesTable)).operator*());
        }

        pos--;

        return parameters;

    }
}

FunctionCallNode SyntaxAnalyser::ParseFunctionCall(shared_ptr<Token> functionName) {
    return FunctionCallNode();
}

//Parse variable or constant block

Node SyntaxAnalyser::ParseVariableDefinition(shared_ptr<Token> variableName) {
    vector<string> tokenTypes = {"=",";"};

    VariableNode variable(variableName.operator*());

    shared_ptr<Token> token = Require(tokenTypes);

    while (token != nullptr){
        if(token->value == "="){
            return BinaryOperationNode(token.operator*(), variable,ParseFormula().operator*());
        }
        if(token->value == ";"){
            return variable;
        }
    }

}

Node SyntaxAnalyser::ParseVariableOrLiteral() {
    shared_ptr<Token> token = Match(getVector(lexer.constantsTable));

    if(token != nullptr){
        return LiteralNode(token.operator*());
    } else {
        token = Match(vector<string>{"!","++","--","-"});
        if( token != nullptr){
            return UnaryOperationNode(token.operator*(), ParseFormula().operator*());
        } else {
            return VariableNode(token.operator*());
        }
    }
}

shared_ptr<Node> SyntaxAnalyser::ParseFormula() {
    shared_ptr<Node> leftNode = ParseParentheses();
    shared_ptr<Token> token = Match(getVector(lexer.operatorsTable));

    while (token != nullptr) {
        if(token->value == "++" || token->value == "--"){
            leftNode = make_shared<UnaryOperationNode>(token.operator*(),leftNode.operator*());
        } else {
            shared_ptr<Node> rightNode = ParseParentheses();
            leftNode = make_shared<BinaryOperationNode>(token.operator*(),leftNode.operator*(),rightNode.operator*());

        }
    }

    return leftNode;
}

shared_ptr<Node> SyntaxAnalyser::ParseParentheses() {
    if(Match(vector<string>{"("}) != nullptr){
        shared_ptr<Node> node = ParseFormula();
        Require(vector<string>{")"});

        return node;
    } else {
        return make_shared<Node>(ParseVariableOrLiteral());
    }
}

shared_ptr<Node> SyntaxAnalyser::ParseExpression() {

    if(Match(getVector(lexer.variablesTypesTable)) != nullptr){

        shared_ptr<Token> variablesToken = Match(getVector(lexer.variablesTable));

        if(Match(vector<string>{"("}) != nullptr){

           return make_shared<Node>(ParseFunctionDefinition(variablesToken));

        } else{
            pos--;
            return make_shared<Node>(ParseVariableDefinition(variablesToken));
        }
    }

    if(Match(getVector(lexer.keyWordsTable)) != nullptr){

        //LOOPS AND OTHERS

    }

    if(Match(getVector(lexer.variablesTable)) != nullptr) {
        pos--;
        Node leftNode = ParseVariableOrLiteral();

        shared_ptr<Token> token = Match(getVector(lexer.operatorsTable));
        if (token != nullptr) {
            shared_ptr<Node> rightNode = ParseFormula();
            Require(vector<string>{";"});
            return make_shared<Node>(BinaryOperationNode(token.operator*(), leftNode, rightNode.operator*()));
        }
    }
    
    return shared_ptr<Node>();
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

void SyntaxAnalyser::PrintTree() {

}


