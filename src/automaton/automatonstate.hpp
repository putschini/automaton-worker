#ifndef AUTOMATON_STATE_HPP
#define AUTOMATON_STATE_HPP

#include <map>
#include <set>
#include <string>
#include <iostream>

namespace automaton {

    class AutomatonState {

        typedef std::multimap<std::string, AutomatonState *> transitions;

        transitions transitions_;
        std::string name_;
        bool final_;

    public:

        AutomatonState(std::string name);

        void connectTo(AutomatonState *to, std::string by);

        std::string getName();

        int countTransitionsBy(std::string by);

        /// Epsilon is configurable so we need to pass it
        std::set<AutomatonState *> getEpsilonClosure(std::string epsilon);

        std::set<AutomatonState *> getTransitionsBy(std::string by);

        std::set<AutomatonState *> getAllReachedStates();

        transitions getAllTransitions();

        bool reachSomeStateOf(std::set<AutomatonState *> states);

        void setFinal(bool final);

        bool isFinal();

        //////////////////////////////
        void printState();

        void printTransitionsBy(std::string by);

    };

}
#endif //AUTOMATON_STATE_HPP
