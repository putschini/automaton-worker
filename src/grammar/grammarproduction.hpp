#ifndef GRAMMAR_PRODUCTION_HPP
#define GRAMMAR_PRODUCTION_HPP

#include <vector>
#include <string>
#include <map>
#include <set>

#include <iostream>

namespace grammar{

    class GrammarProduction{
    private:

        std::string symbol_;
        std::multimap< std::string, GrammarProduction*> derivations_;
        std::set<std::string> terminals_;

    public:
        GrammarProduction( std::string symbol );

        std::string getSymbol();

        std::multimap< std::string, GrammarProduction*> getAllDerivations();

        std::set<GrammarProduction> getDerivationBy( std::string by );

        void addDerivation( std::string terminal, GrammarProduction* not_terminal );

        void addTerminal( std::string terminal );

        std::multimap< std::string, GrammarProduction*> getDerivations(){
            return derivations_;
        }

        std::set<std::string> getTerminals(){
            return terminals_;
        }

        void printProduction(){
            std::cout << symbol_ << "->";
            for( auto derivation : derivations_ ){
                std::cout << derivation.first << derivation.second->getSymbol() << " | ";
            }

            for( auto terminal : terminals_){
                std::cout << terminal << " | ";
            }
            std::cout << std::endl;
        }
    };
}

#endif //GRAMMAR_PRODUCTION_HPP
