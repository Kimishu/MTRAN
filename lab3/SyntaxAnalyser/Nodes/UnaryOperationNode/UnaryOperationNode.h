//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_UNARYOPERATIONNODE_H
#define LAB3_UNARYOPERATIONNODE_H


#include "Node.h"
#include "Token.h"

class UnaryOperationNode: Node {
    Token unaryOperator;
    Node operand;

public:
    UnaryOperationNode(Token unaryOperator, Node operand);
};


#endif //LAB3_UNARYOPERATIONNODE_H
