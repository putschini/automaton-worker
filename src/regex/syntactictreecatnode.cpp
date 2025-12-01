#include "syntactictreecatnode.hpp"

namespace regex{

    SyntacticTreeCatNode::SyntacticTreeCatNode(): SyntacticTreeNode( "." ) {}

    void SyntacticTreeCatNode::computeFirstPos(){
        std::set< SyntacticTreeNode* > first_pos_left = left_node_->getFirstPos(); /// compute if don't exist
        right_node_->computeFirstPos(); /// compute where to grant all node being computed
        first_pos_.insert( first_pos_left.begin(), first_pos_left.end() );
        if( left_node_->getNullable() ){
            std::set< SyntacticTreeNode* > first_pos_right = right_node_->getFirstPos();
            first_pos_.insert( first_pos_right.begin(), first_pos_right.end() );
        }
    }

    void SyntacticTreeCatNode::computeFollowPos(){

    }

    void SyntacticTreeCatNode::computeLastPos(){
        std::set< SyntacticTreeNode* > last_pos_right = right_node_->getLastPos(); /// compute if don't exist
        left_node_->computeFirstPos(); /// compute where to grant all node being computed
        last_pos_.insert( last_pos_right.begin(), last_pos_right.end() );
        if( right_node_->getNullable() ){
            std::set< SyntacticTreeNode* > last_pos_left = left_node_->getLastPos();
            last_pos_.insert( last_pos_left.begin(), last_pos_left.end() );
        }
    }

    void SyntacticTreeCatNode::computeNullable(){
//        right_node_->computeNullable();
        left_node_->computeNullable(); /// May not be computed in &&, compute where to grant all node being computed
        nullable_ = right_node_->getNullable() && left_node_->getNullable();
    }

}
