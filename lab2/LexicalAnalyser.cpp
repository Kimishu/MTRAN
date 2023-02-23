//
// Created by Kimihito on 21.02.2023.
//

#include "LexicalAnalyser.h"

LexicalAnalyser::LexicalAnalyser() {

}

void LexicalAnalyser::PrintTables() {
    cout << "\t\tVariables Table" << endl;
    for(pair<string,string> pr: variablesTable){

    }
}

vector<pair<int,string>> LexicalAnalyser::readFile(const string &path) {

    ifstream reader(path);

    vector<pair<int,string>> result;

    for(int i = 1; !reader.eof(); i++){
        string str;
        getline(reader,str);
        result.push_back(make_pair(i,str));
    }

    return result;
}

void LexicalAnalyser::Analyse() {

}
