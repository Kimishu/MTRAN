//
// Created by Kimihito on 07.05.2023.
//

#ifndef LAB4_SEMANTICANALYSER_H
#define LAB4_SEMANTICANALYSER_H


#include "Node.h"
#include "FunctionNode.h"

class SemanticAnalyser {

    vector<shared_ptr<FunctionNode>> functions;
    vector<string> numberTypes = {"int","double","float","byte","long","short"};
    vector<string> otherTypes = {"String","boolean","char"};

    string AnalyseNode(shared_ptr<Node> node);

public:
    SemanticAnalyser();

    void Analyse(shared_ptr<Node> node);

};


#endif //LAB4_SEMANTICANALYSER_H
