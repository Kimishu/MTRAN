#include <iostream>
#include <algorithm>
#include <sstream>
#include "LexicalAnalyser.h"
#include <map>


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

bool isNum(string &word) {
    char * pEnd = NULL;
    double d = strtod(word.c_str(), &pEnd);

    return *pEnd;
}

int main() {

//    string tmp = "int factorial = 5; int factorial = 6;";
//
//    vector<string> types;
//    vector<string> vars;
//    vector<string> operators;
//    vector<string> constants;
//
//    bool variable = false;
//
//    string word;
//
//    for(char& ch: tmp){
//
//        if(!any_of(chars.begin(), chars.end(), [&ch](char& c){return ch == c;})){
//            word+= ch;
//        }
//
//        if(variable){
//            if(any_of(chars.begin(), chars.end(), [&ch](char& c){return ch == c;}) && !word.empty()){
//                vars.push_back(word);
//                word.clear();
//                variable = false;
//                continue;
//            }
//
//            if(any_of(vars.begin(), vars.end(),[&word](string& w){return word == w;})){
//                cout << "ERROR, variable with the same name was already defined!" << endl;
//                variable = false;
//                word.clear();
//                continue;
//            }
//        }
//
//        if(word == "int"){
//            types.push_back(word);
//            word.clear();
//            variable = true;
//            continue;
//        }
//
//        //operators
//        if(ch == ' ' && word == "="){
//            operators.push_back(word);
//            word.clear();
//            continue;
//        }
//
//        stringstream temp(word);
//        if(temp.good() && !word.empty() && (ch == ' ')|| ch == ';'){
//            constants.push_back(word);
//            word.clear();
//            continue;
//        }
//
//
//
//    }

//    LexicalAnalyser ls;
//
//    ls.Analyse();

    map<string,string> opers = {
            {"-", "aaa"}
    };

    char ch = '-';

    if(string character = string(1,ch); any_of(opers.begin(), opers.end(),[&character](
            pair<const basic_string<char>, basic_string<char>> pr){return character == pr.first;})){
        cout << 'l' << endl;
    }


    cout << endl;

    return 0;
}
