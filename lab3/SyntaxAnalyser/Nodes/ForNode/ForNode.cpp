//
// Created by Kimihito on 03.05.2023.
//

#include "ForNode.h"

ForNode::ForNode(shared_ptr<Node> init, shared_ptr<Node> condition, shared_ptr<Node> step, shared_ptr<Node> body): init(init), condition(condition), step(step), body(body) {
}

NodeType ForNode::getType() {
    return For;
}
