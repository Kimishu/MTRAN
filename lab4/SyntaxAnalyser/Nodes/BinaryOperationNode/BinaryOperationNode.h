//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_BINARYOPERATIONNODE_H
#define LAB3_BINARYOPERATIONNODE_H


#include "Node.h"
#include "Token.h"

class BinaryOperationNode: public Node {

public:
    Token binaryOperator;

    shared_ptr<Node> leftNode;
    shared_ptr<Node> rightNode;

    BinaryOperationNode(Token binaryOperator, shared_ptr<Node> leftNode, shared_ptr<Node> rightNode);

    NodeType getType();

};


#endif //LAB3_BINARYOPERATIONNODE_H
