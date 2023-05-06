#include "LexicalAnalyser.h"
#include "SyntaxAnalyser.h"

using namespace std;

class A{

public:
    virtual NodeType getType(){
        return Default; // 8
    }
};

class B:  public A{

    int a = 5;

public:
    NodeType getType() {
        return Statements; // 10
    }
};

shared_ptr<A> foo(){
    return make_shared<B>();
}

shared_ptr<A> moo(shared_ptr<B> boo){
    return boo;
}

int main() {

    LexicalAnalyser lexer;
    lexer.Analyse();

    SyntaxAnalyser parser(lexer);

    auto root = parser.ParseCode();

    parser.PrintNode(root);


   return 0;
}
