#include "syntactictree.hpp"

namespace regex{

    SyntacticTree::SyntacticTree( std::string regex){

        SyntacticTreeCatNode* first_node = new SyntacticTreeCatNode();

        SyntacticTreeCharNode* final_symbol = new SyntacticTreeCharNode( "#" );

        first_node->addRightNode( final_symbol );

        first_node_ = first_node;

        first_node->addLeftNode( getNodeFrom( tokenize( regex ) ) );
    }

    bool SyntacticTree::is_char_symbol( std::string symbol ) {
        if( symbol == "|" || symbol == "." || symbol == "*" || symbol.size() < 1 )
            return false;
        return true;
    }

    std::vector< std::string > SyntacticTree::tokenize( std::string in ){
        std::vector<std::string> out;
        int sub_str_index = 0;
        std::string sub_str = "";
        std::string last_str = "";
        std::string::reverse_iterator pos = in.rbegin();
        while( pos != in.rend() ) {
            std::string actual( 1, *pos );
            if( actual != ")" && actual != "(" ) {
                if( sub_str_index > 0 ) {
                    sub_str = actual + sub_str;
                }else{
                    if( actual == "*" && is_char_symbol( last_str ) ){
                        out.push_back( "." );
                    }
                    if ( is_char_symbol( last_str ) && is_char_symbol( actual ) ){
                        out.push_back( "." );
                    }
                    out.push_back( actual );
                    last_str = actual;
                }
            } else if ( actual == ")" ) {
                if( sub_str_index > 0 )
                    sub_str = actual + sub_str;
                ++sub_str_index;
            } else { // actual == "("
                --sub_str_index;
                if( sub_str_index == 0 ) {
                    if ( is_char_symbol( sub_str ) && is_char_symbol( last_str ) ){
                        out.push_back( "." );
                    }
                    out.push_back( sub_str );
                    last_str = sub_str;
                    sub_str = "";
                }else {
                    sub_str = actual + sub_str;
                }
            }
            ++pos;
        }
        return out;
    }

    SyntacticTreeNode* SyntacticTree::getNodeFrom( std::vector< std::string > tokens ){
        // std::cout << "Add Node for " << tokens[0] << std::endl;
        if( tokens.size() == 1 ){
            if( tokens[0].size() == 1 ){
                // std::cout << "----- " << tokens[0] << std::endl;
                SyntacticTreeNode* new_node = new SyntacticTreeCharNode( tokens[0] );
                return new_node;
            }
            return getNodeFrom( tokenize( tokens[0] ) );
        }else{
            for( std::vector< std::string >::iterator symbol = tokens.begin(); symbol != tokens.end() - 1; symbol++ ){
                if( *symbol == "|" ){
                    SyntacticTreeNode* new_node = new SyntacticTreeOrNode();
                    std::vector< std::string > left_tokens( symbol + 1, tokens.end() );
                    if( left_tokens.size() ){
                        SyntacticTreeNode* left_node = getNodeFrom( left_tokens );
                        new_node->addLeftNode( left_node );
                    }
                    std::vector< std::string > right_tokens( tokens.begin(), symbol );
                    if ( right_tokens.size() ){
                        SyntacticTreeNode* right_node = getNodeFrom( right_tokens );
                        new_node->addRightNode( right_node );
                    }
                    return new_node;
                }
            }
            for( std::vector< std::string >::iterator symbol = tokens.begin(); symbol != tokens.end() - 1; symbol++ ){
                if( *symbol == "." ){
                    SyntacticTreeNode* new_node = new SyntacticTreeCatNode();
                    std::vector< std::string > left_tokens( symbol + 1, tokens.end() );
                    if( left_tokens.size() ){
                        SyntacticTreeNode* left_node = getNodeFrom( left_tokens );
                        new_node->addLeftNode( left_node );
                    }
                    std::vector< std::string > right_tokens( tokens.begin(), symbol );
                    if ( right_tokens.size() ){
                        SyntacticTreeNode* right_node = getNodeFrom( right_tokens );
                        new_node->addRightNode( right_node );
                    }
                    return new_node;
                }
            }
            for( std::vector< std::string >::iterator symbol = tokens.begin(); symbol != tokens.end() - 1; symbol++ ){
                if( *symbol == "*" ){
                    SyntacticTreeNode* new_node = new SyntacticTreeStarNode();
                    std::vector< std::string > left_tokens( symbol + 1, tokens.end() );
                    SyntacticTreeNode* left_node = getNodeFrom( left_tokens );
                    new_node->addLeftNode( left_node );
                   // std::vector< std::string > right_tokens( tokens.begin(), symbol - 1 );
                   // SyntacticTreeNode* right_node = getNodeFrom( right_tokens );
                   // new_node->addRightNode( right_node );
                    return new_node;
                }
            }
        }
        std::cout << "ERROR " << std::endl;
    }

    void SyntacticTree::printTree(){
        first_node_->printNode();
        std::cout << std::endl;
    }
}