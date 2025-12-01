#include "grammarproduction.hpp"

namespace grammar{

    GrammarProduction::GrammarProduction( std::string symbol ): symbol_(symbol){}

    std::string GrammarProduction::getSymbol(){
        return symbol_;
    }

    std::multimap< std::string, GrammarProduction*> GrammarProduction::getAllDerivations(){
        return derivations_;
    }

    // TODO :: this is a multimap
//    std::set<GrammarProduction> GrammarProduction::getDerivationBy( std::string by ){
//        return derivations_.find( by )->second;
//    }

    void GrammarProduction::addDerivation( std::string terminal, GrammarProduction* not_terminal ){
        derivations_.insert( std::multimap< std::string, GrammarProduction*>::value_type( terminal, not_terminal ) );
    }

    void GrammarProduction::addTerminal( std::string terminal ){
        terminals_.insert( terminal );
    }

}
