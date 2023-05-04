//
// Created by Kimihito on 21.02.2023.
//

#include "LexicalAnalyser.h"

LexicalAnalyser::LexicalAnalyser() {
    defaultPath = R"(D:\Programs\bsuir\6sem\mtran\dev\MTRAN\lab3\input.java)";
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

            if(isChars && ch != ' ' && word.empty()){
                tokens.emplace_back(make_shared<Token>("Special symbol", string(1,ch)));
            }

            if(!isChars && !isOperator){
                word+=ch;
                if(!any_of(operatorsPattern.begin(), operatorsPattern.end(), [&ch](const pair<string,string>& pr){return string(1,*(&ch+1)) == pr.first;})) {
                    continue;
                }
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


            if (isVariable) {
                if(isdigit(word[0])){
                    errorsTable.insert(make_pair("input.java:"+to_string(line.first) + ":" + to_string(line.second.find(ch)-word.length()+1),"Variable mustnt starts with a digit!"));
                } else {
                    if (!any_of(variablesTable.begin(), variablesTable.end(),
                                [&word](const pair<string, string> &pr) { return word == pr.first; })) {
                        if (!any_of(keyWordsPattern.begin(), keyWordsPattern.end(),
                                    [&word](const pair<string, string> &pr) { return word == pr.first; }) &&
                            !any_of(variablesPattern.begin(), variablesPattern.end(),
                                    [&word](const pair<string, string> &pr) { return word == pr.first; })) {
                            variablesTable.insert(make_pair(word, "is a variable"));
                            tokens.emplace_back(make_shared<Token>("is a variable", word));
                            if(isChars && ch != ' '){
                                tokens.emplace_back(make_shared<Token>("Special symbol", string(1,ch)));
                            }
                        } else {
                            string type;
                            if (any_of(keyWordsPattern.begin(), keyWordsPattern.end(),
                                       [&word](const pair<string, string> &pr) { return word == pr.first; })) {
                                type = "keyword";
                            } else {
                                type = "data type";
                            }
                            errorsTable.insert(make_pair("input.java:" + to_string(line.first) + ":" +
                                                         to_string(line.second.find(ch) - word.length() + 1),
                                                         "Variable name mustn't be a " + type + "! Its forbidden!"));
                        }
                    } else {
                        errorsTable.insert(make_pair("input.java:" + to_string(line.first) + ":" +
                                                     to_string(line.second.find(ch) - word.length() + 1),
                                                     "Variable with this name already defined!"));
                    }
                }
                word.clear();

                isVariable = false;
                continue;
            }
            if (any_of(variablesTable.begin(), variablesTable.end(),
                       [&word](const pair<string, string> &pr) { return word == pr.first; })) {
                tokens.emplace_back(make_shared<Token>("is a variable", word));
                if(isChars && ch != ' '){
                    tokens.emplace_back(make_shared<Token>("Special symbol", string(1,ch)));
                }
                word.clear();
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
                tokens.emplace_back(make_shared<Token>(type, word));
                if(isChars && ch != ' '){
                    tokens.emplace_back(make_shared<Token>("Special symbol", string(1,ch)));
                }
                word.clear();
                isVariable = true;

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
                tokens.emplace_back(make_shared<Token>(type, word));
                if(isChars && ch != ' '){
                    tokens.emplace_back(make_shared<Token>("Special symbol", string(1,ch)));
                }
                word.clear();
                continue;
            }

            if(string type; any_of(operatorsPattern.begin(), operatorsPattern.end(), [&word, &type](const pair<string,string>& pr){
                if(word == pr.first){
                    type = pr.second;
                    return true;
                }
                return false;
            })){
                operatorsTable.insert(make_pair(word,type));
                tokens.emplace_back(make_shared<Token>(type, word));
                if(isChars && ch != ' '){
                    tokens.emplace_back(make_shared<Token>("Special symbol", string(1,ch)));
                }
                word.clear();
                continue;
            }

            if(regex_match(word, regex("([0-9]*\.[0-9]+|[0-9]+)")) && isChars){
                pair<string,string> pr;
                if(word == to_string(stoi(word))){
                    pr = make_pair(word,"Constant of int type");
                }
                else {
                    string number = to_string(stod(word));
                    while (word != number){
                        number.pop_back();
                    }
                    pr = make_pair(number,"Constant of double(float) type");
                }

                constantsTable.insert(pr);
                tokens.emplace_back(make_shared<Token>(pr.second, word));
                if(isChars && ch != ' '){
                    tokens.emplace_back(make_shared<Token>("Special symbol", string(1,ch)));
                }
                word.clear();
                continue;
            }

            errorsTable.insert(make_pair("input.java:"+to_string(line.first) + ":" + to_string(line.second.find(ch)-word.length()+1),"Unknown variable!"));
            word.clear();
        }
    }

}

void LexicalAnalyser::Print() {
    PrintTables("Variables types", variablesTypesTable);
    PrintTables("Variables", variablesTable);
    PrintTables("Key Words", keyWordsTable);
    PrintTables("Operators", operatorsTable);
    PrintTables("Constants", constantsTable);
    if(errorsTable.empty()){
        cout << "Code is clear! Nice work!" << endl;
    } else {
        PrintTables("Errors", errorsTable);
    }

    for(shared_ptr<Token>& token : tokens){
        cout << token.get()->value << endl;
    }
}
