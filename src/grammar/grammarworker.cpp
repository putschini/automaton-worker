#include "grammarworker.hpp"

namespace grammar{

    automaton::Automaton* GrammarWorker::getAutomatonFrom( Grammar* grammar ){
        automaton::Automaton* result_automaton = new automaton::Automaton( grammar->getTerminalAlphabet() );
        automaton::AutomatonState* final_state = new automaton::AutomatonState( "NF" );
        final_state->setFinal(true);
        result_automaton->addState( final_state );
//        auto productions = grammar->getProductions();
        for( auto production : grammar->getNotTerminals()){
            automaton::AutomatonState* from  = automaton::AutomataWorker::getStateCreateIfNeeded( result_automaton, production.second->getSymbol(), false );
            for( auto derivation : production.second->getDerivations() ){
                automaton::AutomatonState* to  = automaton::AutomataWorker::getStateCreateIfNeeded( result_automaton, derivation.second->getSymbol(), false );
                result_automaton->addTransition( from, derivation.first, to );
            }
            for( auto terminal : production.second->getTerminals() ){
                result_automaton->addTransition( from, terminal, final_state );
            }
        }
        automaton::AutomatonState* first  = automaton::AutomataWorker::getStateCreateIfNeeded( result_automaton, grammar->getFirstProduction()->getSymbol() , false );

        result_automaton->setAsFirstState( first );

        return result_automaton;
    }

}



// TODO : Finish it
//GrammarProduction* GrammarWorker::getProductionCreateIfNeeded( Grammar* grammar, std::string symbol){
//    GrammarProduction* result_state;
//    if( automaton->containState( state_name ) ){
//        result_state = automaton->getState( state_name );
//    }else{
//        result_state = new AutomatonState( state_name );
//        result_state->setFinal( final );
//        automaton->addState( result_state );
//    }
//    return result_state;
//}
