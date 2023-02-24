#include <iostream>
#include <algorithm>
#include "LexicalAnalyser.h"


using namespace std;

int main() {

    string s = "if";

    if (auto keywords = { "if", "for", "while" }; any_of(keywords.begin(), keywords.end(), [&s](const string& kw) { return s == kw; }))
    {
        cout << "Error! Token must not be a keyword\n";
    }

    LexicalAnalyser ls;

    ls.Analyse();

    cout << "Done" << endl;

    return 0;
}
