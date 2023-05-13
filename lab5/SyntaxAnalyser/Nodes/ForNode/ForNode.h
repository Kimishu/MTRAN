//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_FORNODE_H
#define LAB3_FORNODE_H


#include "Node.h"

class ForNode: public Node {

public:
    shared_ptr<Node> init;
    shared_ptr<Node> condition;
    shared_ptr<Node> step;

    shared_ptr<Node> body;


    ForNode(shared_ptr<Node> init, shared_ptr<Node> condition, shared_ptr<Node> step, shared_ptr<Node> body);
    NodeType getType();
};


#endif //LAB3_FORNODE_H
