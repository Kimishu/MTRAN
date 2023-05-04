//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_FUNCTIONNODE_H
#define LAB3_FUNCTIONNODE_H


#include <vector>
#include "Node.h"
#include "Token.h"

class FunctionNode: public Node{

    Token function;
    vector<Token> parameters;
    Node body;

public:
    FunctionNode(Token function, vector<Token> parameters, Node body);

};


#endif //LAB3_FUNCTIONNODE_H
