//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_IFNODE_H
#define LAB3_IFNODE_H


#include "Node.h"

class IfNode: public Node {

public:

    shared_ptr<Node> condition;
    shared_ptr<Node> body;
    shared_ptr<Node> elseBody;


    IfNode(shared_ptr<Node> condition, shared_ptr<Node> body, shared_ptr<Node> elseBody);
    IfNode(shared_ptr<Node> condition, shared_ptr<Node> body);
    NodeType getType();
};


#endif //LAB3_IFNODE_H
