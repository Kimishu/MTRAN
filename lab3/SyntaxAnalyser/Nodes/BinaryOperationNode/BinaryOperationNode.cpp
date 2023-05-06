//
// Created by Kimihito on 03.05.2023.
//

#include "BinaryOperationNode.h"

BinaryOperationNode::BinaryOperationNode(Token binaryOperator, shared_ptr<Node> leftNode, shared_ptr<Node> rightNode): binaryOperator(binaryOperator),
                                                                                               leftNode(leftNode),
                                                                                               rightNode(rightNode){
}

NodeType BinaryOperationNode::getType() {
    return Binary;
}
