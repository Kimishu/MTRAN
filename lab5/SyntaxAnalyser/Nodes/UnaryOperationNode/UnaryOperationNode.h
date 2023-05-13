//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_UNARYOPERATIONNODE_H
#define LAB3_UNARYOPERATIONNODE_H


#include "Node.h"
#include "Token.h"

class UnaryOperationNode: public Node {

public:
    Token unaryOperator;
    shared_ptr<Node> operand;

    UnaryOperationNode(Token unaryOperator, shared_ptr<Node> operand);
    NodeType getType();
};


#endif //LAB3_UNARYOPERATIONNODE_H
