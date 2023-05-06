//
// Created by Kimihito on 26.04.2023.
//

#ifndef LAB3_STATEMENTSNODE_H
#define LAB3_STATEMENTSNODE_H

#include "Node.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// The root node
class StatementsNode: public Node {

public:
    vector<shared_ptr<Node>> nodes;
    void AddNode(shared_ptr<Node>);
    NodeType getType();
};


#endif //LAB3_STATEMENTSNODE_H
