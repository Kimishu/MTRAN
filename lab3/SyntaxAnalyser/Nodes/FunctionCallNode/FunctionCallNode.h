//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_FUNCTIONCALLNODE_H
#define LAB3_FUNCTIONCALLNODE_H


#include <vector>
#include "Node.h"
#include "Token.h"

class FunctionCallNode: public Node{

public:
    Token function;
    vector<shared_ptr<Node>> parameters;

    FunctionCallNode(Token function, vector<shared_ptr<Node>> parameters);
    NodeType getType();
};


#endif //LAB3_FUNCTIONCALLNODE_H
