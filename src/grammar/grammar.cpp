#include "grammar.hpp"

namespace grammar{

    Grammar::Grammar( std::vector<std::string> alphabet ) : terminal_alphabet_( alphabet ){}

    bool Grammar::containNotTerminal( std::string not_terminal ){
        return not_terminal_.count(not_terminal);
    }

    void Grammar::addNotTerminal(GrammarProduction* production){
        not_terminal_.insert( std::map<std::string, GrammarProduction* >::value_type( production->getSymbol(), production ) );
        if( first_symbol_ == nullptr )
            first_symbol_ = production;
    }

    void Grammar::addDerivation( GrammarProduction* from, std::string terminal, GrammarProduction* to ){
        if( !containNotTerminal( from->getSymbol() ) )
            addNotTerminal( from );
        if( !containNotTerminal( to->getSymbol() ) )
            addNotTerminal( to );
        from->addDerivation( terminal, to );
    }

    void Grammar::addTerminalTo( GrammarProduction* production, std::string terminal ){
        if( !containNotTerminal( production->getSymbol() ) )
            addNotTerminal( production );
        production->addTerminal( terminal );
    }

    GrammarProduction* Grammar::getNotTerminal( std::string not_terminal ){
        return not_terminal_.find( not_terminal )->second;
    }

    void Grammar::setFirstSymbol( std::string first_symbol ){
        first_symbol_ = not_terminal_.find( first_symbol )->second;
    }

    void Grammar::printGrammar(){
        first_symbol_->printProduction();
        for( auto derivation : not_terminal_ ){
            if( derivation.second != first_symbol_ )
                derivation.second->printProduction();
        }
    }

}
