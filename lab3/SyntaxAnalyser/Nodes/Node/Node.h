//
// Created by Kimihito on 26.04.2023.
//

#ifndef LAB3_NODE_H
#define LAB3_NODE_H

enum NodeType {
    Binary,
    Case,
    For,
    FunctionCall,
    Function,
    If,
    KeyWord,
    Literal,
    Default,
    Return,
    Statements,
    Switch,
    UnaryOperation,
    Variable,
    VariableType,
    While
};

#include "string"
#include <memory>

using namespace std;

class Node {
public:
    virtual NodeType getType();
    Node();
};


#endif //LAB3_NODE_H
