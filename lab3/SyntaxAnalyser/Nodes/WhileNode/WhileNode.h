//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_WHILENODE_H
#define LAB3_WHILENODE_H


#include "Node.h"

class WhileNode: public Node{

    Node condition;
    Node body;

public:
    WhileNode(Node condition, Node body);
};


#endif //LAB3_WHILENODE_H
