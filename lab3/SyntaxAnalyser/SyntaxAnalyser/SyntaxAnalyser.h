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
    FunctionNode ParseFunctionDefinition(shared_ptr<Token> functionName);
    FunctionCallNode ParseFunctionCall(shared_ptr<Token> functionName);

    //Variable or constant parsing
    Node ParseVariableDefinition(shared_ptr<Token> variableName);
    Node ParseVariableOrLiteral();

    //

public:

    //Public block of functions, USER MUST USE ONLY THIS FUNCTIONS!
    SyntaxAnalyser(LexicalAnalyser lexer);
    Node ParseCode();
    void PrintTree();
};


#endif //LAB3_SYNTAXANALYSER_H
