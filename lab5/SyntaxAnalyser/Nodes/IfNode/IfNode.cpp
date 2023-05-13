//
// Created by Kimihito on 03.05.2023.
//

#include "IfNode.h"

IfNode::IfNode(shared_ptr<Node> condition, shared_ptr<Node> body, shared_ptr<Node> elseBody): condition(condition), body(body), elseBody(elseBody) {
}

IfNode::IfNode(shared_ptr<Node> condition, shared_ptr<Node> body): condition(condition), body(body) {
}

NodeType IfNode::getType() {
    return If;
}
