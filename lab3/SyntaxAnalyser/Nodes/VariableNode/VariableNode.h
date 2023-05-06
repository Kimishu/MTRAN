//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_VARIABLENODE_H
#define LAB3_VARIABLENODE_H


#include "Node.h"
#include "Token.h"

class VariableNode: public Node {

public:

    Token variable;

    VariableNode(Token variable);
    NodeType getType();
};


#endif //LAB3_VARIABLENODE_H
