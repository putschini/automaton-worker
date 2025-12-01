#include "syntactictreecharnode.hpp"

namespace regex{

    SyntacticTreeCharNode::SyntacticTreeCharNode( std::string character ) : SyntacticTreeNode( character ) {}

    void SyntacticTreeCharNode::computeFirstPos(){
        first_pos_.insert( this );
    }

    void SyntacticTreeCharNode::computeLastPos(){
        last_pos_.insert( this );
    }

    void SyntacticTreeCharNode::computeFollowPos(){

    }

    void SyntacticTreeCharNode::computeNullable(){
        nullable_ = false;
    }
}
