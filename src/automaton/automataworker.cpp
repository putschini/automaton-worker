#include "automataworker.hpp"

namespace automaton{

    Automaton* AutomataWorker::getDetermination( Automaton* automaton ){

        state_set new_first_state_set = automaton->getFirstState()->getEpsilonClosure( "&" );
        AutomatonState* new_first_state = getNewState( new_first_state_set );
        std::vector<std::string> alphabet = automaton->getAlphabet();

        Automaton* automaton_result = new Automaton( alphabet );
        automaton_result->addState( new_first_state );
        automaton_result->setAsFirstState( new_first_state );

        std::set<state_set> new_states_set;
        new_states_set.insert( new_first_state_set );

        while ( !new_states_set.empty() ){  // While a new state is added
            state_set new_state_set = *( new_states_set.begin() );
            AutomatonState* from_state = automaton_result->getState( utils::getNewStateName(new_state_set) );

            for( auto by = alphabet.begin(); by != alphabet.end(); by++ ){  // For every symbol

                state_set new_state_set_by = automaton->getStatesReachedBy( new_state_set, *by ); // Get Set of states reached by
                new_state_set_by = getEpsilonClosureOfSet( new_state_set_by );
                AutomatonState* new_state_by;
                std::string new_state_by_name = utils::getNewStateName( new_state_set_by );

                if( !automaton_result->containState( new_state_by_name ) ){ // Add AutomatonState if don't exists
                    new_state_by = getNewState( new_state_set_by );
                    automaton_result->addState( new_state_by );
                    new_states_set.insert( new_state_set_by );
                }else{
                    new_state_by = automaton_result->getState(new_state_by_name);
                }

                automaton_result->addTransition(from_state, *by, new_state_by);  // Add transition
            }
            new_states_set.erase( new_state_set ); // remove added state
        }

        return automaton_result;
    }

    AutomatonState* AutomataWorker::getNewState( state_set states ){
        AutomatonState* new_state = new AutomatonState( utils::getNewStateName( states ) );
        for( state_set::iterator state = states.begin(); state != states.end(); state++ ){
            if( (*state)->isFinal() ){
                new_state->setFinal(true);
                break;
            }
        }
        return new_state;
    }

    state_set AutomataWorker::getEpsilonClosureOfSet( state_set states ){
        state_set result;
        for( AutomatonState* state: states ){
            state_set state_epsilon_closure = state->getEpsilonClosure( "&" );
            result.insert( state_epsilon_closure.begin(), state_epsilon_closure.end() );
        }
        return result;
    }

    Automaton* AutomataWorker::getAutomatonWithoutDeadStates( Automaton* automaton ){
        state_set not_dead_states;
        state_set new_not_dead = automaton->getFinalStates();
        state_map all_old_states = automaton->getAllStates();

        while ( !new_not_dead.empty() ){
            not_dead_states.insert( new_not_dead.begin(), new_not_dead.end() );
            new_not_dead.clear();
            for( auto state_it = all_old_states.begin(); state_it != all_old_states.end(); ++state_it ){
                AutomatonState* state = state_it->second;
                if( !not_dead_states.count( state ) && state->reachSomeStateOf( not_dead_states ) )
                    new_not_dead.insert( state );
            }
        }

        std::vector<std::string> alphabet = automaton->getAlphabet();
        Automaton* automaton_result = new Automaton( alphabet );
        AutomatonState* first_state = automaton->getFirstState();

        for( auto state_it = not_dead_states.begin(); state_it != not_dead_states.end(); ++state_it ){
            AutomatonState* state = *state_it;

            if( !automaton_result->containState( state ) ){
                automaton_result->addState( state ); // TODO change to a copy with no transitions
            }
            if( state == first_state ){
                automaton_result->setAsFirstState( first_state  );
            }

            for( auto by = alphabet.begin(); by != alphabet.end(); by++ ){
                state_set transitions = state->getTransitionsBy( *by );
                for( auto state_reached = transitions.begin(); state_reached != transitions.end(); ++state_reached ){
                    if( not_dead_states.count( *state_reached ) )
                        automaton_result->addTransition( state, *by, *state_reached );
                }
            }
        }

        return automaton_result;
    }


