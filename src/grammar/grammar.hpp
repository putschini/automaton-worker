#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "grammarproduction.hpp"

namespace grammar {

    class Grammar {
    private:
        std::vector<std::string> not_terminal_alphabet_;
        std::vector<std::string> terminal_alphabet_;
        std::map<std::string, GrammarProduction* > not_terminal_;
        GrammarProduction* first_symbol_;  // TODO : change for a string

    public:
        Grammar( std::vector<std::string> alphabet );

        bool containNotTerminal( std::string not_terminal );

        void addNotTerminal(GrammarProduction* production);

        void addDerivation( GrammarProduction* from, std::string terminal, GrammarProduction* to );

        void addTerminalTo( GrammarProduction* production, std::string terminal );

        GrammarProduction* getNotTerminal( std::string not_terminal );

        void setFirstSymbol( std::string first_symbol );

        std::map<std::string, GrammarProduction* > getNotTerminals(){
            return not_terminal_;
        }

        std::vector<std::string> getTerminalAlphabet(){
            return terminal_alphabet_;
        }

        GrammarProduction* getFirstProduction(){
            return first_symbol_;
        }
        void printGrammar();

//        bool isRegularGrammar();

    };
}

#endif //GRAMMAR_HPP
