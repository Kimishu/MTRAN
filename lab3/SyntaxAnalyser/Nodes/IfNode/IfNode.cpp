//
// Created by Kimihito on 03.05.2023.
//

#include "IfNode.h"

IfNode::IfNode(Node condition, Node body, Node elseBody): condition(condition), body(body), elseBody(elseBody) {
}

IfNode::IfNode(Node condition, Node body): condition(condition), body(body) {
}
