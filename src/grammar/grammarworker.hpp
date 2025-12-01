#ifndef GRAMMAR_WORKER_HPP
#define GRAMMAR_WORKER_HPP

#include "automaton.hpp"
#include "grammar.hpp"

#include "automataworker.hpp"

namespace grammar{

    class GrammarWorker{

    public:
        static automaton::Automaton* getAutomatonFrom( Grammar* grammar);

    };
}


#endif //GRAMMAR_WORKER_HPP
