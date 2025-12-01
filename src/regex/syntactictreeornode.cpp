#include "syntactictreeornode.hpp"

namespace regex{

    SyntacticTreeOrNode::SyntacticTreeOrNode(): SyntacticTreeNode( "|" ){}

    void SyntacticTreeOrNode::computeFirstPos(){
        std::set<SyntacticTreeNode*> first_pos_left = left_node_->getFirstPos();
        first_pos_.insert( first_pos_left.begin(), first_pos_left.end() );
        std::set<SyntacticTreeNode*> first_pos_right = right_node_->getFirstPos();
        first_pos_.insert( first_pos_right.begin(), first_pos_right.end() );
    }

    void SyntacticTreeOrNode::computeFollowPos(){

    }

    void SyntacticTreeOrNode::computeLastPos(){
        std::set<SyntacticTreeNode*> last_pos_left = left_node_->getLastPos();
        last_pos_.insert( last_pos_left.begin(), last_pos_left.end() );
        std::set<SyntacticTreeNode*> last_pos_right = right_node_->getLastPos();
        last_pos_.insert( last_pos_right.begin(), last_pos_right.end() );
    }

    void SyntacticTreeOrNode::computeNullable(){
//        right_node_->computeNullable();
        left_node_->computeNullable();
        nullable_ = right_node_->getNullable() || left_node_->getNullable();
    }

}