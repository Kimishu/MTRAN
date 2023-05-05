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
    FunctionNode ParseFunctionDefinition(Token functionName);
    FunctionCallNode ParseFunctionCall(shared_ptr<Token> functionName);

    //Variable or constant parsing
    Node ParseVariableDefinition(shared_ptr<Token> variableName);
    Node ParseVariableOrLiteral();

    //Loops parsing
    Node ParseFor();
    Node ParseWhile();

    //If/Switch
    Node ParseIf();
    Node ParseSwitch();
    Node ParseCase();

    Node ParseReturn();

    KeyWordNode ParseKeyWord(shared_ptr<Token> keyWord);



public:

    //Public block of functions, USER MUST USE ONLY THIS FUNCTIONS!
    SyntaxAnalyser(LexicalAnalyser lexer);
    StatementsNode ParseCode();
    void PrintTree(Node root);

};


#endif //LAB3_SYNTAXANALYSER_H