    Automaton* AutomataWorker::getAutomatonWithoutUnreachedStates( Automaton* automaton ){
        std::vector<std::string> alphabet = automaton->getAlphabet();
        Automaton* automaton_result = new Automaton( alphabet );
        AutomatonState* old_first_state = automaton->getFirstState();

        AutomatonState* first_state =  getStateCreateIfNeeded(automaton_result, old_first_state->getName(), old_first_state->isFinal() );
        automaton_result->addState( first_state );
        automaton_result->setAsFirstState(  first_state );

        state_set new_reached_states_set;
        new_reached_states_set.insert( old_first_state );

        alphabet.push_back( automaton->getEpsilon() );
        while ( !new_reached_states_set.empty() ){  // While a new reached state is added
            AutomatonState* old_reached = *( new_reached_states_set.begin() );
            AutomatonState* new_reached = getStateCreateIfNeeded( automaton_result, old_reached->getName(), old_reached->isFinal() );
            for( auto by = alphabet.begin(); by != alphabet.end(); by++ ){  // For every symbol

                state_set old_reached_state_set_by = automaton->getStatesReachedBy( old_reached, *by ); // Get Set of states reached by in old automaton
                for ( auto state = old_reached_state_set_by.begin(); state != old_reached_state_set_by.end(); state++ ) {
                    if( !automaton_result->containState( (*state)->getName() ) ){ // Add AutomatonState if don't exists
                        new_reached_states_set.insert( (*state) );
                    }
                    AutomatonState* new_reached_by = getStateCreateIfNeeded( automaton_result, (*state)->getName(), (*state)->isFinal() );
                    automaton_result->addTransition( new_reached, *by, new_reached_by );  // Add transition
                }
            }
            new_reached_states_set.erase( old_reached );
        }
        return automaton_result;
    }

