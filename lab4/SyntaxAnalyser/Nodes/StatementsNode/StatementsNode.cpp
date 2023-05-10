//
// Created by Kimihito on 26.04.2023.
//

#include "StatementsNode.h"

void StatementsNode::AddNode(shared_ptr<Node> node) {
    nodes.push_back(node);
}

NodeType StatementsNode::getType() {
    return Statements;
}
