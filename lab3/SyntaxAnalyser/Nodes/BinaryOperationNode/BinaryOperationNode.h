//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_BINARYOPERATIONNODE_H
#define LAB3_BINARYOPERATIONNODE_H


#include "Node.h"
#include "Token.h"

class BinaryOperationNode: Node {

    Token binaryOperator;

    Node leftNode;
    Node rightNode;

public:
    BinaryOperationNode(Token binaryOperator, Node leftNode, Node rightNode);

};


#endif //LAB3_BINARYOPERATIONNODE_H
