#include <iostream>
#include <algorithm>
#include "LexicalAnalyser.h"


using namespace std;

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
        '#'};

int main() {

//    string s = "if";
//
//    if (auto keywords = { "if", "for", "while" }; any_of(keywords.begin(), keywords.end(), [&s](const string& kw) { return s == kw; }))
//    {
//        cout << "Error! Token must not be a keyword\n";
//    }

//    LexicalAnalyser ls;
//
//    ls.Analyse();
//
//    cout << "\nDone" << endl;

    string tmp = "int factorial = 5++;";

    int a = 5;

    vector<string> types;
    vector<string> vars;
    vector<string> operators;
    bool variable = false;
    string word;
    for(char& ch: tmp){

        if(!any_of(chars.begin(), chars.end(), [&ch](char& c){return ch == c;})){
            word+= ch;
        }

        if(variable){
            if(any_of(chars.begin(), chars.end(), [&ch](char& c){return ch == c;})){

            }
        }

        if(word == "int"){
            types.push_back(word);
            word.clear();
            variable = true;
            continue;
        }

    }

    return 0;
}
