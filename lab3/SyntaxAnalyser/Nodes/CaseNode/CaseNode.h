//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_CASENODE_H
#define LAB3_CASENODE_H


#include "Token.h"
#include "Node.h"

class CaseNode: public Node{

    Node literal;

public:
    CaseNode(Node literal);

};


#endif //LAB3_CASENODE_H
