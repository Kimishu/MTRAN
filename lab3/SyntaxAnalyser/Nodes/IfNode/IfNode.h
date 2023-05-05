//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_IFNODE_H
#define LAB3_IFNODE_H


#include "Node.h"

class IfNode: public Node {

    Node condition;
    Node body;
    Node elseBody;

public:

    IfNode(Node condition, Node body, Node elseBody);
    IfNode(Node condition, Node body);

};


#endif //LAB3_IFNODE_H
