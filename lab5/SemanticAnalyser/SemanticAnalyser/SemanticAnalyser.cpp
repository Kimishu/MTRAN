//
// Created by Kimihito on 07.05.2023.
//

#include <algorithm>
#include "SemanticAnalyser.h"
#include "StatementsNode.h"
#include "FunctionNode.h"
#include "WhileNode.h"
#include "IfNode.h"
#include "ForNode.h"
#include "FunctionCallNode.h"
#include "SwitchNode.h"
#include "CaseNode.h"
#include "KeyWordNode.h"
#include "BinaryOperationNode.h"
#include "LiteralNode.h"
#include "UnaryOperationNode.h"
#include "VariableNode.h"
#include "ReturnNode.h"
#include "VariableTypeNode.h"

SemanticAnalyser::SemanticAnalyser(){
}

void SemanticAnalyser::Analyse(shared_ptr<Node> root) {

    if (root == nullptr) {
        return;
    }

    if (root->getType() == Statements) {
        shared_ptr<StatementsNode> statementsNode = dynamic_pointer_cast<StatementsNode>(root);

        for (shared_ptr<Node>& node: statementsNode->nodes) {
            Analyse(node);
        }
    }

    if (root->getType() == Function) {
        shared_ptr<FunctionNode> functionNode = dynamic_pointer_cast<FunctionNode>(root);


        functions.push_back(functionNode);
        ScopeAdd(functionNode->function.value);

        level++;

        for(Token& parameter : functionNode->parameters){
            ScopeAdd(parameter.value);
        }

        Analyse(functionNode->body);
        ScopeClear();
    }

    if (root->getType() == While) {
        shared_ptr<WhileNode> whileNode = dynamic_pointer_cast<WhileNode>(root);

        Analyse(whileNode->condition);
        Analyse(whileNode->body);
    }

    if (root->getType() == If) {
        shared_ptr<IfNode> ifNode = dynamic_pointer_cast<IfNode>(root);

        Analyse(ifNode->condition);
        level++;
        Analyse(ifNode->body);
        ScopeClear();
        level++;
        Analyse(ifNode->elseBody);
        ScopeClear();
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

        if(shared_ptr<FunctionNode> function; any_of(functions.begin(), functions.end(),[&functionCallNode, &function](shared_ptr<FunctionNode> f){
            if(functionCallNode->function.value == f->function.value){
                function = f;
                return true;
            }
            return false;
        })){
            if(function->parameters.size() != functionCallNode->parameters.size()){
                cout << "Wrong parameters count! Expected: " << function->parameters.size() << " Detected: "<<functionCallNode->parameters.size()<<endl;
                exit(EXIT_FAILURE);
            }
        } else{
            cout << "Unknown function " << functionCallNode->function.value << " detected";
            exit(EXIT_FAILURE);
        }

        for (shared_ptr<Node> &node: functionCallNode->parameters) {
            Analyse(node);
        }

    }

    if (root->getType() == Switch) {
        shared_ptr<SwitchNode> switchNode = dynamic_pointer_cast<SwitchNode>(root);

        Analyse(switchNode->body);
    }

    if(root->getType() == Case){
        shared_ptr<CaseNode> caseNode = dynamic_pointer_cast<CaseNode>(root);

        Analyse(caseNode->literal);
    }

    if (root->getType() == Binary) {
        shared_ptr<BinaryOperationNode> binaryOperationNode = dynamic_pointer_cast<BinaryOperationNode>(root);
        if (binaryOperationNode->leftNode->getType() == Variable) {
            shared_ptr<VariableNode> variableNode = dynamic_pointer_cast<VariableNode>(binaryOperationNode->leftNode);
            CheckForNode(variableNode);
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
                        cout << "Cannot solve " << variableNode->variable.type << " and "
                             << literalNode->literal.type << endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
            // VARIABLE
            if(binaryOperationNode->rightNode->getType() == Variable){
                shared_ptr<VariableNode> secondNode = dynamic_pointer_cast<VariableNode>(
                        binaryOperationNode->rightNode);
                CheckForNode(secondNode);
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
                        cout << "Cannot solve " << variableNode->variable.type << " and " << secondNode->variable.type << endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
            if(binaryOperationNode->rightNode->getType() == Binary || binaryOperationNode->rightNode->getType() == UnaryOperation || binaryOperationNode->rightNode->getType() == FunctionCall){
                string rightNodeType = AnalyseNode(binaryOperationNode->rightNode);
                if(variableNode->variable.type != rightNodeType) {
                    if(!any_of(numberTypes.begin(),numberTypes.end(),[&variableNode](const string& type){
                        return variableNode->variable.type == type;
                    }) || !any_of(numberTypes.begin(), numberTypes.end(),[&rightNodeType](const string& type){
                        return rightNodeType == type;
                    })) {
                        cout << "Cannot solve " << variableNode->variable.type << " and " << rightNodeType << endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
        if(binaryOperationNode->leftNode->getType() == VariableType){
            shared_ptr<VariableTypeNode> variableNode = dynamic_pointer_cast<VariableTypeNode>(binaryOperationNode->leftNode);
            ScopeAdd(variableNode->variable.value);
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
                        cout << "Cannot solve " << variableNode->variable.type << " and "
                             << literalNode->literal.type << endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
            // VARIABLE
            if(binaryOperationNode->rightNode->getType() == Variable){
                shared_ptr<VariableNode> secondNode = dynamic_pointer_cast<VariableNode>(
                        binaryOperationNode->rightNode);
                CheckForNode(secondNode);
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
                        cout << "Cannot solve " << variableNode->variable.type << " and " << secondNode->variable.type << endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
            if(binaryOperationNode->rightNode->getType() == Binary || binaryOperationNode->rightNode->getType() == UnaryOperation || binaryOperationNode->rightNode->getType() == FunctionCall){
                string rightNodeType = AnalyseNode(binaryOperationNode->rightNode);
                if(variableNode->variable.type != rightNodeType) {
                    if(!any_of(numberTypes.begin(),numberTypes.end(),[&variableNode](const string& type){
                        return variableNode->variable.type == type;
                    }) || !any_of(numberTypes.begin(), numberTypes.end(),[&rightNodeType](const string& type){
                        return rightNodeType == type;
                    })) {
                        cout << "Cannot solve " << variableNode->variable.type << " and " << rightNodeType << endl;
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }

    if (root->getType() == UnaryOperation) {
        shared_ptr<UnaryOperationNode> unaryOperationNode = dynamic_pointer_cast<UnaryOperationNode>(root);

        vector<string> booleanOperators = {"!"};
        vector<string> numberOperators = {"++","--"};

        if(any_of(booleanOperators.begin(), booleanOperators.end(),[&unaryOperationNode](const string& booleanOperator){
            return unaryOperationNode->unaryOperator.value == booleanOperator;
        })){
            if(unaryOperationNode->operand->getType() == Variable){
                if(dynamic_pointer_cast<VariableNode>(unaryOperationNode->operand)->variable.type != "boolean"){
                    cout << "Unary operator " << unaryOperationNode->unaryOperator.value << " can be used only with boolean variables" << endl;
                    exit(EXIT_FAILURE);
                }
            }
            if(unaryOperationNode->operand->getType() == Literal){
                if(dynamic_pointer_cast<LiteralNode>(unaryOperationNode->operand)->literal.type != "boolean"){
                    cout << "Unary operator " << unaryOperationNode->unaryOperator.value << " can be used only with boolean literals!" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        if(any_of(numberOperators.begin(), numberOperators.end(),[&unaryOperationNode](const string& numberOperator){
            return unaryOperationNode->unaryOperator.value == numberOperator;
        })){
            if(unaryOperationNode->operand->getType() == Variable){
                shared_ptr<VariableNode> variableNode = dynamic_pointer_cast<VariableNode>(unaryOperationNode->operand);
                if(!any_of(numberTypes.begin(), numberTypes.end(), [&variableNode](const string& type){
                    return variableNode->variable.type == type;
                })){
                    cout << "Unary operator " << unaryOperationNode->unaryOperator.value << " can be used only with number variables!" << endl;
                    exit(EXIT_FAILURE);
                }
            }
            if(unaryOperationNode->operand->getType() == Literal){
                cout << "Unary operator " << unaryOperationNode->unaryOperator.value << " can be used only with number variables!" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    //Simple parts
    if (root->getType() == Literal) {
        shared_ptr<LiteralNode> literalNode = dynamic_pointer_cast<LiteralNode>(root);

    }

    if(root->getType() == VariableType){
        shared_ptr<VariableTypeNode> variableTypeNode = dynamic_pointer_cast<VariableTypeNode>(root);
        ScopeAdd(variableTypeNode->variable.value);
    }

    if (root->getType() == Variable) {
        shared_ptr<VariableNode> variableNode = dynamic_pointer_cast<VariableNode>(root);
        CheckForNode(variableNode);
    }

    if (root->getType() == Return) {
        shared_ptr<ReturnNode> returnNode = dynamic_pointer_cast<ReturnNode>(root);


        string functionReturnType = functions[functions.size()-1]->function.type;
        string returnType = AnalyseNode(returnNode->statement);

        if(functionReturnType != returnType) {
            cout << "Wrong function return type!\n" << "Expected: " << functionReturnType << endl << "Detected: " << returnType << endl;
            exit(EXIT_FAILURE);
        }

    }
}

string SemanticAnalyser::AnalyseNode(shared_ptr<Node> node) {

    if(node == nullptr){
        return "void";
    }

    if(node->getType() == Binary){
        shared_ptr<BinaryOperationNode> binaryOperationNode = dynamic_pointer_cast<BinaryOperationNode>(node);

        if(binaryOperationNode->leftNode->getType() == Variable){

            auto leftVariableNode = dynamic_pointer_cast<VariableNode>(binaryOperationNode->leftNode);
            CheckForNode(leftVariableNode);
            if(binaryOperationNode->rightNode->getType() == Variable){
                auto rightVariableNode = dynamic_pointer_cast<VariableNode>(binaryOperationNode->rightNode);
                CheckForNode(rightVariableNode);
                if(leftVariableNode->variable.type == rightVariableNode->variable.type){
                    return leftVariableNode->variable.type;
                } else {
                    cout << "Cannot solve " << leftVariableNode->variable.type << " and " << rightVariableNode->variable.type << " variable types" << endl;
                    exit(EXIT_FAILURE);
                }
            }

            if(binaryOperationNode->rightNode->getType() == Literal){
                auto rightVariableNode = dynamic_pointer_cast<LiteralNode>(binaryOperationNode->rightNode);
                if(leftVariableNode->variable.type == rightVariableNode->literal.type){
                    return leftVariableNode->variable.type;
                } else {
                    cout << "Cannot solve " << leftVariableNode->variable.type << " and " << rightVariableNode->literal.type << " variable types" << endl;
                    exit(EXIT_FAILURE);
                }
            }

            if(binaryOperationNode->rightNode->getType() == Binary || binaryOperationNode->rightNode->getType() == Variable || binaryOperationNode->rightNode->getType() == FunctionCall){
                string rightNodeType = AnalyseNode(binaryOperationNode->rightNode);

                if(leftVariableNode->variable.type == rightNodeType){
                    return leftVariableNode->variable.type;
                } else {
                    cout << "Cannot solve " << leftVariableNode->variable.type << " and " << rightNodeType << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        if(binaryOperationNode->leftNode->getType() == Literal){
            auto leftVariableNode = dynamic_pointer_cast<LiteralNode>(binaryOperationNode->leftNode);

            if(binaryOperationNode->rightNode->getType() == Variable){
                auto rightVariableNode = dynamic_pointer_cast<VariableNode>(binaryOperationNode->rightNode);
                CheckForNode(rightVariableNode);
                if(leftVariableNode->literal.type == rightVariableNode->variable.type){
                    return leftVariableNode->literal.type;
                } else {
                    cout << "Cannot solve " << leftVariableNode->literal.type << " and " << rightVariableNode->variable.type << endl;
                    exit(EXIT_FAILURE);
                }
            }

            if(binaryOperationNode->rightNode->getType() == Literal){
                auto rightVariableNode = dynamic_pointer_cast<LiteralNode>(binaryOperationNode->rightNode);
                if(leftVariableNode->literal.type == rightVariableNode->literal.type){
                    return leftVariableNode->literal.type;
                } else {
                    cout << "Cannot solve " << leftVariableNode->literal.type << " and " << rightVariableNode->literal.type << endl;
                    exit(EXIT_FAILURE);
                }
            }

            if(binaryOperationNode->rightNode->getType() == Binary || binaryOperationNode->rightNode->getType() == Variable || binaryOperationNode->rightNode->getType() == FunctionCall){
                string rightNodeType = AnalyseNode(binaryOperationNode->rightNode);

                if(leftVariableNode->literal.type == rightNodeType){
                    return leftVariableNode->literal.type;
                } else {
                    cout << "Cannot solve " << leftVariableNode->literal.type << " and " << rightNodeType << endl;
                    exit(EXIT_FAILURE);
                }

            }
        }

        if(binaryOperationNode->leftNode->getType() == Binary || binaryOperationNode->leftNode->getType() == UnaryOperation || binaryOperationNode->rightNode->getType() == FunctionCall){
            string leftVariableNode = AnalyseNode(binaryOperationNode->leftNode);

            if(binaryOperationNode->rightNode->getType() == Variable){
                auto rightVariableNode = dynamic_pointer_cast<VariableNode>(binaryOperationNode->rightNode);
                CheckForNode(rightVariableNode);
                if(leftVariableNode == rightVariableNode->variable.type){
                    return leftVariableNode;
                } else {
                    cout << "Cannot solve " << leftVariableNode << " and " << rightVariableNode << endl;
                    exit(EXIT_FAILURE);
                }
            }

            if(binaryOperationNode->rightNode->getType() == Literal){
                auto rightVariableNode = dynamic_pointer_cast<LiteralNode>(binaryOperationNode->rightNode);
                if(leftVariableNode == rightVariableNode->literal.type){
                    return leftVariableNode;
                } else {
                    cout << "Cannot solve " << leftVariableNode << " and " << rightVariableNode << endl;
                    exit(EXIT_FAILURE);
                }
            }

            if(binaryOperationNode->rightNode->getType() == Binary || binaryOperationNode->rightNode->getType() == UnaryOperation || binaryOperationNode->rightNode->getType() == FunctionCall){
                string rightNodeType = AnalyseNode(binaryOperationNode->rightNode);

                if(leftVariableNode == rightNodeType){
                    return leftVariableNode;
                } else {
                    cout << "Cannot solve " << leftVariableNode << " and " << rightNodeType << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

    }

    if(node->getType() == UnaryOperation){
        shared_ptr<UnaryOperationNode> unaryOperationNode = dynamic_pointer_cast<UnaryOperationNode>(node);

        vector<string> booleanOperators = {"!"};
        vector<string> numberOperators = {"++","--","-","+"};

        if(unaryOperationNode->operand->getType() == Variable){
            auto variable = dynamic_pointer_cast<VariableNode>(unaryOperationNode->operand);
            CheckForNode(variable);
            if(any_of(numberOperators.begin(), numberOperators.end(),[&unaryOperationNode](const string& type){
                return unaryOperationNode->unaryOperator.value == type;
            })){
                if(!any_of(numberTypes.begin(), numberTypes.end(),[&variable](const string& type){
                    return variable->variable.type == type;
                })){
                    cout << "Unary operator " << unaryOperationNode->unaryOperator.value << " can be used only with number variables!" << endl;
                    exit(EXIT_FAILURE);
                } else {
                    return variable->variable.type;
                }
            }

            if(any_of(booleanOperators.begin(), booleanOperators.end(),[&unaryOperationNode](const string& type){
                return unaryOperationNode->unaryOperator.type == type;
            })){
                if(variable->variable.type == "boolean"){
                    return variable->variable.type;
                } else {
                    cout << "Unary operator " << unaryOperationNode->unaryOperator.value << " can be used only with boolean variables!" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        if(unaryOperationNode->operand->getType() == Literal){
            auto literal = dynamic_pointer_cast<LiteralNode>(unaryOperationNode->operand);

            if(any_of(numberOperators.begin(), numberOperators.end(),[&unaryOperationNode](const string& type){
                return unaryOperationNode->unaryOperator.value == type;
            })){
                if(!any_of(numberTypes.begin(), numberTypes.end(),[&literal](const string& type){
                    return literal->literal.type == type;
                })){
                    cout << "Unary operator " << unaryOperationNode->unaryOperator.value << " can be used only with number literals!" << endl;
                    exit(EXIT_FAILURE);
                } else {
                    return literal->literal.type;
                }
            }

            if(any_of(booleanOperators.begin(), booleanOperators.end(),[&unaryOperationNode](const string& type){
                return unaryOperationNode->unaryOperator.value == type;
            })){
                if(literal->literal.type == "boolean"){
                    return literal->literal.type;
                } else {
                    cout << "Unary operator " << unaryOperationNode->unaryOperator.value << " can be used only with boolean literals!" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        if(unaryOperationNode->operand->getType() == UnaryOperation || unaryOperationNode->operand->getType() == Binary){
            string operandType = AnalyseNode(unaryOperationNode->operand);

            if(any_of(numberOperators.begin(), numberOperators.end(),[&unaryOperationNode](const string& type){
                return unaryOperationNode->unaryOperator.value == type;
            })){
                if(!any_of(numberTypes.begin(), numberTypes.end(),[&operandType](const string& type){
                    return operandType == type;
                })){
                    cout << "Unary operator " << unaryOperationNode->unaryOperator.value << " can be used only with number expressions!" << endl;
                    exit(EXIT_FAILURE);
                } else {
                    return operandType;
                }
            }

            if(any_of(booleanOperators.begin(), booleanOperators.end(),[&unaryOperationNode](const string& type){
                return unaryOperationNode->unaryOperator.value == type;
            })){
                if(operandType == "boolean"){
                    return operandType;
                } else {
                    cout << "Unary operator " << unaryOperationNode->unaryOperator.value << " can be used only with boolean expressions!" << endl;
                    exit(EXIT_FAILURE);
                }
            }

        }

    }

    if(node->getType() == Literal){
        shared_ptr<LiteralNode> literalNode = dynamic_pointer_cast<LiteralNode>(node);

        return literalNode->literal.type;
    }

    if(node->getType() == Variable){
        shared_ptr<VariableNode> variableNode = dynamic_pointer_cast<VariableNode>(node);

        return variableNode->variable.type;
    }

    if(node->getType() == FunctionCall){
        shared_ptr<FunctionCallNode> functionCallNode = dynamic_pointer_cast<FunctionCallNode>(node);

        if(shared_ptr<FunctionNode> function; any_of(functions.begin(), functions.end(),[&functionCallNode, &function](shared_ptr<FunctionNode> f){
            if(functionCallNode->function.value == f->function.value){
                function = f;
                return true;
            }
            return false;
        })){
            if(function->parameters.size() != functionCallNode->parameters.size()){
                cout << "Wrong parameters count! Expected: " << function->parameters.size() << " Detected: "<<functionCallNode->parameters.size()<<endl;
                exit(EXIT_FAILURE);
            }
        } else{
            cout << "Unknown function " << functionCallNode->function.value << " detected";
            exit(EXIT_FAILURE);
        }

        for (shared_ptr<Node> &node: functionCallNode->parameters) {
            Analyse(node);
        }

        return find_if(functions.begin(), functions.end(), [&functionCallNode](shared_ptr<FunctionNode> function){
            return functionCallNode->function.type == function->function.type;
        })->get()->function.type;
    }
}

void SemanticAnalyser::ScopeAdd(string value) {
    scope.push_back(make_pair(value, level));
}

void SemanticAnalyser::ScopeClear() {
    scope.erase(remove_if(scope.begin(), scope.end(),[this](const pair<string,int>& pr) {
        return pr.second == level;
    }), scope.end());
    level--;
}

bool SemanticAnalyser::CheckForNode(shared_ptr<VariableNode> node) {

    if(!any_of(scope.begin(),scope.end(),[&node, this](const pair<string,int>& pr){
        if(pr.first == node->variable.value){
            return true;
        }
        return false;
    })){
        cout << "Variable " << node->variable.value << " is out of scope!" << endl;
        exit(EXIT_FAILURE);
    }
    return false;
}






