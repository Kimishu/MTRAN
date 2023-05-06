//
// Created by Kimihito on 03.05.2023.
//

#include "LiteralNode.h"

LiteralNode::LiteralNode(Token number): number(number) {
}

NodeType LiteralNode::getType() {
    return Literal;
}
