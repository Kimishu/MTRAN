//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_FORNODE_H
#define LAB3_FORNODE_H


#include "Node.h"

class ForNode: public Node {

    Node init;
    Node condition;
    Node step;

    Node body;

public:

    ForNode(Node init, Node condition, Node step, Node body);

};


#endif //LAB3_FORNODE_H
