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
vector<char> operators = {
        '+',
        '-',
        '=',
        '*',
        '/'
};

bool isNum(string &word) {
    char * pEnd = NULL;
    double d = strtod(word.c_str(), &pEnd);

    return *pEnd;
}

int main() {

//    string str = "int a=5;";
//    string word;
//
//    for(char& ch: str) {
//        bool notChars = !any_of(chars.begin(), chars.end(), [&ch](char &c) { return ch == c; });
//
//    }

    LexicalAnalyser ls;
    ls.Analyse();

    return 0;
}