    Automaton* AutomataWorker::getMinimal( Automaton* automaton ){

        if( automaton->isAFND() )
            automaton = getDetermination( automaton );

        automaton = getAutomatonWithoutUnreachedStates( automaton );
        automaton = getAutomatonWithoutDeadStates( automaton );

        automaton->addDeadState();// add dead state to make it a complete AFD

        std::map< AutomatonState*, int > map_state_group;
        std::map< int, AutomatonState* > map_group_state;

        state_map all_states = automaton->getAllStates();

        for( auto state = all_states.begin(); state != all_states.end(); ++state ){
            if( state->second->isFinal() ){
                map_state_group.insert( std::map<AutomatonState*, int>::value_type( state->second , 0) );
                map_group_state.insert( std::map<int, AutomatonState*>::value_type( 0, state->second ) );
            }
            else{
                map_state_group.insert( std::map<AutomatonState*, int>::value_type( state->second, 1 ) );
                map_group_state.insert( std::map<int, AutomatonState*>::value_type( 1, state->second ) );
            }
        }

        std::map< AutomatonState*, int > new_map_state_group;
        std::map< int, AutomatonState* > new_map_group_state;
        auto alphabet = automaton->getAlphabet();

        while( new_map_group_state.size() !=  map_group_state.size()   ){
            new_map_group_state.clear();
            new_map_state_group.clear();

            auto state = all_states.begin();
            new_map_state_group.insert( std::map<AutomatonState*, int>::value_type( state->second, 0 ) );
            new_map_group_state.insert( std::map<int, AutomatonState*>::value_type( 0, state->second ) );
            ++state;
            for( ;state != all_states.end(); ++state){
                int new_group_state = -1;
                for( auto group_representative = new_map_group_state.begin(); group_representative != new_map_group_state.end(); ++group_representative )
                {
                    bool same_group = true;
                    for( auto by : alphabet ){
                        AutomatonState* state_transition = *(state->second->getTransitionsBy( by ).begin());
                        AutomatonState* group_transition = *(group_representative->second->getTransitionsBy( by ).begin());
                        if( map_state_group.find( state_transition ) != map_state_group.find( group_transition ) ){
                            same_group = false;
                            break;
                        }
                    }
                    if( same_group ){
                        new_group_state = group_representative->first;
                        break;
                    }
                }
                if( new_group_state == -1 ){
                    new_group_state = new_map_group_state.size();
                    new_map_group_state.insert( std::map<int, AutomatonState*>::value_type( new_group_state, state->second ) );
                }
                new_map_state_group.insert( std::map<AutomatonState*, int>::value_type( state->second, new_group_state ) );
            }
            new_map_group_state.swap( map_group_state );
            new_map_state_group.swap( map_state_group );
        }

        Automaton* result_automaton = new Automaton( alphabet );

        for( auto group_it = map_group_state.begin(); group_it != map_group_state.end(); ++group_it ){
            std::string state_name = "q" + std::to_string(group_it->first);
            AutomatonState* new_state = getStateCreateIfNeeded( result_automaton, state_name, group_it->second->isFinal() );
            for( auto by : alphabet ){
                AutomatonState* old_transition_state = *(group_it->second->getTransitionsBy(by).begin());
                int transition_group = map_state_group.find( old_transition_state )->second;
                std::string transition_state_name = "q" + std::to_string(transition_group);
                AutomatonState* transition_state = getStateCreateIfNeeded( result_automaton, transition_state_name, old_transition_state->isFinal() );
                result_automaton->addTransition(new_state, by, transition_state);
            }
        }

        int first_group = map_state_group.find( automaton->getFirstState() )->second;
        std::string first_state_name = "q" + std::to_string(first_group);
        AutomatonState* first_state = getStateCreateIfNeeded( result_automaton, first_state_name, automaton->getFirstState()->isFinal() );
        result_automaton->setAsFirstState( first_state );

        return result_automaton;
    }

    grammar::Grammar* AutomataWorker::getGrammarFrom( Automaton* automaton ){
        grammar::Grammar* result_grammar = new grammar::Grammar( automaton->getAlphabet() );

        for( auto state: automaton->getAllStates() ){
            std::string state_name = state.first;
            grammar::GrammarProduction* new_not_terminal;
            if( result_grammar->containNotTerminal( state_name ) ){
                new_not_terminal = result_grammar->getNotTerminal( state_name );
            }else{
                new_not_terminal = new grammar::GrammarProduction( state_name );
                result_grammar->addNotTerminal( new_not_terminal );
            }
            for( auto to_state: state.second->getAllTransitions() ){
                std::string to_state_name = to_state.second->getName();
                std::string by = to_state.first;

                grammar::GrammarProduction* to_terminal;
                if( result_grammar->containNotTerminal( to_state_name ) ){
                    to_terminal = result_grammar->getNotTerminal( to_state_name );
                }else{
                    to_terminal = new grammar::GrammarProduction( to_state_name );
                    result_grammar->addNotTerminal( to_terminal );
                }

                result_grammar->addDerivation(new_not_terminal, by, to_terminal);

                // ver se estado e final e adicionar terminal
                if( to_state.second->isFinal() )
                    result_grammar->addTerminalTo(new_not_terminal, by);
            }
        }
        result_grammar->setFirstSymbol( automaton->getFirstState()->getName() );

        return result_grammar;
    }

