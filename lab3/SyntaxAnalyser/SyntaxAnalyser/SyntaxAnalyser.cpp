//
// Created by Kimihito on 24.04.2023.
//

#include "SyntaxAnalyser.h"
#include "StatementsNode.h"
#include "VariableNode.h"
#include "BinaryOperationNode.h"
#include "LiteralNode.h"
#include "UnaryOperationNode.h"
#include "ForNode.h"
#include "WhileNode.h"
#include "IfNode.h"
#include "SwitchNode.h"
#include "CaseNode.h"
#include "ReturnNode.h"

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

FunctionNode SyntaxAnalyser::ParseFunctionDefinition(Token functionName) {
    vector<Token> parameters = ParseFunctionParameters();

    Require(vector<string>{")"});
    Require(vector<string>{"{"});
    Node body = ParseCode();

    return FunctionNode(functionName, parameters, body);
}

vector<Token> SyntaxAnalyser::ParseFunctionParameters() {

    vector<Token> parameters;

    if(Match(getVector(lexer.variablesTypesTable)) == nullptr) {
        if (Match(vector<string>{")"}) != nullptr) {
            return parameters;
        }

        throw "После токена " + tokens[pos-1]->value + " ожидалась ) или тип переменной";
    } else {

        shared_ptr<Token> parameter = Match(getVector(lexer.variablesTable));

        if(parameter == nullptr){
            throw "После токена "+tokens[pos-1]->value + " ожидалось имя переменной";
        }
        parameters.push_back(parameter.operator*());

        shared_ptr<Token> token = Match(vector<string>{","});

        while (token != nullptr){

            if(Match(getVector(lexer.variablesTypesTable)) == nullptr){
                throw "Ожидался тип перменной перед " + tokens[pos]->value;
            }

            parameters.push_back(Match(getVector(lexer.variablesTable)).operator*());
            token = Match(vector<string>{","});
        }

        return parameters;

    }
}

FunctionCallNode SyntaxAnalyser::ParseFunctionCall(shared_ptr<Token> functionName) {

    vector<Node> parameters;
    shared_ptr<Node> parameter = ParseFormula();

    parameters.push_back(parameter.operator*());

    shared_ptr<Token> token = Match(vector<string>{","});
    while (token != nullptr){
        parameter = ParseFormula();
        parameters.push_back(parameter.operator*());
        token = Match(vector<string>{","});
    }
    Require(vector<string>{")"});
    return FunctionCallNode(functionName.operator*(), parameters);
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
            token = Match(getVector(lexer.variablesTable));
            if(Match(vector<string>{"("})){
                return ParseFunctionCall(token);
            } else {
                return VariableNode(token.operator*());
            }
        }
    }
}

//Parse keywords

Node SyntaxAnalyser::ParseFor() {

    Require(vector<string>{"("});
    shared_ptr<Node> init = ParseFormula();
    Require(vector<string>{";"});

    shared_ptr<Node> condition = ParseFormula();
    Require(vector<string>{";"});

    shared_ptr<Node> step = ParseFormula();
    Require(vector<string>{")"});

    Require(vector<string>{"{"});
    Node body = ParseCode();


    return ForNode(init.operator*(), condition.operator*(), step.operator*(), body);
}

Node SyntaxAnalyser::ParseWhile() {
    Require(vector<string>{"("});
    shared_ptr<Node> condition = ParseFormula();
    Require(vector<string>{")"});

    Require(vector<string>{"{"});
    Node body = ParseCode();

    return WhileNode(condition.operator*(), body);

}

Node SyntaxAnalyser::ParseIf() {

    Require(vector<string>{"("});
    shared_ptr<Node> condition = ParseFormula();
    Require(vector<string>{")"});

    Require(vector<string>{"{"});
    Node body = ParseCode();

    if(Match(vector<string>{"else"})){
        if(Match(vector<string>{"if"})){
            Node elseCondition = ParseIf();
            return IfNode(condition.operator*(), body, elseCondition);
        } else {
            Require(vector<string>{"{"});
            Node elseBody = ParseCode();
            return IfNode(condition.operator*(), body, elseBody);
        }
    }
    return IfNode(condition.operator*(),body);
}

