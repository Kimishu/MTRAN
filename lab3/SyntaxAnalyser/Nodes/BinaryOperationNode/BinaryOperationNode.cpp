//
// Created by Kimihito on 03.05.2023.
//

#include "BinaryOperationNode.h"

BinaryOperationNode::BinaryOperationNode(Token binaryOperator, Node leftNode, Node rightNode): binaryOperator(binaryOperator),
                                                                                               leftNode(leftNode),
                                                                                               rightNode(rightNode){
}
