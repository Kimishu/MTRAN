//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_WHILENODE_H
#define LAB3_WHILENODE_H


#include "Node.h"

class WhileNode: public Node{

public:

    shared_ptr<Node> condition;
    shared_ptr<Node> body;

    WhileNode(shared_ptr<Node> condition, shared_ptr<Node> body);
    NodeType getType();
};


#endif //LAB3_WHILENODE_H
