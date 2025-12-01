#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "automatonstate.hpp"

namespace utils{

    static std::string getNewStateName( std::set<automaton::AutomatonState*> new_state ){
        std::string result = "";
        for( std::set<automaton::AutomatonState*>::iterator state = new_state.begin(); state != new_state.end(); state++ ){
            result += (*state)->getName();
        }
        return result;
    }

}

#endif //UTILS_HPP
