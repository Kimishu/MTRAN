//
// Created by Kimihito on 05.05.2023.
//

#include "CaseNode.h"

CaseNode::CaseNode(shared_ptr<Node> literal): literal(literal) {
}

NodeType CaseNode::getType() {
    return Case;
}
