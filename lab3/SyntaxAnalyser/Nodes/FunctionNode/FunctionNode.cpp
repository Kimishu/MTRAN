//
// Created by Kimihito on 05.05.2023.
//

#include "FunctionNode.h"

FunctionNode::FunctionNode(Token function, vector<Token> parameters, shared_ptr<Node> body): function(function), parameters(parameters),
                                                                                 body(body) {
}

NodeType FunctionNode::getType() {
    return Function;
}
