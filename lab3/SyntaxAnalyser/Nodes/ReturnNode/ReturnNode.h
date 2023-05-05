//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_RETURNNODE_H
#define LAB3_RETURNNODE_H


#include "Node.h"

class ReturnNode: public Node{

    Node statement;

public:
    ReturnNode(Node statement);

};


#endif //LAB3_RETURNNODE_H
