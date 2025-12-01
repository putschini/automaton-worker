#include "syntactictreestarnode.hpp"

namespace regex {

    SyntacticTreeStarNode::SyntacticTreeStarNode(): SyntacticTreeNode( "*" ){}

    void SyntacticTreeStarNode::computeFirstPos(){
        std::set<SyntacticTreeNode*> first_pos_left = left_node_->getFirstPos();
        first_pos_.insert( first_pos_left.begin(), first_pos_left.end() );
    }

    void SyntacticTreeStarNode::computeLastPos(){
        std::set<SyntacticTreeNode*> last_pos_left = left_node_->getLastPos();
        last_pos_.insert( last_pos_left.begin(), last_pos_left.end() );
    }

    void SyntacticTreeStarNode::computeFollowPos(){
        
    }

    void SyntacticTreeStarNode::computeNullable(){
        left_node_->computeNullable();
        nullable_ = true;
    }

}