     Automaton* AutomataWorker::getUnion( Automaton* first, Automaton* second ){

        Automaton* result_automaton = new Automaton( first->getAlphabet() );

        AutomatonState* new_first_state = new AutomatonState( "UI" + first->getName() + second->getName() );
//        AutomatonState* new_final_state = new AutomatonState( "UF" + first->getName() + second->getName() );

        result_automaton->addState( new_first_state );
        result_automaton->setAsFirstState( new_first_state );

//        result_automaton->addState( new_final_state );
//        result_automaton->setAsFinalState( new_final_state );

        addStatesToAutomaton( result_automaton, first->getAllStates() );

        addStatesToAutomaton( result_automaton, second->getAllStates() );

        // TODO :: change names of states

        AutomatonState* firs_first_state = result_automaton->getState( first->getFirstState()->getName() );
        result_automaton->addEpsilonTransition( new_first_state, firs_first_state );

        AutomatonState* second_first_state = result_automaton->getState( second->getFirstState()->getName() );
        result_automaton->addEpsilonTransition( new_first_state, second_first_state );

//        auto first_final_states = first->getFinalStates();
//        for( auto final_state_it = first_final_states.begin(); final_state_it != first_final_states.end(); final_state_it++  ){
//            AutomatonState* final_state = result_automaton->getState( (*final_state_it)->getName() );
//            result_automaton->addEpsilonTransition( final_state, new_final_state );
//        }
//
//        auto second_final_states = second->getFinalStates();
//        for( auto final_state_it = second_final_states.begin(); final_state_it != second_final_states.end(); final_state_it++  ){
//            AutomatonState* final_state = result_automaton->getState( (*final_state_it)->getName() );
//            result_automaton->addEpsilonTransition( final_state, new_final_state );
//        }

         return result_automaton;
    }


    Automaton* AutomataWorker::getIntersection( Automaton* first, Automaton* second ){

        Automaton* result_automaton = new Automaton( first->getAlphabet() );

        AutomatonState* new_first_state = new AutomatonState( "IntersectionFirst" ); // TODO :: add Automaton name;
//        AutomatonState* new_final_state = new AutomatonState( "IntersectionFinal" );

        result_automaton->addState( new_first_state );
        result_automaton->setAsFirstState( new_first_state );
//
//        result_automaton->addState( new_final_state );
//        result_automaton->setAsFinalState( new_final_state );

        addComplementOfStatesToAutomaton( result_automaton, first->getAllStates() );

        addComplementOfStatesToAutomaton( result_automaton, second->getAllStates() );

        // TODO :: change names of states
        AutomatonState* firs_first_state = result_automaton->getState( first->getFirstState()->getName() );
        result_automaton->addEpsilonTransition( new_first_state, firs_first_state );

        AutomatonState* second_first_state = result_automaton->getState( second->getFirstState()->getName() );
        result_automaton->addEpsilonTransition( new_first_state, second_first_state );

//        auto first_final_states = first->getFinalStates();
//        for( auto final_state_it = first_final_states.begin(); final_state_it != first_final_states.end(); final_state_it++  ){
//            AutomatonState* final_state = result_automaton->getState( (*final_state_it)->getName() );
//            final_state->setFinal( false );
//            result_automaton->addEpsilonTransition( final_state, new_final_state );
//        }
//
//        auto second_final_states = second->getFinalStates();
//        for( auto final_state_it = second_final_states.begin(); final_state_it != second_final_states.end(); final_state_it++  ){
//            AutomatonState* final_state = result_automaton->getState( (*final_state_it)->getName() );
//            final_state->setFinal( false );
//            result_automaton->addEpsilonTransition( final_state, new_final_state );
//        }

        return  getComplement( getDetermination( result_automaton ) );
    }

    AutomatonState* AutomataWorker::getStateCreateIfNeeded( Automaton* automaton, std::string state_name, bool final ){
        AutomatonState* result_state;
        if( automaton->containState( state_name ) ){
            result_state = automaton->getState( state_name );
        }else{
            result_state = new AutomatonState( state_name );
            result_state->setFinal( final );
            automaton->addState( result_state );
        }
        return result_state;
    }

