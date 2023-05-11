//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_VARIABLETYPENODE_H
#define LAB3_VARIABLETYPENODE_H


#include "Node.h"
#include "Token.h"

class VariableTypeNode: public Node {
public:
    Token variable;
    VariableTypeNode(Token variable);
    NodeType getType();
};


#endif //LAB3_VARIABLETYPENODE_H
