#ifndef SYNTACTIC_TREE_STAR_NODE_HPP
#define SYNTACTIC_TREE_STAR_NODE_HPP

#include "syntactictree.hpp"

namespace regex {
    class SyntacticTreeStarNode : public SyntacticTreeNode {

    public:

        SyntacticTreeStarNode();

        void computeFirstPos();

        void computeLastPos();

        void computeFollowPos();

        void computeNullable();

	    void printNode(){
	        if(left_node_ != nullptr ){
            	std::cout << "(";
                left_node_->printNode();
                std::cout << ")";
	        }
	        std::cout << symbol_;
	        // if(right_node_ != nullptr ){
         //        std::cout << "(";
         //        right_node_->printNode();
         //        std::cout << ")";
	        // }
	    }
    };
}

#endif // SYNTACTIC_TREE_STAR_NODE_HPP
