//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_SWITCHNODE_H
#define LAB3_SWITCHNODE_H


#include "Token.h"
#include "Node.h"

class SwitchNode: public Node{
public:

    Token variable;
    shared_ptr<Node> body;

    SwitchNode(Token variable, shared_ptr<Node> body);
    NodeType getType();
};


#endif //LAB3_SWITCHNODE_H
