//
// Created by Kimihito on 24.04.2023.
//

#ifndef LAB3_SYNTAXANALYSER_H
#define LAB3_SYNTAXANALYSER_H

#include "Token.h"
#include "LexicalAnalyser.h"
#include "Node.h"

class SyntaxAnalyser {

    unique_ptr<LexicalAnalyser> lexer = nullptr;
    vector<Token> tokens;
    int pos;

public:
    SyntaxAnalyser(LexicalAnalyser lexer, vector<Token> tokens);

    vector<string> getVector(map<string,string> pattern);

    unique_ptr<Token> Match(vector<string> tokenTypes);
    unique_ptr<Token> Require(vector<string> tokenTypes);

    Node ParseCode();

};


#endif //LAB3_SYNTAXANALYSER_H
