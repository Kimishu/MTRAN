//
// Created by Kimihito on 24.04.2023.
//

#ifndef LAB3_SYNTAXANALYSER_H
#define LAB3_SYNTAXANALYSER_H

#include <list>
#include "Token/Token.h"
#include "LexicalAnalyser/LexicalAnalyser.h"

class SyntaxAnalyser {

    LexicalAnalyser lexer;
    list<Token> tokens;

public:
    SyntaxAnalyser(LexicalAnalyser lexer, list<Token> tokens);

    Token Match(list<string> tokenTypes);
    Token Require(list<string> tokenTypes);

    list<string> getList(map<string,string> pattern);

};


#endif //LAB3_SYNTAXANALYSER_H
