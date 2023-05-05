#include "LexicalAnalyser.h"
#include "SyntaxAnalyser.h"

using namespace std;

int main() {

   LexicalAnalyser lexer;
   lexer.Analyse();

   SyntaxAnalyser parser(lexer);


   return 0;
}
