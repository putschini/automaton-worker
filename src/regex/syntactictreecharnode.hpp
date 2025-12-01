#ifndef SYNTACTIC_TREE_CHAR_NODE_HPP
#define SYNTACTIC_TREE_CHAR_NODE_HPP

#include "syntactictreenode.hpp"

namespace regex {

    class SyntacticTreeCharNode : public SyntacticTreeNode {

    public:

        SyntacticTreeCharNode( std::string character );

        void computeFirstPos();

        void computeLastPos();

        void computeFollowPos();

        void computeNullable();
        
	    void printNode(){
	        std::cout << symbol_;
	    }
    };
}

#endif // SYNTACTIC_TREE_CHAR_NODE_HPP
