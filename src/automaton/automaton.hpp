#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>

#include "automatonstate.hpp"
#include "utils.cpp"

namespace automaton {

    typedef std::map<std::string, AutomatonState *> state_map;
    typedef std::set<AutomatonState *> state_set;

    class Automaton {

        AutomatonState* first_state_;
        state_map all_states_;
        std::vector <std::string> alphabet_; // should not contain epsilon symbol
        std::string epsilon_;
        std::string name_;

    public:

        Automaton(std::vector<std::string> alphabet);

        void addTransition(AutomatonState *out, std::string by, AutomatonState *in);

        void addState(AutomatonState *state);

        AutomatonState *getState(std::string name);

        bool containState(AutomatonState *state);

        bool containState(std::string name);

        void setAsFirstState(AutomatonState *first);

        void setAsFinalState(AutomatonState *final);

        bool isFinalState(AutomatonState *final);

        void setAlphabet(std::vector <std::string> alphabet);

        std::vector <std::string> getAlphabet();

        std::string getEpsilon();

        bool isAFND();

        state_set getStatesReachedBy(state_set from, std::string by);

        state_set getStatesReachedBy(AutomatonState *from, std::string by);

        void addDeadState();

        AutomatonState* getFirstState();

        state_map getAllStates();

        state_set getFinalStates();

        state_set getNotFinalStates();

        void printState();

        void addEpsilonTransition( AutomatonState* from, AutomatonState* to );

        std::string getName(){
            return name_;
        }

        void setName( std::string name ){
            name_ = name;
        }
    };
}

#endif //AUTOMATON_HPP
