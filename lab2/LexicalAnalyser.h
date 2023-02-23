//
// Created by Kimihito on 21.02.2023.
//

#ifndef LAB2_LEXICALANALYSER_H
#define LAB2_LEXICALANALYSER_H

#include <map>
#include <iostream>

using namespace std;

class LexicalAnalyser {
private:

    map<string,string> variablesPattern = {
            {"byte","Variable of byte type"},
            {"int","Variable of int type"},
            {"short","Variable of short type"},
            {"long","Variable of long type"},

            {"float","Variable of float type"},
            {"double","Variable of double type"},

            {"char","Variable of char type"},
            {"String","Variable of String type"},

            {"boolean","Variable of boolean type"},
    };

    map<string,string> keyWordsPattern = {
            {"if","is conditional statement"},
            {"for","is conditional statement"},
            {"do","is conditional statement"},
            {"while","is conditional statement"},

    };

    map<string,string> operatorsPattern = {
            {"+","is arithmetic operator"},
            {"+=","is arithmetic operator"},
            {"-","is arithmetic operator"},
            {"-=","is arithmetic operator"},
            {"/","is arithmetic operator"},
            {"/=","is arithmetic operator"},
            {"*","is arithmetic operator"},
            {"*=","is arithmetic operator"},

            {"==","is comparison operator"},
            {"!=","is comparison operator"},
    };


    map<string, string> variablesTable;
    map<string,string> keyWordsTable;
    map<string,string> operatorsTale;

    void FormTable();
public:
    LexicalAnalyser();

    void PrintTables();
};


#endif //LAB2_LEXICALANALYSER_H
