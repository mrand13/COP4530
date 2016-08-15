#include "bet.h"
#include <iostream>
/*
    Project 4:  Binary Expression Tree Implementation
    Date:       11/9/2015
    Name:       Michael Rand
    Class:      COP 4530
*/
//------------------------------------------------------------//
//Public Scope
//------------------------------------------------------------//
//Default Constructor
BET::BET() : root{nullptr}{}

//One param constructor with intialization list
BET::BET(const std::string postfix) : root{nullptr}{
    //Call buildFromPostfix
    buildFromPostfix(postfix);
}

//Copy Constructor with initialization list
BET::BET(const BET& rhs): root{nullptr}{
    ClearStack();
    root = clone(rhs.root);
    betStack.push(root);
}

//Destructor
BET::~BET(){
    if(!empty())
        makeEmpty(root);
    if(root != nullptr)
        delete root;
}

//Assignment Operator
const BET & BET::operator=(const BET& rhs){
    //Clone the root
    root = clone(rhs.root);
    //Cleanup any loose ends
    ClearStack();
    //Add root to current stack
    betStack.push(root);
    return *this;
}

//Param postfix: string containing postfix expression
// Tree built based on postfix, tokens are separated by space
// Returns if tree is built successfully.
bool BET::buildFromPostfix(const std::string postfix){
    //Ensure new tree being formed
    if(!empty()){
        makeEmpty(root);
        ClearStack();
    }
    //Local variables
    bool ret = true;
    std::string post = postfix, token;
    //Iterate across postfix string
    for(std::string::iterator it = post.begin(); it!= post.end(); ++it){
        token += *it;   //Add given character to token string
        //If the given char is a space or the end of string, create the tree
        if(*it == ' ' || it == (post.end()- 1)){
            //If last character in postfix string is space, remove from token
            if(*it == ' ')
                token.pop_back();
            if(IsOperand(token)){
                //Create nodes when Operand is found
                //Create new node with operand
                BinaryNode *n = new BinaryNode(token,nullptr,nullptr);
                //Push new node into Stack
                betStack.push(n);
            }
            else if(IsOperator(token)){
                //Create Tree based on when Operator is found
                //Pop operands from Stack
                BinaryNode *rr, *ll;    //Right and left temp
                //Error handling for empty stack
                if(!betStack.empty()){
                    rr = betStack.top();
                    betStack.pop();
                }
                else {ret = false;break;}
                //Error handling for empty stack
                if(!betStack.empty()){
                    ll = betStack.top();
                    betStack.pop();
                }
                else {ret = false; break;}
                //create new node with operator/operands
                BinaryNode *op = new BinaryNode(token,ll,rr);
                //push new node into stack
                betStack.push(op);
            }
            token = ""; //Reset token string
        }
    }
    //Final Error checking for missing operand/operators of empty stack
    if(!betStack.empty()){
        root = betStack.top();  //Get the expected 'root'
        //If stack has leftover operands error
        if(betStack.size() > 1 && IsOperand(root->element))
            ret = false;
    }
    else ret = false;

    //Error message/cleanup based on 'ret' boolean value
    if(!ret){
        std::cout << "Wrong postfix expression" << std::endl;
        //Clear any attempted tree
        if(!empty()){
            makeEmpty(root);
            ClearStack();
        }
    }
    return ret;
}

//Calls the private version of printInfix based on root
void BET::printInfixExpression(){
    printInfixExpression(root);
    std::cout << std::endl;  //Newline terminator
}

//Calls the private version of printPostfix based on root
void BET::printPostfixExpression(){
    printPostfixExpression(root);
    std::cout << std::endl;  //Newline terminator
}

//Calls the private version of size based on root
size_t BET::size(){
    return size(root);
}

//Calls the private version of leaf_nodes based on root
size_t BET::leaf_nodes(){
    return leaf_nodes(root);
}

//Returns whether or not a root has been initialized
bool BET::empty(){
    return (root == nullptr);
}

//Member function ClearStack empty's a stack
void BET::ClearStack(){
    while(!betStack.empty())
        betStack.pop();
}

//Member function IsOperator returns whether a string is an operator
bool BET::IsOperator(const std::string &s){
    return(s == "+" || s == "-" || s == "/" || s == "*");
}

//Member function IsOperand checks string for operand case
bool BET::IsOperand(const std::string &s){
    if(s.length() == 1){
        char c = s[0];
        return((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c == '_'));
    }
    else return true;
}
//------------------------------------------------------------//
//Private Scope
//------------------------------------------------------------//

//Print to standard output the infix expression
//by navigating recursively tree LEFT, ELEMENT, RIGHT
void BET::printInfixExpression(BET::BinaryNode *n){
    if(n != nullptr){
        //If Node is an operator and it is not the root node
        if(IsOperator(n->element) && n != root)
            std::cout << "( ";
        printInfixExpression(n->left);
        std::cout << n->element << " ";
        printInfixExpression(n->right);
        //If Node is an operator and it is not the root node
        if(IsOperator(n->element) && n != root)
            std::cout << ") ";
    }
    //Could not figure out how to remove unnecessary parentheses
    //even when comparing the visual structures of the five example
    //postfix expressions, no correlation was seen visually between
    //the trees nodes.
}

//Print to the standard output the postfix expression
//by navigating recursively tree LEFT, RIGHT, ELEMENT
void BET::printPostfixExpression(BET::BinaryNode *n){
    if(n != nullptr){
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        std::cout << n->element << " ";
    }
}

//Function makeEmpty frees the memory allocated
//to a given tree recursively, calls 'delete'
void BET::makeEmpty(BinaryNode* &t){
    //If node is not empty, delete
    if(t != nullptr){
        //Check to make sure left & right are not
        //nullptr's before emptying
        if(t->left != nullptr)
            makeEmpty(t->left);
        if(t->right != nullptr)
            makeEmpty(t->right);
        delete t;   //free memory
    }
    //Set node to nullptr for recursion and deletion
    t = nullptr;
}

//Clones a given tree by creating new nodes
//recursively
BET::BinaryNode * BET::clone(BET::BinaryNode* t) const{
    if(t == nullptr)
        return nullptr;
    else return new BinaryNode{t->element,clone(t->left),clone(t->right)};
}

//Returns the size_t of number of nodes
//recursively in a given tree
size_t BET::size(BET::BinaryNode *t){
    if(t == nullptr)
        return 0;
    else return 1 + size(t->left) + size(t->right);
}

//Returns the size_t of number of leaf nodes
//recursively in a given tree
size_t BET::leaf_nodes(BET::BinaryNode *t){
    if(t == nullptr)
        return 0;
    //If node does not have any children, it is a leaf
    if(t->left == nullptr && t->right == nullptr)
        return 1;
    else return 0 + leaf_nodes(t->left) + leaf_nodes(t->right);
}
