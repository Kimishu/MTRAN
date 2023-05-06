//
// Created by Kimihito on 05.05.2023.
//

#include "ReturnNode.h"

ReturnNode::ReturnNode(shared_ptr<Node> statement): statement(statement) {
}

NodeType ReturnNode::getType() {
    return Return;
}
