//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_SWITCHNODE_H
#define LAB3_SWITCHNODE_H


#include "Token.h"
#include "Node.h"

class SwitchNode: public Node{

    Token variable;
    Node body;

public:
    SwitchNode(Token variable, Node body);
};


#endif //LAB3_SWITCHNODE_H
