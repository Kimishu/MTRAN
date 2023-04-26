//
// Created by Kimihito on 24.04.2023.
//

#ifndef LAB3_SYNTAXANALYSER_H
#define LAB3_SYNTAXANALYSER_H

#include <list>
#include "Token.h"
#include "LexicalAnalyser.h"

class SyntaxAnalyser {

    LexicalAnalyser lexer;
    list<Token> tokens;
    int pos;

public:
    SyntaxAnalyser(LexicalAnalyser lexer, list<Token> tokens);

    Token Match(list<string> tokenTypes);
    Token Require(list<string> tokenTypes);

    list<string> getList(map<string,string> pattern);

};


#endif //LAB3_SYNTAXANALYSER_H
