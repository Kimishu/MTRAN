//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_VARIABLENODE_H
#define LAB3_VARIABLENODE_H


#include "Node.h"
#include "Token.h"

class VariableNode: Node {

    Token variable;

public:
    VariableNode(Token variable);

};


#endif //LAB3_VARIABLENODE_H
