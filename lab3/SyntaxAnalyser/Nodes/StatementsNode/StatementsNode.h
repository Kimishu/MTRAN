//
// Created by Kimihito on 26.04.2023.
//

#ifndef LAB3_STATEMENTSNODE_H
#define LAB3_STATEMENTSNODE_H

#include "Node.h"
#include <iostream>
#include <list>

using namespace std;

// The root node
class StatementsNode: public Node {

    list<Node> nodes;

public:
    void AddNode(Node);
};


#endif //LAB3_STATEMENTSNODE_H
