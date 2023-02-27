//
// Created by Kimihito on 21.02.2023.
//

#include "LexicalAnalyser.h"

LexicalAnalyser::LexicalAnalyser() {
    defaultPath = R"(D:\Programs\bsuir\6sem\mtran\dev\MTRAN\lab2\input.java)";
}

[[maybe_unused]] LexicalAnalyser::LexicalAnalyser(const string &path) {
    defaultPath = path;
}

void LexicalAnalyser::PrintTables(const string& tableName, map<string,string>& table) {
    cout << "\t\t***"<< tableName <<" Table***" << endl;
    for(int i = 0; i<30; i++) cout << '=';
    cout << endl;
    for(pair<const basic_string<char>, basic_string<char>>& pr: table){
        cout << pr.first << "\t|\t" << pr.second << endl;
    }
    for(int i = 0; i<30; i++) cout << '=';
    cout << endl;
    cout << endl;
    cout << endl;
}

vector<pair<int,string>> LexicalAnalyser::readFile(const string &path) {

    ifstream reader(path);

    vector<pair<int,string>> result;

    for(int i = 1; !reader.eof(); i++){
        string str;
        getline(reader,str);
        result.emplace_back(i,str);
    }

    return result;
}

void LexicalAnalyser::Analyse() {
    fileLines = readFile(defaultPath);

    for(pair<int,string>& line: fileLines){

        string word;

        bool isVariable = false;
        for(char& ch : line.second){
            bool isChars = any_of(chars.begin(), chars.end(), [&ch](char& c){return ch == c;});
            bool isOperator = any_of(operatorsPattern.begin(), operatorsPattern.end(), [&ch](const pair<string,string>& pr){return string(1,ch) == pr.first;});

            if(!isChars && !isOperator){
                word+=ch;
                if(!any_of(operatorsPattern.begin(), operatorsPattern.end(), [&ch](const pair<string,string>& pr){return string(1,*(&ch+1)) == pr.first;}))
                    continue;
            }
            if(isOperator) {
                word+=ch;
                if(!any_of(operatorsPattern.begin(), operatorsPattern.end(), [&ch](const pair<string,string>& pr){return string(1,*(&ch+1)) == pr.first;})
                && !any_of(chars.begin(), chars.end(), [&ch](char& c){return *(&ch+1) == c;})) {
                    isOperator = false;
                } else{
                    continue;
                }
            }
            if(word.empty()){
                continue;
            }

            if (string type; any_of(variablesPattern.begin(), variablesPattern.end(), [&word, &type](
                    const pair<string, string> &kw) {
                if (word == kw.first) {
                    type = kw.second;
                    return true;
                }
                return false;
            })) {
                variablesTypesTable.insert(make_pair(word, type));
                word.clear();
                isVariable = true;

                continue;
            }

            if (isVariable) {
                if (!any_of(variablesTable.begin(), variablesTable.end(),
                            [&word](const pair<string, string> &pr) { return word == pr.first; })) {
                    variablesTable.insert(make_pair(word, "is a variable"));
                    word.clear();
                    isVariable = false;
                    continue;
                }
            }
            if (any_of(variablesTable.begin(), variablesTable.end(),
                       [&word](const pair<string, string> &pr) { return word == pr.first; })) {
                word.clear();
                continue;
            }

            if(string type; any_of(keyWordsPattern.begin(), keyWordsPattern.end(), [&word, &type](const pair<string,string>& pr){
                if(word == pr.first){
                    type = pr.second;
                    return true;
                }
                return false;
            })){
                keyWordsTable.insert(make_pair(word,type));
                word.clear();
                continue;
            }

            if(any_of(operatorsPattern.begin(), operatorsPattern.end(), [&word](const pair<string,string>& pr){return word == pr.first;})){
                operatorsTable.insert(make_pair(word,"operator"));
                word.clear();
                continue;
            }
        }
    }

    PrintTables("Variables types", variablesTypesTable);
    PrintTables("Variables", variablesTable);
    PrintTables("Key Words", keyWordsTable);
    PrintTables("Operators", operatorsTable);

}

bool LexicalAnalyser::isNum(string &word) {
    char * pEnd = NULL;
    double d = strtod(word.c_str(), &pEnd);

    return *pEnd;
}
