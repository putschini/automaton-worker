#ifndef SYNTACTIC_TREE_OR_NODE_HPP
#define SYNTACTIC_TREE_OR_NODE_HPP

#include "syntactictree.hpp"

namespace regex {
    class SyntacticTreeOrNode : public SyntacticTreeNode {

    public:

        SyntacticTreeOrNode();

        void computeFirstPos();

        void computeLastPos();

        void computeFollowPos();

        void computeNullable();

	    void printNode(){
            std::cout << "(";
	        if(left_node_ != nullptr ){
                left_node_->printNode();
            }
	        std::cout << symbol_;
	        if(right_node_ != nullptr ){
                right_node_->printNode();
	        }
            std::cout << ")";
	    }
    };
}

#endif // SYNTACTIC_TREE_OR_NODE_HPP