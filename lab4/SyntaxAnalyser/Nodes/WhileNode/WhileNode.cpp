//
// Created by Kimihito on 05.05.2023.
//

#include "WhileNode.h"

WhileNode::WhileNode(shared_ptr<Node> condition, shared_ptr<Node> body): condition(condition), body(body) {
}

NodeType WhileNode::getType() {
    return While;
}
