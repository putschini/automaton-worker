#include "automaton.hpp"

namespace automaton {

    Automaton::Automaton( std::vector< std::string > alphabet ): alphabet_(alphabet), epsilon_( "&" ){}

    void Automaton::addTransition( AutomatonState* out, std::string by, AutomatonState* in ){
        if( !containState( out ) )
            addState(out);

        if( !containState( in ) )
            addState(in);

        out->connectTo( in, by );
    }

    void Automaton::addEpsilonTransition( AutomatonState* from, AutomatonState* to ){
        if( !containState( from ) )
            addState(from);

        if( !containState( to ) )
            addState(to);

        from->connectTo( to, epsilon_ );
    }

    void Automaton::addState( AutomatonState* state ){
        all_states_.insert( state_map::value_type( state->getName(), state ));
    //        std::cout << state->getName() << all_states_.size() << std::endl;
    }

    AutomatonState* Automaton::getState( std::string name ){
        AutomatonState* state = nullptr;
        if( containState( name ) )
            state = all_states_[name];
        return state;
    }

    bool Automaton::containState( AutomatonState* state ){
        return all_states_.count( state->getName() );
    }

    bool Automaton::containState( std::string name ){
        return all_states_.count( name );
    }

    void Automaton::setAsFirstState( AutomatonState* first ){
        if( !containState(first) )
            addState(first);
        first_state_ = first;
    }

    void Automaton::setAsFinalState( AutomatonState* final ){
        if( !containState(final) )
            addState(final);
        final->setFinal(true);
    }

    bool Automaton::isFinalState( AutomatonState* final ){
        return final->isFinal();
    }

    void Automaton::setAlphabet( std::vector <std::string> alphabet ){
        alphabet_ = alphabet;
    }

    std::vector< std::string > Automaton::getAlphabet(){
        return alphabet_;
    }

    std::string Automaton::getEpsilon(){
        return epsilon_;
    }

    bool Automaton::isAFND( ){
        for( state_map::iterator state_it = all_states_.begin(); state_it != all_states_.end(); ++state_it ) {
            AutomatonState* state = state_it->second;
            if( state->countTransitionsBy( epsilon_ ) )
                return true;
            for( auto by = alphabet_.begin(); by != alphabet_.end(); by++ ){
                if( state->countTransitionsBy( *by ) > 1 )
                    return true;
            }
        }
        return false;
    }

    state_set Automaton::getStatesReachedBy( state_set from ,std::string by ){
        state_set result;
        state_set transition_states;
        for( auto state = from.begin( ); state != from.end( ); state++ ){  // For every state in new state set
            state_set states_by = (*state)->getTransitionsBy( by );   // Get Transitions by
            transition_states.insert( states_by.begin(), states_by.end() );
        }
        for( auto state = transition_states.begin(); state != transition_states.end(); state++ ){  //Get Epsilon Closure for the reached states
            state_set states_epsilon_closure = (*state)->getEpsilonClosure( epsilon_ );
            result.insert( states_epsilon_closure.begin(), states_epsilon_closure.end() );
        }
        return result;
    }

    state_set Automaton::getStatesReachedBy( AutomatonState* from ,std::string by ){
        state_set result;
        state_set transition_states;

        state_set states_by = from->getTransitionsBy( by );   // Get Transitions by
        transition_states.insert( states_by.begin(), states_by.end() );

        for( auto state = transition_states.begin(); state != transition_states.end(); state++ ){  //Get Epsilon Closure for the reached states
            state_set states_epsilon_closure = (*state)->getEpsilonClosure( epsilon_ );
            result.insert( states_epsilon_closure.begin(), states_epsilon_closure.end() );
        }
        return result;
    }

    void Automaton::addDeadState(){
        AutomatonState* dead_state = new AutomatonState( "--" );
        for( auto by = alphabet_.begin(); by != alphabet_.end(); ++by ){
            for( auto state = all_states_.begin(); state != all_states_.end(); ++state ){
                if( !state->second->countTransitionsBy( *by ) ){
                    if( !containState( dead_state ) ){
                        addState( dead_state );
                        std::cout << "ADD DEAD STATE " << std::endl;
                    }
                    addTransition( state->second, *by, dead_state );
                }
            }
        }
        if( containState(dead_state) ){
            for( auto by = alphabet_.begin(); by != alphabet_.end(); ++by ){
                addTransition( dead_state, *by, dead_state );
            }
        }
    }

    AutomatonState* Automaton::getFirstState(){
        return first_state_;
    }

    state_map Automaton::getAllStates(){
        return all_states_;
    }

    state_set Automaton::getFinalStates(){
        state_set final;
        for( auto state = all_states_.begin(); state != all_states_.end(); ++state  ){
            if( state->second->isFinal() )
                final.insert( state->second );
        }
        return final;
    }

    state_set Automaton::getNotFinalStates(){
        state_set not_final;
        for( auto state = all_states_.begin(); state != all_states_.end(); ++state  ){
            if( !state->second->isFinal() )
                not_final.insert( state->second );
        }
        return not_final;
    }


    //    void Automaton::printState(){
    //        for( state_map::iterator state = all_states_.begin(); state != all_states_.end(); ++state ){
    //            for( auto by = alphabet_.begin(); by != alphabet_.end(); by++ ){
    //                state->second->printTransitionsBy( *by );
    //            }
    //        }
    //    }

    void Automaton::printState(){
        for( state_map::iterator state = all_states_.begin(); state != all_states_.end(); ++state ){
            if( state->second == first_state_ )
                std::cout << "->";
            state->second->printState();
        }
    }

}