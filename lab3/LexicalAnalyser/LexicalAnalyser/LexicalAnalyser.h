//
// Created by Kimihito on 21.02.2023.
//

#ifndef LAB2_LEXICALANALYSER_H
#define LAB2_LEXICALANALYSER_H

#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <regex>
#include "Token.h"

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
            {"default","is a selection statement"},
            //ITERATION STATEMENT
            {"for","is an iteration statement"},
            {"do","is an iteration statement"},
            {"while","is an iteration statement"},
            //JUMP STATEMENT
            {"return","is a jump statement"},
            {"break","is a jump statement"},
            {"continue","is a jump statement"},
            {"goto","is a jump statement"},
            //PRIVACY STATEMENT
    };

    map<string,string> operatorsPattern = {
            //ARITHMETIC OPERATORS
            {"+","is arithmetic operator"},
            {"++","is arithmetic operator"},
            {"+=","is arithmetic operator"},
            {"-","is arithmetic operator"},
            {"--","is arithmetic operator"},
            {"-=","is arithmetic operator"},
            {"/","is arithmetic operator"},
            {"/=","is arithmetic operator"},
            {"*","is arithmetic operator"},
            {"*=","is arithmetic operator"},
            {"=","is arithmetic operator"},
            //COMPARISON OPERATORS
            {"==","is comparison operator"},
            {"!=","is comparison operator"},
            {"<","is comparison operator"},
            {">","is comparison operator"},
            {"<=","is comparison operator"},
            {">=","is comparison operator"},
    };

    vector<char> chars = {
            ' ',
            '\n',
            '{',
            '}',
            ';',
            '(',
            ')',
            '\t',
            '\r',
            '#',
            ',',
            ':'};


    vector<pair<int,string>> fileLines;
    string defaultPath;

    static vector<pair<int,string>> readFile(const string& path);

public:

    map<string, string> variablesTypesTable;
    map<string, string> variablesTable;
    map<string,string> keyWordsTable;
    map<string,string> operatorsTable;
    map<string,string> constantsTable;
    map<string,string> errorsTable;

    vector<shared_ptr<Token>> tokens;


    LexicalAnalyser();
    [[maybe_unused]] explicit LexicalAnalyser(const string& path);
    void Analyse();
    static void PrintTables(const string& tableName, map<string,string>& table);
};


#endif //LAB2_LEXICALANALYSER_H
