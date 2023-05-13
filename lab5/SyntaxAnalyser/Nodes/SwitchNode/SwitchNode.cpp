//
// Created by Kimihito on 05.05.2023.
//

#include "SwitchNode.h"

SwitchNode::SwitchNode(Token variable, shared_ptr<Node> body): variable(variable), body(body) {
}

NodeType SwitchNode::getType() {
    return Switch;
}
