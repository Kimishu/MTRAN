//
// Created by Kimihito on 03.05.2023.
//

#include "UnaryOperationNode.h"

UnaryOperationNode::UnaryOperationNode(Token unaryOperator, shared_ptr<Node> operand): unaryOperator(unaryOperator), operand(operand) {
}

NodeType UnaryOperationNode::getType() {
    return UnaryOperation;
}
