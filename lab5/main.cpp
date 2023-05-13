#include "LexicalAnalyser.h"
#include "SyntaxAnalyser.h"
#include "SemanticAnalyser.h"
#include " Translator/Translator.h"

using namespace std;

int main() {

    LexicalAnalyser lexicalAnalyser;
    lexicalAnalyser.Analyse();

    SyntaxAnalyser syntaxAnalyser(lexicalAnalyser);

    shared_ptr<Node> root = syntaxAnalyser.ParseCode();

    //syntaxAnalyser.PrintNode(root);

    SemanticAnalyser semanticAnalyser;

    semanticAnalyser.Analyse(root);

    Translator translator(root);
    translator.Run();



    return 0;
}
