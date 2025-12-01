#include "syntactictreenode.hpp"

namespace regex{

    SyntacticTreeNode::SyntacticTreeNode( std::string symbol ): symbol_( symbol ), left_node_(nullptr), right_node_(
            nullptr)  {}

    void SyntacticTreeNode::addLeftNode( SyntacticTreeNode *left ) {
        left_node_ = left;
    }

    void SyntacticTreeNode::addRightNode( SyntacticTreeNode *right ) {
        right_node_ = right;
    }

    std::set<SyntacticTreeNode*> SyntacticTreeNode::getFirstPos(){
        if( first_pos_.empty() )
            computeFirstPos();
        return first_pos_;
    }

    std::set<SyntacticTreeNode*> SyntacticTreeNode::getLastPos(){
        if( last_pos_.empty() )
            computeLastPos();
        return last_pos_;
    }

    std::set<SyntacticTreeNode*> SyntacticTreeNode::getFollowPos(){
        if( follow_pos_.empty() )
            computeFollowPos();
        return follow_pos_;
    }

    bool SyntacticTreeNode::getNullable(){
        if( nullable_ == -1 )
            computeNullable();
        return nullable_;
    }

    std::string SyntacticTreeNode::getSymbol(){
        return symbol_;
    }
}