    void AutomataWorker::addStatesToAutomaton( Automaton* automaton, std::map< std::string, AutomatonState* > new_states ){
        std::vector<std::string> alphabet = automaton->getAlphabet();
        for( auto new_state_it = new_states.begin(); new_state_it != new_states.end(); new_state_it++ ){
            AutomatonState* new_state_from = getStateCreateIfNeeded( automaton, new_state_it->first, new_state_it->second->isFinal() ); // TODO :: Add automaton name
            for( int by = 0; by < alphabet.size(); ++by ){
                auto new_set_transition_by = new_state_it->second->getTransitionsBy( alphabet[by] );
                for( auto new_state_by_it = new_set_transition_by.begin(); new_state_by_it != new_set_transition_by.end(); ++new_state_by_it ){
                    AutomatonState* new_state_to  = getStateCreateIfNeeded( automaton, (*new_state_by_it)->getName(), (*new_state_by_it)->isFinal() ); // TODO :: Add automaton name
                    automaton->addTransition( new_state_from, alphabet[by], new_state_to );
                }
            }
        }
    }

//    void AutomataWorker::addStatesToAutomaton( Automaton* automaton, std::set< AutomatonState* > new_states ){
//        std::cout << "Add States" << std::endl;
//
//        for( auto new_state_it = new_states.begin(); new_state_it != new_states.end(); new_state_it++ ){
//
//            AutomatonState* new_state_from = getStateCreateIfNeeded(automaton,  (*new_state_it)->getName(), (*new_state_it)->isFinal() ); // TODO :: Add automaton name
//            std::cout << "getFirst state " << std::endl;
//
//            for( auto alphabet_it = automaton->getAlphabet().begin(); alphabet_it != automaton->getAlphabet().end(); alphabet_it++ ){
//                auto new_set_transition_by = (*new_state_it)->getTransitionsBy( *alphabet_it );
//                for( auto new_state_by_it = new_set_transition_by.begin(); new_state_by_it != new_set_transition_by.end(); ++new_state_by_it ){
//                    AutomatonState* new_state_to  = getStateCreateIfNeeded( automaton, (*new_state_by_it)->getName(), (*new_state_by_it)->isFinal() ); // TODO :: Add automaton name
//                    automaton->addTransition( new_state_from, *alphabet_it, new_state_to );
//                }
//            }
//        }
//    }

    void AutomataWorker::addComplementOfStatesToAutomaton( Automaton* automaton, std::map< std::string, AutomatonState* > new_states ){
        std::vector<std::string> alphabet = automaton->getAlphabet();
        for( auto new_state_it = new_states.begin(); new_state_it != new_states.end(); new_state_it++ ){
            AutomatonState* new_state_from = getStateCreateIfNeeded( automaton, new_state_it->first, !new_state_it->second->isFinal() ); // TODO :: Add automaton name
            for( int by = 0; by < alphabet.size(); ++by ){
                auto new_set_transition_by = new_state_it->second->getTransitionsBy( alphabet[by] );
                for( auto new_state_by_it = new_set_transition_by.begin(); new_state_by_it != new_set_transition_by.end(); ++new_state_by_it ){
                    AutomatonState* new_state_to  = getStateCreateIfNeeded( automaton, (*new_state_by_it)->getName(), !(*new_state_by_it)->isFinal() ); // TODO :: Add automaton name
                    automaton->addTransition( new_state_from, alphabet[by], new_state_to );
                }
            }
        }
    }

    bool AutomataWorker::areEqualAlphabets( std::vector<std::string> first, std::vector<std::string> second ){
        if( first.size() != second.size() )
            return false;

        for (auto first_it = first.begin(), second_it = second.begin(); first_it != first.end(); first_it++, second_it++ ){
            if( *first_it != *second_it )
                return false;
        }

        return true;
    }

    Automaton* AutomataWorker::getComplement( Automaton* automaton ){
        Automaton* result_automaton = new Automaton( automaton->getAlphabet() );;
        addComplementOfStatesToAutomaton( result_automaton, automaton->getAllStates());
        AutomatonState* first = getStateCreateIfNeeded( result_automaton, automaton->getFirstState()->getName(), false );
        result_automaton->setAsFirstState( first );
        return result_automaton;
    }

}