//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_FUNCTIONNODE_H
#define LAB3_FUNCTIONNODE_H


#include <vector>
#include "Node.h"
#include "Token.h"

class FunctionNode: public Node{

public:
    Token function;
    vector<Token> parameters;
    shared_ptr<Node> body;

    FunctionNode(Token function, vector<Token> parameters, shared_ptr<Node> body);
    NodeType getType();
};


#endif //LAB3_FUNCTIONNODE_H
