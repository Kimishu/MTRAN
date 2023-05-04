//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_LITERALNODE_H
#define LAB3_LITERALNODE_H


#include "Node.h"
#include "Token.h"

class LiteralNode: Node {

    Token number;

public:
    LiteralNode(Token number);

};


#endif //LAB3_LITERALNODE_H
