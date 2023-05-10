//
// Created by Kimihito on 24.04.2023.
//

#ifndef LAB3_SYNTAXANALYSER_H
#define LAB3_SYNTAXANALYSER_H

#include "Token.h"
#include "LexicalAnalyser.h"
#include "Node.h"
#include "FunctionNode.h"
#include "FunctionCallNode.h"
#include "KeyWordNode.h"
#include "StatementsNode.h"
#include "WhileNode.h"
#include "ForNode.h"

class SyntaxAnalyser {

    LexicalAnalyser lexer;
    vector<shared_ptr<Token>> tokens;
    int pos;

    //Helpful functions
    vector<string> getVector(map<string,string> pattern);
    shared_ptr<Token> Match(vector<string> tokenTypes);
    shared_ptr<Token> Require(vector<string> tokenTypes);

    //Parsing
    shared_ptr<Node> ParseExpression();
    shared_ptr<Node> ParseFormula();
    shared_ptr<Node> ParseParentheses();

    //Function parsing
    vector<Token> ParseFunctionParameters();
    shared_ptr<Node> ParseFunctionDefinition(Token functionName);
    shared_ptr<Node> ParseFunctionCall(shared_ptr<Token> functionName);

    //Variable or constant parsing
    shared_ptr<Node> ParseVariableDefinition(shared_ptr<Token> variableName);
    shared_ptr<Node> ParseVariableOrLiteral();

    //Loops parsing
    shared_ptr<Node> ParseFor();
    shared_ptr<Node> ParseWhile();

    //If/Switch
    shared_ptr<Node> ParseIf();
    shared_ptr<Node> ParseSwitch();
    shared_ptr<Node> ParseCase();

    shared_ptr<Node> ParseReturn();

    shared_ptr<Node> ParseKeyWord(shared_ptr<Token> keyWord);



    void PrintTab(int level);

public:

    //Public block of functions, USER MUST USE ONLY THIS FUNCTIONS!
    SyntaxAnalyser(LexicalAnalyser lexer);
    shared_ptr<Node> ParseCode();
    void PrintNode(shared_ptr<Node> root, int level = 0);
};


#endif //LAB3_SYNTAXANALYSER_H
