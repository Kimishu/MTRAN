//
// Created by Kimihito on 03.05.2023.
//

#include "VariableNode.h"

VariableNode::VariableNode(Token variable) : variable(variable) {

}

NodeType VariableNode::getType() {
    return Variable;
}
