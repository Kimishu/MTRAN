#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    string s = "if";

    if (auto keywords = { "if", "for", "while" }; any_of(keywords.begin(), keywords.end(), [&s](const string& kw) { return s == kw; }))
    {
        cout << "Error! Token must not be a keyword\n";
    }

    unsigned long l = -1;

    cout << l << endl;

    return 0;
}
