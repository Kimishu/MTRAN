//
// Created by Kimihito on 03.05.2023.
//

#include "VariableTypeNode.h"

NodeType VariableTypeNode::getType() {
    return VariableType;
}

VariableTypeNode::VariableTypeNode(Token variable): variable(variable) {
}
