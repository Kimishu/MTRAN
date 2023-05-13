//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_RETURNNODE_H
#define LAB3_RETURNNODE_H


#include "Node.h"

class ReturnNode: public Node{

public:

    shared_ptr<Node> statement;

    ReturnNode(shared_ptr<Node> statement);
    NodeType getType();
};


#endif //LAB3_RETURNNODE_H