Node SyntaxAnalyser::ParseSwitch() {

    Require(vector<string>{"("});
    shared_ptr<Token> switchCondition = Require(getVector(lexer.variablesTable));
    Require(vector<string>{")"});

    Require(vector<string>{"{"});
    Node body = ParseCode();

    return SwitchNode(switchCondition.operator*(), body);
}

Node SyntaxAnalyser::ParseCase() {

    Node node = ParseVariableOrLiteral();

    Require(vector<string>{":"});


    return CaseNode(node);
}

Node SyntaxAnalyser::ParseReturn() {

    shared_ptr<Node> formula = ParseFormula();

    Require(vector<string>{";"});

    return ReturnNode(formula.operator*());
}

KeyWordNode SyntaxAnalyser::ParseKeyWord(shared_ptr<Token> keyWord) {

    if(keyWord->value == "break"){
        Require(vector<string>{";"});
    }

    return KeyWordNode(keyWord.operator*());
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
        token = Match(getVector(lexer.operatorsTable));
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

    shared_ptr<Token> isVariable = Match(getVector(lexer.variablesTypesTable));
    if(isVariable != nullptr){

        shared_ptr<Token> variablesToken = Match(getVector(lexer.variablesTable));

        //Here should be a check?

        if(Match(vector<string>{"("}) != nullptr){
            FunctionNode func = ParseFunctionDefinition(variablesToken.operator*());

            shared_ptr<Node> lala = make_shared<FunctionNode>(func);

            return lala;

        } else{
            pos--;
            auto some = ParseVariableDefinition(variablesToken);
            return make_shared<Node>(ParseVariableDefinition(variablesToken));
        }
    }


    if(Match(getVector(lexer.keyWordsTable)) != nullptr){
        pos--;
        shared_ptr<Token> token = Match(getVector(lexer.keyWordsTable));

        //LOOPS AND OTHERS
        if(token->value == "for"){
            return make_shared<Node>(ParseFor());
        }
        if(token->value == "while"){
            return make_shared<Node>(ParseWhile());
        }
        if(token->value == "if"){
            return make_shared<Node>(ParseIf());
        }
        if(token->value == "switch"){
            return make_shared<Node>(ParseSwitch());
        }
        if(token->value == "case"){
            return make_shared<Node>(ParseCase());
        }
        if(token->value == "return"){
            return make_shared<Node>(ParseReturn());
        }
        if(token->value == "break"){
            return make_shared<Node>(ParseKeyWord(token));
        }

    }

    if(Match(getVector(lexer.variablesTable)) != nullptr) {
        pos--;
        shared_ptr<Token> token =  Match(getVector(lexer.variablesTable));

        if(Match(vector<string>{"("}) != nullptr){
            return make_shared<Node>(ParseFunctionCall(token));
        }

        pos--;
        Node leftNode = ParseVariableOrLiteral();

        token = Match(getVector(lexer.operatorsTable));
        if (token != nullptr) {
            shared_ptr<Node> rightNode = ParseFormula();
            Require(vector<string>{";"});
            return make_shared<Node>(BinaryOperationNode(token.operator*(), leftNode, rightNode.operator*()));
        }

    }
    
    return shared_ptr<Node>();
}

StatementsNode SyntaxAnalyser::ParseCode() {

    StatementsNode root;

    while (pos < tokens.size()){
        if(Match(vector<string>{"}"}) != nullptr){
            return root;
        }
        shared_ptr<Node> statementNode = ParseExpression();


        if(statementNode != nullptr){
            root.AddNode(statementNode.operator*());
        }
    }

    cout << endl;
    return root;
}

void SyntaxAnalyser::PrintTree(Node root) {

}




