#include "automatonstate.hpp"

namespace automaton {

    AutomatonState::AutomatonState( std::string name ): name_(name), final_(false) {}

    void AutomatonState::connectTo( AutomatonState* to, std::string by ){
        transitions_.insert( transitions::value_type( by, to ) );
    }

    std::string AutomatonState::getName(){
        return name_;
    }

    int AutomatonState::countTransitionsBy( std::string by ){
        return transitions_.count(by);
    }

    AutomatonState::transitions AutomatonState::getAllTransitions(){
        return transitions_;
    }

    /// Epsilon is configurable so we need to pass it
    std::set<AutomatonState*> AutomatonState::getEpsilonClosure( std::string epsilon ){
        std::set<AutomatonState*> result;
        std::pair<transitions::iterator, transitions::iterator> found = transitions_.equal_range( epsilon );
        for( transitions::iterator it = found.first; it != found.second; it++ ){
            std::set<AutomatonState*> new_state_closure = it->second->getEpsilonClosure( epsilon );
            result.insert( new_state_closure.begin(), new_state_closure.end() );
        }
        result.insert( this );
        return result;
    }

    std::set<AutomatonState*> AutomatonState::getTransitionsBy( std::string by ){
        std::set<AutomatonState*> result;
        std::pair<transitions::iterator, transitions::iterator> found = transitions_.equal_range( by );
        for( transitions::iterator it = found.first; it != found.second; it++ ){
            result.insert( it->second );
        }
        return result;
    }

    std::set<AutomatonState*> AutomatonState::getAllReachedStates(){
        std::set<AutomatonState*> result;
        for( transitions::iterator it = transitions_.begin(); it != transitions_.end(); it++ ){
            result.insert( it->second );
        }
        return result;
    }

    bool AutomatonState::reachSomeStateOf( std::set<AutomatonState*> states ){
        for( transitions::iterator it = transitions_.begin(); it != transitions_.end(); it++ ){
            AutomatonState* state = it->second;
            if( states.count( state ) )
                return true;
        }
        return false;
    }

    void AutomatonState::setFinal( bool final ){
        final_ = final;
    }

    bool AutomatonState::isFinal(){
        return final_;
    }

    //////////////////////////////
    void AutomatonState::printState( ){
        if(final_)
            std::cout << "*";
        std::cout << name_ << " -> ";
        for( auto trans = transitions_.begin(); trans != transitions_.end(); trans++)
        {
            std::cout << trans->first << " : "  << trans->second->getName() << "; " ;
        }
        std::cout << std::endl;
    }

    void AutomatonState::printTransitionsBy( std::string by ){
        std::cout << "STATE  " << name_ << std::endl;
        std::pair<transitions::iterator, transitions::iterator> found = transitions_.equal_range( by );
        for( transitions::iterator it = found.first; it != found.second; it++ ){
            std::cout << it->second->getName() << std::endl;
        }
    }

}
