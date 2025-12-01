#ifndef SYNTACTIC_TREE_NODE_HPP
#define SYNTACTIC_TREE_NODE_HPP

#include <string>
#include <set>
#include <iostream>

namespace regex{

    class SyntacticTreeNode{
    protected:
        std::string symbol_;
        std::set<SyntacticTreeNode*> first_pos_;
        std::set<SyntacticTreeNode*> last_pos_;
        std::set<SyntacticTreeNode*> follow_pos_;
        int nullable_;

        SyntacticTreeNode* left_node_;
        SyntacticTreeNode* right_node_;

    public:

        SyntacticTreeNode( std::string symbol );

        virtual void computeFirstPos() = 0;

        virtual void computeLastPos() = 0;

        virtual void computeFollowPos() = 0;

        virtual void computeNullable() = 0;

        std::set<SyntacticTreeNode*> getFirstPos();

        std::set<SyntacticTreeNode*> getLastPos();

        std::set<SyntacticTreeNode*> getFollowPos();

        bool getNullable();

        void addLeftNode( SyntacticTreeNode* left );

        void addRightNode( SyntacticTreeNode* right );

        std::string getSymbol();

        virtual void printNode() = 0;
    };
}

#endif // SYNTACTIC_TREE_NODE_HPP
