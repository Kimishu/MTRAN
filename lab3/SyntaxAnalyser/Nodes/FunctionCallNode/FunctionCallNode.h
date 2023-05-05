//
// Created by Kimihito on 05.05.2023.
//

#ifndef LAB3_FUNCTIONCALLNODE_H
#define LAB3_FUNCTIONCALLNODE_H


#include <vector>
#include "Node.h"
#include "Token.h"

class FunctionCallNode: public Node{

    Token function;
    vector<Node> parameters;

public:
    FunctionCallNode(Token function, vector<Node> parameters);

};


#endif //LAB3_FUNCTIONCALLNODE_H
