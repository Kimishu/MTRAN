#include "LexicalAnalyser.h"
#include "SyntaxAnalyser.h"

using namespace std;


class A{


};

class B: public A{
    int a;

public:
    B(int a): a(a){}
};

shared_ptr<A> foo(){


    return make_shared<B>(5);
}

int main() {

   LexicalAnalyser lexer;
   lexer.Analyse();

   SyntaxAnalyser parser(lexer);

   StatementsNode root = parser.ParseCode();

   auto a = foo();

   shared_ptr<B> b = dynamic_pointer_cast<B>(a);


   return 0;
}
