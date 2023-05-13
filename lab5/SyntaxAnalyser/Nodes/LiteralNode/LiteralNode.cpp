//
// Created by Kimihito on 03.05.2023.
//

#include "LiteralNode.h"

LiteralNode::LiteralNode(Token literal): literal(literal) {
}

NodeType LiteralNode::getType() {
    return Literal;
}
