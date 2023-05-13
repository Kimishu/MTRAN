//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_CASENODE_H
#define LAB3_CASENODE_H


#include "Token.h"
#include "Node.h"

class CaseNode: public Node{

public:
    shared_ptr<Node> literal;

    CaseNode(shared_ptr<Node> literal);
    NodeType getType();
};


#endif //LAB3_CASENODE_H
