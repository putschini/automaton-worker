#ifndef REGEX_HPP
#define REGEX_HPP

#include <string>

#include "syntactictree.hpp"

namespace regex{


    class Regex{
    private:
        std::string expression_;

    public:

        Regex( std::string expression );

        SyntacticTree* createSyntacticTree();

    };

}

#endif // REGEX_HPP
