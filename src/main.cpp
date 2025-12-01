#include "fileworker.hpp"
#include "automataworker.hpp"
#include "grammarworker.hpp"
#include "syntactictree.hpp"

// TODO : Remove iostreams

// TODO : create test function

// TODO : Change news

void test_regex(){
    std::string regex = "(cd(a|c)a)*(asd)*";

    regex::SyntacticTree* st = new regex::SyntacticTree( regex );
    std::vector< std::string > token = st->tokenize( regex );

    for( std::string a : token ){
    	std::cout << a << "\n";
    }
    std::cout << std::endl;

    st->printTree();
}


int main( int argc, char** argv )
{

    // test_regex();
   FileWorker* fl = new FileWorker();

   std::map< std::string, automaton::Automaton* > a = fl->getAutomata();
   for( auto a_it : a ){
   		std::cout << "Automaton" << std::endl;
       std::cout << a_it.first << std::endl;
       a_it.second->printState();
   }
//    auto a1 = a.find( "a1" ), a2 = a.find( "a0" ), a3 = a.find("a2")  ;
//    if( a1 != a.end() && a2 != a.end() ){
//
////        grammar::Grammar * g = automaton::AutomataWorker::getGrammarFrom( a1->second );
////
////        g->printGrammar();
////
////        automaton::Automaton* c = grammar::GrammarWorker::getAutomatonFrom( g );
////        c->printState();
//
//        std::cout << "OK" << std::endl;
//        std::cout << "Union" << std::endl;
//
//        automaton::Automaton* b = automaton::AutomataWorker::getUnion( a1->second, a2->second );
//        automaton::AutomataWorker::getDetermination( b )->printState();
//        std::cout << "Intersection" << std::endl;
//
//        automaton::Automaton* c = automaton::AutomataWorker::getIntersection( a1->second, a2->second );
//        c->printState();
//
//        std::cout << "UnionMinimal" << std::endl;
//
//        automaton::Automaton* d = automaton::AutomataWorker::getMinimal( b );
//
//        d->printState();
//
//        std::cout << "Intersection Minimal" << std::endl;
//
//        automaton::Automaton* f = automaton::AutomataWorker::getMinimal( c );
//
//        f->printState();
//
//    }


    //    automaton::AutomatonWorker aw =

//    std::vector< std::string > alph( {"a", "b"} ) ;
//    automaton::Automaton* a = fl.getAutomaton();
//
//
////    a->printState();
//
//    automaton::Automaton* b = automaton::AutomataWorker::getDetermination(a);
////    automaton::Automaton* c = automaton::AutomataWorker::getAutomatonWithoutDeadStates(a);
////    automaton::Automaton* d = automaton::AutomataWorker::getAutomatonWithoutUnreachedStates(a);
////    automaton::Automaton* f = automaton::AutomataWorker::getAutomatonWithoutUnreachedStates(b);
////    f = automaton::AutomataWorker::getAutomatonWithoutDeadStates(f);
//
//    std::cout << "Determination" << std::endl;
//    b->printState();
////    std::cout << "No Dead States" << std::endl;
////    c->printState();
////    std::cout << "No Unreached States" << std::endl;
////    d->printState();
//
////    std::cout << "PRE - Minimal" << std::endl;
////    f->printState();
////    f = automaton::AutomataWorker::getMinimal(f);
////    std::cout << "Minimal" << std::endl;
////    f->printState();
//    grammar::Grammar* g1 = automaton::AutomataWorker::getGrammarFrom( b );
//
////    grammar::Grammar* g = fl.getGrammar();
//    std::cout << "Grammar" << std::endl;
//
//    g1->printGrammar();

    return 0;
};
