#ifndef SYNTACTIC_TREE_HPP
#define SYNTACTIC_TREE_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "syntactictreenode.hpp"
#include "syntactictreecatnode.hpp"
#include "syntactictreeornode.hpp"
#include "syntactictreestarnode.hpp"
#include "syntactictreecharnode.hpp"

namespace regex{


    class SyntacticTree{
    private:
        SyntacticTreeNode* first_node_;
        std::map< int, SyntacticTreeNode* > map_position_leaf;

    public:

        //TODO MOVE TO WORKER
        SyntacticTreeNode* getNodeFrom( std::vector< std::string > tokens);

        std::vector< std::string > tokenize( std::string in );

        bool is_char_symbol( std::string symbol );

        SyntacticTree( std::string regex);

        void computeFirstPos();

        void computeLastPos();

        void computeNullable();

        void computeLeafPos();

        void printTree();
    };
}


#endif // SYNTACTIC_TREE_HPP
