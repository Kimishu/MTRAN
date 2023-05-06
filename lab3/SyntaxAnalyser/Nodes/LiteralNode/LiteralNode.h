//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_LITERALNODE_H
#define LAB3_LITERALNODE_H


#include "Node.h"
#include "Token.h"

class LiteralNode: public Node {

public:
    Token number;

    LiteralNode(Token number);
    NodeType getType();
};


#endif //LAB3_LITERALNODE_H
