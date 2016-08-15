#ifndef BET_H
#define BET_H
#include <stack>
#include <string>
/*
    Project 4:  Binary Expression Tree Implementation
    Date:       11/9/2015
    Name:       Michael Rand
    Class:      COP 4530
*/

class BET{
    private:
        //Private BinaryNode Struct with element, left & right nodes
        struct BinaryNode{
                std::string element;
                BinaryNode *left;
                BinaryNode *right;

                //Constructor
                BinaryNode() : left{nullptr},right{nullptr}{}
                BinaryNode(const std::string &elm, BinaryNode *ll, BinaryNode *rr)
                    : element{elm}, left{ll},right{rr}{}
            };
    public:
        BET();  //default constr.
        BET(const std::string postfix); //overl. constr.
        BET(const BET&);    //copy
        ~BET(); //destructor

        //mutators
        const BET & operator=(const BET &); //assignment op.
        bool buildFromPostfix(const std::string postfix); //Tree built success

        void printInfixExpression();    //print infix
        void printPostfixExpression();  //print postfix

        //Accessors
        size_t size();  //num nodes in tree
        size_t leaf_nodes();    //num leaf nodes in tree
        bool empty();   //tree is empty
    private:
        std::stack<BinaryNode*> betStack;   //Expression stack
        BinaryNode *root;   //Root node

        void ClearStack();
        bool IsOperator(const std::string &s);
        bool IsOperand(const std::string &s);
        //Recursive
        void printInfixExpression(BinaryNode *n);   //print infix
        void makeEmpty(BinaryNode* &t); //delete all nodes in subtree,->destr.
        void printPostfixExpression(BinaryNode *n);

        BinaryNode * clone(BinaryNode *t) const;   //clone all nodes,->assn. op
        size_t size(BinaryNode *t); //num nodes in subtree of t
        size_t leaf_nodes(BinaryNode *t);   //num leafnodes
        //End recursive
    };

#endif
