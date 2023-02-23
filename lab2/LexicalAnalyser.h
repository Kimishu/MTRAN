//
// Created by Kimihito on 21.02.2023.
//

#ifndef LAB2_LEXICALANALYSER_H
#define LAB2_LEXICALANALYSER_H

#include <map>
#include <iostream>
#include <vector>
#include <fstream>

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
            //SELECTION STATEMENTS
            {"if","is a selection statement"},
            {"else","is a selection statement"},
            {"switch","is a selection statement"},
            {"case","is a selection statement"},
            {"deafult","is a selection statement"},
            //ITERATION STATEMENT
            {"for","is an iteration statement"},
            {"do","is an iteration statement"},
            {"while","is an iteration statement"},
            //JUMP STATEMENT
            {"return","is a jump statement"},
            {"break","is a jump statement"},
            {"continue","is a jump statement"},
            {"goto","is a jump statement"},
            //



    };

    map<string,string> operatorsPattern = {
            //ARITHMETIC OPERATORS
            {"+","is arithmetic operator"},
            {"+=","is arithmetic operator"},
            {"-","is arithmetic operator"},
            {"-=","is arithmetic operator"},
            {"/","is arithmetic operator"},
            {"/=","is arithmetic operator"},
            {"*","is arithmetic operator"},
            {"*=","is arithmetic operator"},
            //COMPARISON OPERATORS
            {"==","is comparison operator"},
            {"!=","is comparison operator"},
    };


    map<string, string> variablesTable;
    map<string,string> keyWordsTable;
    map<string,string> operatorsTale;

    vector<pair<int,string>> fileLines;

    vector<pair<int,string>> readFile(const string& path);

public:
    LexicalAnalyser();
    void Analyse();
    void PrintTables();
};


#endif //LAB2_LEXICALANALYSER_H
