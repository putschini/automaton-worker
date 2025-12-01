#ifndef FILE_WORKER_HPP
#define FILE_WORKER_HPP

#include "config.hpp"
#include "automaton.hpp"
#include "automatonstate.hpp"

#include "grammar.hpp"
#include "grammarproduction.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <string>

class FileWorker {

    // Automaton Config
    std::string transition_separator_;
    std::string state_separator_ ;
    std::string initial_state_marker_ ;
    std::string final_state_marker_ ;
    std::string dead_state_;

    // Grammar Config
    std::string derivation_separator_;

    // Both Config
    std::string epsilon_ ;
    std::string alphabet_marker_ ;
    std::string alphabet_separator_ ;
    std::string name_marker_ ;
    std::string final_marker_;

    // alphabet should be configurable for every automaton
    // TODO Move to fileworker
    std::vector <std::string> alphabet_ ;

    std::ifstream* inputFileAutomata;
    std::ifstream* inputFileGrammar;

    std::vector <std::string> tokenize(std::string in, char separator);

    bool checkAndClearFirstState(std::string &state);

    bool checkAndClearFinalState(std::string &state);

    void createNewState(std::vector <std::string> state_and_transitions, automaton::Automaton *automaton);

    void createNewProduction(std::vector <std::string> production, grammar::Grammar* grammar );

    void openAutomataFile();

    void openGrammarFile();

    void closeAutomataFile();

    void closeGrammarFile();

public:

    FileWorker();

    automaton::Automaton* getAutomaton();

    grammar::Grammar* getGrammar();

    automaton::Automaton* getNextAutomaton( );

    grammar::Grammar* getNextGrammar( );

    std::map< std::string, automaton::Automaton* > getAutomata();

    std::map< std::string, grammar::Grammar* > getGrammars();

};

#endif //FILE_WORKER_HPP
