//
// Created by Kimihito on 24.04.2023.
//

#ifndef LAB3_SYNTAXANALYSER_H
#define LAB3_SYNTAXANALYSER_H

#include "Token.h"
#include "LexicalAnalyser.h"
#include "Node.h"
#include "../Nodes/FunctionNode/FunctionNode.h"

class SyntaxAnalyser {

    LexicalAnalyser lexer;
    vector<shared_ptr<Token>> tokens;
    int pos;

    vector<string> getVector(map<string,string> pattern);
    shared_ptr<Token> Match(vector<string> tokenTypes);
    shared_ptr<Token> Require(vector<string> tokenTypes);

public:

    SyntaxAnalyser(LexicalAnalyser lexer);
    Node ParseCode();
    void PrintTree();

    shared_ptr<Node> ParseExpression();

    vector<Token> ParseFunctionDefinition();

    FunctionNode ParseFunction();
};


#endif //LAB3_SYNTAXANALYSER_H
