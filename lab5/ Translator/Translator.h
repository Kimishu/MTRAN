//
// Created by Kimihito on 13.05.2023.
//

#ifndef LAB5_TRANSLATOR_H
#define LAB5_TRANSLATOR_H


#include "Node.h"

class Translator {

    shared_ptr<Node> root;
    void Execute();
public:
    void Run();
    Translator(shared_ptr<Node> node);
};


#endif //LAB5_TRANSLATOR_H
