//
// Created by Kimihito on 05.05.2023.
//

#include "FunctionCallNode.h"

FunctionCallNode::FunctionCallNode(Token function, vector<shared_ptr<Node>> parameters): function(function), parameters(parameters) {
}

NodeType FunctionCallNode::getType() {
    return FunctionCall;
}
