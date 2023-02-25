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
        bool variable = false;
        for(char& ch: line.second){

            if(!any_of(chars.begin(), chars.end(), [&ch](char& c){return ch == c;})) {

                word += ch;

                //continue;
            }

            //Variables Name
            if(variable){
                if((any_of(chars.begin(), chars.end(), [&ch](char& c){return ch == c;}) && !word.empty()) ||
                        (any_of(operatorsPattern.begin(), operatorsPattern.end(), [&ch](pair<const basic_string<char>, basic_string<char>> kw)
                        {return to_string(ch) == kw.first;}))){
                    variable = false;
                    variablesTable.insert(make_pair(word,"VAR"));
                    word.clear();
                }

                continue;
            }

            if(any_of(variablesTable.begin(), variablesTable.end(), [&word](
                    const pair<const basic_string<char>, basic_string<char>>& kw) { return word == kw.first; })){
                word.clear();
            }

            //Key Words
            if(any_of(keyWordsPattern.begin(), keyWordsPattern.end(), [&word](
                    const pair<const basic_string<char>, basic_string<char>>& kw) { return word == kw.first; })){

                map<string,string>::iterator iter;

                for(iter = keyWordsPattern.begin(); iter != keyWordsPattern.end(); iter++){
                    if(word == iter->first){
                        break;
                    }
                }

                keyWordsTable.insert(make_pair(word, iter->second));

                word.clear();
                continue;
            }

            //Variables Types
            if(any_of(variablesPattern.begin(), variablesPattern.end(), [&word](
                    const pair<const basic_string<char>, basic_string<char>>& kw) { return word == kw.first; })){

                map<string,string>::iterator iter;

                for(iter = variablesPattern.begin(); iter != variablesPattern.end(); iter++){
                    if(word == iter->first){
                        break;
                    }
                }

                variablesTypesTable.insert(make_pair(word, iter->second));

                word.clear();

                variable = true;

                continue;
            }

            //Operators
            if(any_of(operatorsPattern.begin(), operatorsPattern.end(), [&word](
                    const pair<const basic_string<char>, basic_string<char>>& kw) { return word == kw.first; })){

                map<string,string>::iterator iter;

                for(iter = operatorsPattern.begin(); iter != operatorsPattern.end(); iter++){
                    if(word == iter->first){
                        break;
                    }
                }

                operatorsTable.insert(make_pair(word, iter->second));

                word.clear();
                continue;
            }

//            if(ch == ' ' || any_of(operatorsPattern.begin(),operatorsPattern.end(),[&ch](
//                    const pair<const basic_string<char>, basic_string<char>>& kw) { return to_string(ch) == kw.first; }))

            //error

            //Constant table


        }

    }

    PrintTables("Variables types", variablesTypesTable);
    PrintTables("Variables", variablesTable);
    PrintTables("Key Words", keyWordsTable);
    PrintTables("Operators", operatorsTable);

}
