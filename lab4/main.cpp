#include "LexicalAnalyser.h"
#include "SyntaxAnalyser.h"
#include "SemanticAnalyser.h"

using namespace std;

int main() {

    LexicalAnalyser lexicalAnalyser;
    lexicalAnalyser.Analyse();

    SyntaxAnalyser syntaxAnalyser(lexicalAnalyser);

    shared_ptr<Node> root = syntaxAnalyser.ParseCode();

    //parser.PrintNode(root);

    SemanticAnalyser semanticAnalyser;

    semanticAnalyser.Analyse(root);

    return 0;
}
