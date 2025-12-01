#ifndef AUTOMATA_WORKER_HPP
#define AUTOMATA_WORKER_HPP

#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>

#include "automatonstate.hpp"
#include "utils.hpp"
#include "automaton.hpp"

#include "grammar.hpp"

namespace automaton{

    class AutomataWorker{

    private:
        static bool areEqualAlphabets( std::vector<std::string> first, std::vector<std::string> second );

        static void createNewState( std::vector< std::string > state_and_transitions, automaton::Automaton* automaton );

        static void createNewProduction(std::vector <std::string> production, grammar::Grammar* grammar );

        static void addStatesToAutomaton( Automaton* automaton, std::map< std::string, AutomatonState* > new_states );

        static void addStatesToAutomaton( Automaton* automaton, std::set< AutomatonState* > new_states );

        static void addComplementOfStatesToAutomaton( Automaton* automaton, std::map< std::string, AutomatonState* > new_states );

    public:

        static Automaton* getDetermination( Automaton* automaton );

        static AutomatonState* getNewState( state_set states );

        static state_set getEpsilonClosureOfSet( state_set states );

        static Automaton* getAutomatonWithoutDeadStates( Automaton* automaton );

        static Automaton* getAutomatonWithoutUnreachedStates( Automaton* automaton );

        static Automaton* getMinimal( Automaton* automaton );

        static grammar::Grammar* getGrammarFrom( Automaton* automaton );

        static Automaton* getUnion( Automaton* first, Automaton* second );

        static Automaton* getIntersection( Automaton* first, Automaton* second );

        static Automaton* getComplement( Automaton* automaton );

        static AutomatonState* getStateCreateIfNeeded( Automaton* automaton, std::string state_mame, bool final );

        Automaton* getAutomaton();

        /// First Symbol add to the Grammar will be set as initial
        grammar::Grammar* getGrammar();

    };

}

#endif //AUTOMATA_WORKER_HPP
