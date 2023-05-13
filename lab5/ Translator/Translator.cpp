//
// Created by Kimihito on 13.05.2023.
//

#include <vector>
#include "Translator.h"
#include "VariableNode.h"
#include "SwitchNode.h"
#include "IfNode.h"
#include "SwitchNode.h"
#include "ForNode.h"
#include "WhileNode.h"
#include "StatementsNode.h"
#include "UnaryOperationNode.h"
#include "BinaryOperationNode.h"
#include "FunctionCallNode.h"
#include "FunctionNode.h"
#include <algorithm>
#include "LiteralNode.h"
#include "CaseNode.h"
#include "VariableTypeNode.h"


Translator::Translator(shared_ptr<Node> node): root(node) {
}

void Translator::Run() {

    if (root == nullptr) {
        return;
    }

    if (root->getType() == Statements) {
        shared_ptr<StatementsNode> statementsNode = dynamic_pointer_cast<StatementsNode>(root);

        for (shared_ptr<Node> &node: statementsNode->nodes) {

        }
    }

    if (root->getType() == Function) {
        shared_ptr<FunctionNode> functionNode = dynamic_pointer_cast<FunctionNode>(root);

        for (Token &parameter: functionNode->parameters) {

        }

    }

    if (root->getType() == While) {
        shared_ptr<WhileNode> whileNode = dynamic_pointer_cast<WhileNode>(root);

    }

    if (root->getType() == If) {
        shared_ptr<IfNode> ifNode = dynamic_pointer_cast<IfNode>(root);
    }

    if (root->getType() == For) {
        shared_ptr<ForNode> forNode = dynamic_pointer_cast<ForNode>(root);

//        AnalyseForNode(forNode->init,0);
//        AnalyseForNode(forNode->condition,1);
//        AnalyseForNode(forNode->step,2);
//        Analyse(forNode->body);
    }

    if (root->getType() == FunctionCall) {
        shared_ptr<FunctionCallNode> functionCallNode = dynamic_pointer_cast<FunctionCallNode>(root);


//            "Unknown function " << functionCallNode->function.value << " detected";
//            exit(EXIT_FAILURE);

        for (shared_ptr<Node> &node: functionCallNode->parameters) {
        }

    }

    if (root->getType() == Switch) {
        shared_ptr<SwitchNode> switchNode = dynamic_pointer_cast<SwitchNode>(root);
    }

    if (root->getType() == Case) {
        shared_ptr<CaseNode> caseNode = dynamic_pointer_cast<CaseNode>(root);
    }

    if (root->getType() == Binary) {
        vector<string> numberTypes = {"int", "double", "float", "byte", "long", "short"};
        vector<string> otherTypes = {"String", "boolean", "char"};

        shared_ptr<BinaryOperationNode> binaryOperationNode = dynamic_pointer_cast<BinaryOperationNode>(root);
        if (binaryOperationNode->leftNode->getType() == Variable) {
            shared_ptr<VariableNode> variableNode = dynamic_pointer_cast<VariableNode>(binaryOperationNode->leftNode);
            // LITERAL
            if (binaryOperationNode->rightNode->getType() == Literal) {
                shared_ptr<LiteralNode> literalNode = dynamic_pointer_cast<LiteralNode>(
                        binaryOperationNode->rightNode);
                if (variableNode->variable.type != literalNode->literal.type) {
                    if ((any_of(numberTypes.begin(), numberTypes.end(),
                                [&variableNode](const string &type) { return variableNode->variable.type == type; })
                         && any_of(otherTypes.begin(), otherTypes.end(), [&literalNode](const string &type) {
                        return literalNode->literal.type == type;
                    }))
                        || (any_of(otherTypes.begin(), otherTypes.end(), [&variableNode](const string &type) {
                        return variableNode->variable.type == type;
                    })
                            && any_of(numberTypes.begin(), numberTypes.end(), [&literalNode](const string &type) {
                        return literalNode->literal.type == type;
                    }))) {

                    }
                }
            }
            // VARIABLE
            if (binaryOperationNode->rightNode->getType() == Variable) {
                shared_ptr<VariableNode> secondNode = dynamic_pointer_cast<VariableNode>(
                        binaryOperationNode->rightNode);
                if (variableNode->variable.type != secondNode->variable.type) {
                    vector<string> numberTypes = {"int", "double", "float", "byte", "long", "short"};
                    vector<string> otherTypes = {"String", "boolean", "char"};

                    if ((any_of(numberTypes.begin(), numberTypes.end(),
                                [&variableNode](const string &type) { return variableNode->variable.type == type; })
                         && any_of(otherTypes.begin(), otherTypes.end(),
                                   [&secondNode](const string &type) { return secondNode->variable.type == type; }))
                        || (any_of(otherTypes.begin(), otherTypes.end(), [&variableNode](const string &type) {
                        return variableNode->variable.type == type;
                    })
                            && any_of(numberTypes.begin(), numberTypes.end(), [&secondNode](const string &type) {
                        return secondNode->variable.type == type;
                    }))) {

                    }
                }
            }
            if (binaryOperationNode->rightNode->getType() == Binary ||
                binaryOperationNode->rightNode->getType() == UnaryOperation) {
                string rightNodeType = "default";
                if (variableNode->variable.type != rightNodeType) {
                    if (!any_of(numberTypes.begin(), numberTypes.end(), [&variableNode](const string &type) {
                        return variableNode->variable.type == type;
                    }) || !any_of(numberTypes.begin(), numberTypes.end(), [&rightNodeType](const string &type) {
                        return rightNodeType == type;
                    })) {

                    }
                }
            }
        }
        if (binaryOperationNode->leftNode->getType() == VariableType) {
            shared_ptr<VariableTypeNode> variableNode = dynamic_pointer_cast<VariableTypeNode>(
                    binaryOperationNode->leftNode);
            // LITERAL
            if (binaryOperationNode->rightNode->getType() == Literal) {
                shared_ptr<LiteralNode> literalNode = dynamic_pointer_cast<LiteralNode>(
                        binaryOperationNode->rightNode);
                if (variableNode->variable.type != literalNode->literal.type) {
                    if ((any_of(numberTypes.begin(), numberTypes.end(),
                                [&variableNode](const string &type) { return variableNode->variable.type == type; })
                         && any_of(otherTypes.begin(), otherTypes.end(), [&literalNode](const string &type) {
                        return literalNode->literal.type == type;
                    }))
                        || (any_of(otherTypes.begin(), otherTypes.end(), [&variableNode](const string &type) {
                        return variableNode->variable.type == type;
                    })
                            && any_of(numberTypes.begin(), numberTypes.end(), [&literalNode](const string &type) {
                        return literalNode->literal.type == type;
                    }))) {

                    }
                }
            }
            // VARIABLE
            if (binaryOperationNode->rightNode->getType() == Variable) {
                shared_ptr<VariableNode> secondNode = dynamic_pointer_cast<VariableNode>(
                        binaryOperationNode->rightNode);
                if (variableNode->variable.type != secondNode->variable.type) {
                    vector<string> numberTypes = {"int", "double", "float", "byte", "long", "short"};
                    vector<string> otherTypes = {"String", "boolean", "char"};

                    if ((any_of(numberTypes.begin(), numberTypes.end(),
                                [&variableNode](const string &type) { return variableNode->variable.type == type; })
                         && any_of(otherTypes.begin(), otherTypes.end(),
                                   [&secondNode](const string &type) { return secondNode->variable.type == type; }))
                        || (any_of(otherTypes.begin(), otherTypes.end(), [&variableNode](const string &type) {
                        return variableNode->variable.type == type;
                    })
                            && any_of(numberTypes.begin(), numberTypes.end(), [&secondNode](const string &type) {
                        return secondNode->variable.type == type;
                    }))) {
                    }
                }
            }
            if (binaryOperationNode->rightNode->getType() == Binary ||
                binaryOperationNode->rightNode->getType() == UnaryOperation) {
                string rightNodeType = "default";
                if (variableNode->variable.type != rightNodeType) {
                    if (!any_of(numberTypes.begin(), numberTypes.end(), [&variableNode](const string &type) {
                        return variableNode->variable.type == type;
                    }) || !any_of(numberTypes.begin(), numberTypes.end(), [&rightNodeType](const string &type) {
                        return rightNodeType == type;
                    })) {

                    }
                }
            }
        }

    }
    Execute();
}

