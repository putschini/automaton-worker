#include "regex.hpp"

namespace regex{

    SyntacticTree* Regex::createSyntacticTree(){

        SyntacticTree* result_tree = new SyntacticTree( expression_);


        return result_tree;
    }
}
