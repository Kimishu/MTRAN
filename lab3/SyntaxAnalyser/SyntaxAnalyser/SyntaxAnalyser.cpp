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
#include "VariableTypeNode.h"

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

    try {
        if (!token) {
            throw ("на позиции " + to_string(pos) + " ожидается " + tokenTypes[0]);
        }
    }
    catch (...){
        cout << "на позиции " + to_string(pos) + " ожидается " + tokenTypes[0] << endl;
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

shared_ptr<Node> SyntaxAnalyser::ParseFunctionDefinition(Token functionName) {
    vector<Token> parameters = ParseFunctionParameters();

    Require(vector<string>{")"});
    Require(vector<string>{"{"});
    shared_ptr<Node> body = ParseCode();

    return make_shared<FunctionNode>(functionName, parameters, body);
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

shared_ptr<Node> SyntaxAnalyser::ParseFunctionCall(shared_ptr<Token> functionName) {

    vector<shared_ptr<Node>> parameters;
    shared_ptr<Node> parameter = ParseFormula();

    parameters.push_back(parameter);

    shared_ptr<Token> token = Match(vector<string>{","});
    while (token != nullptr){
        parameter = ParseFormula();
        parameters.push_back(parameter);
        token = Match(vector<string>{","});
    }
    Require(vector<string>{")"});
    return make_shared<FunctionCallNode>(functionName.operator*(), parameters);
}

//Parse variable or constant block

shared_ptr<Node> SyntaxAnalyser::ParseVariableDefinition(shared_ptr<Token> variableName) {
    vector<string> tokenTypes = {"=",";"};

    shared_ptr<VariableNode> variable = make_shared<VariableNode>(variableName.operator*());

    shared_ptr<Token> token = Require(tokenTypes);

    while (token != nullptr){
        if(token->value == "="){
            shared_ptr<BinaryOperationNode> binaryOperationNode = make_shared<BinaryOperationNode>(token.operator*(), variable,ParseFormula());

            Require(vector<string>{";"});

            return binaryOperationNode;
        }
        if(token->value == ";"){
            return make_shared<VariableNode>(variable->variable);
        }

        token = Require(tokenTypes);
    }

}

shared_ptr<Node> SyntaxAnalyser::ParseVariableOrLiteral() {
    shared_ptr<Token> token = Match(getVector(lexer.constantsTable));

    if(token != nullptr){
        return make_shared<LiteralNode>(token.operator*());
    } else {
        token = Match(vector<string>{"!","++","--","-"});
        if( token != nullptr){
            return make_shared<UnaryOperationNode>(token.operator*(), ParseFormula());
        } else {
            token = Match(getVector(lexer.variablesTable));
            if(Match(vector<string>{"("})){
                return ParseFunctionCall(token);
            } else {
                return make_shared<VariableNode>(token.operator*());
            }
        }
    }
}

//Parse keywords

shared_ptr<Node> SyntaxAnalyser::ParseFor() {

    Require(vector<string>{"("});
    shared_ptr<Node> init = ParseFormula();
    Require(vector<string>{";"});

    shared_ptr<Node> condition = ParseFormula();
    Require(vector<string>{";"});

    shared_ptr<Node> step = ParseFormula();
    Require(vector<string>{")"});

    Require(vector<string>{"{"});
    shared_ptr<Node> body = ParseCode();

    return make_shared<ForNode>(init, condition, step, body);
}

shared_ptr<Node> SyntaxAnalyser::ParseWhile() {

    Require(vector<string>{"("});
    shared_ptr<Node> condition = ParseFormula();
    Require(vector<string>{")"});

    Require(vector<string>{"{"});
    shared_ptr<Node> body = ParseCode();

    return make_shared<WhileNode>(condition, body);
}

shared_ptr<Node> SyntaxAnalyser::ParseIf() {

    Require(vector<string>{"("});
    shared_ptr<Node> condition = ParseFormula();
    Require(vector<string>{")"});

    Require(vector<string>{"{"});
    shared_ptr<Node> body = ParseCode();

    if(Match(vector<string>{"else"})){
        if(Match(vector<string>{"if"})){
            shared_ptr<Node> elseCondition = ParseIf();
            return make_shared<IfNode>(condition, body, elseCondition);
        } else {
            Require(vector<string>{"{"});
            shared_ptr<Node> elseBody = ParseCode();
            return make_shared<IfNode>(condition, body, elseBody);
        }
    }
    return make_shared<IfNode>(condition,body);
}

shared_ptr<Node> SyntaxAnalyser::ParseSwitch() {

    Require(vector<string>{"("});
    shared_ptr<Token> switchCondition = Require(getVector(lexer.variablesTable));
    Require(vector<string>{")"});

    Require(vector<string>{"{"});
    shared_ptr<Node> body = ParseCode();

    return make_shared<SwitchNode>(switchCondition.operator*(), body);
}

shared_ptr<Node> SyntaxAnalyser::ParseCase() {
//HERE
    shared_ptr<Node> node = ParseVariableOrLiteral();

    Require(vector<string>{":"});


    return make_shared<CaseNode>(node);
}

shared_ptr<Node> SyntaxAnalyser::ParseReturn() {

    shared_ptr<Node> formula = ParseFormula();

    Require(vector<string>{";"});

    return make_shared<ReturnNode>(formula);
}

shared_ptr<Node> SyntaxAnalyser::ParseKeyWord(shared_ptr<Token> keyWord) {

    if(keyWord->value == "break"){
        Require(vector<string>{";"});
    }

    return make_shared<KeyWordNode>(keyWord.operator*());
}

shared_ptr<Node> SyntaxAnalyser::ParseFormula() {
    shared_ptr<Node> leftNode = ParseParentheses();
    shared_ptr<Token> token = Match(getVector(lexer.operatorsTable));

    while (token != nullptr) {
        if(token->value == "++" || token->value == "--"){
            leftNode = make_shared<UnaryOperationNode>(token.operator*(),leftNode);
        } else {
            shared_ptr<Node> rightNode = ParseParentheses();
            leftNode = make_shared<BinaryOperationNode>(token.operator*(),leftNode,rightNode);
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
        //HERE
        return ParseVariableOrLiteral();
    }
}

shared_ptr<Node> SyntaxAnalyser::ParseExpression() {

    shared_ptr<Token> isVariable = Match(getVector(lexer.variablesTypesTable));
    if(isVariable != nullptr){

        shared_ptr<Token> variablesToken = Match(getVector(lexer.variablesTable));

        //Here should be a check?

        if(Match(vector<string>{"("}) != nullptr){

            return ParseFunctionDefinition(variablesToken.operator*());
        } else{

            return ParseVariableDefinition(variablesToken);
        }
    }


    if(Match(getVector(lexer.keyWordsTable)) != nullptr){
        pos--;
        shared_ptr<Token> token = Match(getVector(lexer.keyWordsTable));

        //LOOPS AND OTHERS
        if(token->value == "for"){
            return ParseFor();
        }
        if(token->value == "while"){
            return ParseWhile();
        }
        if(token->value == "if"){
            return ParseIf();
        }
        if(token->value == "switch"){
            return ParseSwitch();
        }
        if(token->value == "case"){
            return ParseCase();
        }
        if(token->value == "return"){
            return ParseReturn();
        }
        if(token->value == "break"){
            return ParseKeyWord(token);
        }

    }

    if(Match(getVector(lexer.variablesTable)) != nullptr) {
        pos--;
        shared_ptr<Token> token =  Match(getVector(lexer.variablesTable));

        if(Match(vector<string>{"("}) != nullptr){
            return ParseFunctionCall(token);
        }

        pos--;
        shared_ptr<Node> leftNode = ParseVariableOrLiteral();

        token = Match(getVector(lexer.operatorsTable));
        if (token != nullptr) {
            shared_ptr<Node> rightNode = ParseFormula();
            Require(vector<string>{";"});
            return make_shared<BinaryOperationNode>(token.operator*(), leftNode, rightNode);
        }

    }
    
    return shared_ptr<Node>();
}

shared_ptr<Node> SyntaxAnalyser::ParseCode() {

    StatementsNode root;

    while (pos < tokens.size()){
        if(Match(vector<string>{"}"}) != nullptr){
            return make_shared<StatementsNode>(root);
        }
        shared_ptr<Node> statementNode = ParseExpression();


        if(statementNode != nullptr){
            root.AddNode(statementNode);
        }
    }

    cout << endl;
    return make_shared<StatementsNode>(root);
}

void SyntaxAnalyser::PrintNode(shared_ptr<Node> root, int level) {


    if (root == nullptr) {
        return;
    }

    if (root->getType() == Statements) {
        shared_ptr<StatementsNode> statementsNode = dynamic_pointer_cast<StatementsNode>(root);

        for (shared_ptr<Node> node: statementsNode->nodes) {
            PrintNode(node, level);
        }
    }

    if (root->getType() == Function) {
        PrintTab(level);
        shared_ptr<FunctionNode> functionNode = dynamic_pointer_cast<FunctionNode>(root);

        cout << functionNode->function.value << endl;
        PrintTab(level + 1);

        for (Token &token: functionNode->parameters) {
            cout << token.value << " ";
        }

        cout << endl;

        PrintNode(functionNode->body, level + 1);
    }

    if (root->getType() == While) {
        shared_ptr<WhileNode> whileNode = dynamic_pointer_cast<WhileNode>(root);
        PrintTab(level);
        cout << "while" << endl;
        PrintNode(whileNode->condition, level + 1);
        PrintNode(whileNode->body, level + 1);
    }

    if (root->getType() == If) {
        shared_ptr<IfNode> ifNode = dynamic_pointer_cast<IfNode>(root);
        PrintTab(level);
        cout << "if" << endl;
        PrintNode(ifNode->condition, level + 1);
        PrintNode(ifNode->body, level + 1);
        PrintNode(ifNode->elseBody, level + 1);
    }

    if (root->getType() == For) {
        shared_ptr<ForNode> forNode = dynamic_pointer_cast<ForNode>(root);
        PrintTab(level);
        cout << "for" << endl;

        PrintNode(forNode->init, level + 1);
        PrintNode(forNode->condition, level + 1);
        PrintNode(forNode->step, level + 1);
        PrintNode(forNode->body, level + 1);
    }

    if (root->getType() == FunctionCall) {
        shared_ptr<FunctionCallNode> functionCallNode = dynamic_pointer_cast<FunctionCallNode>(root);
        PrintTab(level);
        cout << functionCallNode->function.value << endl;

        for (shared_ptr<Node> &node: functionCallNode->parameters) {
            PrintNode(node, level + 1);
        }

    }

    if (root->getType() == Switch) {
        shared_ptr<SwitchNode> switchNode = dynamic_pointer_cast<SwitchNode>(root);
        PrintTab(level);
        cout << "switch" << endl;
        PrintTab(level);
        cout << switchNode->variable.value << endl;
        PrintNode(switchNode->body, level + 1);
    }

    if(root->getType() == Case){
        shared_ptr<CaseNode> caseNode = dynamic_pointer_cast<CaseNode>(root);
        PrintTab(level);
        cout << "case" << endl;
        PrintTab(level);
        PrintNode(caseNode->literal, level+1);
    }

    if (root->getType() == KeyWord) {
        shared_ptr<KeyWordNode> keyWordNode = dynamic_pointer_cast<KeyWordNode>(root);
        PrintTab(level);
        cout << keyWordNode->keyWord.value << endl;
    }

    if (root->getType() == Binary) {
        shared_ptr<BinaryOperationNode> binaryOperationNode = dynamic_pointer_cast<BinaryOperationNode>(root);
        PrintTab(level);
        cout << binaryOperationNode->binaryOperator.value << endl;
        PrintNode(binaryOperationNode->leftNode, level + 1);
        PrintNode(binaryOperationNode->rightNode, level + 1);
    }

    if (root->getType() == UnaryOperation) {
        shared_ptr<UnaryOperationNode> unaryOperationNode = dynamic_pointer_cast<UnaryOperationNode>(root);
        PrintTab(level);
        cout << unaryOperationNode->unaryOperator.value << endl;
        PrintNode(unaryOperationNode->operand, level + 1);
    }

    if (root->getType() == Literal) {
        shared_ptr<LiteralNode> literalNode = dynamic_pointer_cast<LiteralNode>(root);
        PrintTab(level);
        cout << literalNode->number.value << endl;
    }

    if (root->getType() == Variable) {
        shared_ptr<VariableNode> variableNode = dynamic_pointer_cast<VariableNode>(root);
        PrintTab(level);
        cout << variableNode->variable.value << endl;
    }

//    if(root->getType() == VariableType){
//        shared_ptr<VariableTypeNode> variableTypeNode = dynamic_pointer_cast<VariableTypeNode>(root);
//        PrintTab(level);
//        cout << variableTypeNode.type.value();
//    }

    if (root->getType() == Return) {
        shared_ptr<ReturnNode> returnNode = dynamic_pointer_cast<ReturnNode>(root);
        PrintTab(level);
        cout << "return" << endl;
        PrintNode(returnNode->statement, level + 1);
    }
}

void SyntaxAnalyser::PrintTab(int level) {
    for(int i = 0; i < level; i++){
        cout << "    ";
    }
}
