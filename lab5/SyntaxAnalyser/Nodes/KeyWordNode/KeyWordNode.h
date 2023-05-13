//
// Created by Kimihito on 03.05.2023.
//

#ifndef LAB3_KEYWORDNODE_H
#define LAB3_KEYWORDNODE_H


#include "Node.h"
#include "Token.h"

class KeyWordNode: public Node {

public:
    Token keyWord;

    KeyWordNode(Token keyWord);
    NodeType getType();
};


#endif //LAB3_KEYWORDNODE_H
