#include "fileworker.hpp"


FileWorker::FileWorker(){
    // Automaton Config
    transition_separator_ = "|";
    state_separator_ = ",";
    initial_state_marker_ = "->";
    final_state_marker_ = "*";
    dead_state_ = "--";

    // Grammar Config
    derivation_separator_ = "|";

    // Both Config
    epsilon_ = "&";
    alphabet_marker_ = "#";
    alphabet_separator_ = ",";
    name_marker_ = "@";
    final_marker_ = "=";

    // alphabet is configurable for every automaton but we need a default value
    alphabet_ = {"a", "b", "c", "d" };
    inputFileAutomata = new  std::ifstream("automata.in", std::ifstream::in);
    inputFileGrammar = new std::ifstream("grammar.in", std::ifstream::in);
}

std::vector< std::string > FileWorker::tokenize( std::string in, char separator ){
    std::vector< std::string > out;
    std::string::iterator pos = in.begin();
    std::string new_state_name = "";
    bool state = false;
    while ( pos != in.end() ){
        char actual = *pos;
        pos++;
        if( actual == ' ' )
            continue;
        if(actual == separator){
            if( state ){
//                    std::cout << "new_state_name : " << new_state_name << std::endl;
                out.push_back( new_state_name );
                state = false;
                new_state_name = "";
            }else{
                continue;
            }
        }else{
            new_state_name += actual;
            state = true;
//                std::cout << actual << std::endl;
        }
    }
    if( new_state_name.size() )
        out.push_back(new_state_name);

    return out;
}

bool FileWorker::checkAndClearFirstState( std::string& state ){
    std::size_t pos = state.find( initial_state_marker_ );
    if( pos != std::string::npos ){
        state.erase( pos, initial_state_marker_.size() );
        return true;
    }
    return false;
}

bool FileWorker::checkAndClearFinalState( std::string& state ){
    std::size_t pos = state.find( final_state_marker_ );
    if( pos != std::string::npos ){
        state.erase( pos, final_state_marker_.size() );
        return true;
    }
    return false;
}

void FileWorker::createNewState( std::vector< std::string > state_and_transitions, automaton::Automaton* automaton ){
    auto state_name = state_and_transitions.begin();
    bool is_first = checkAndClearFirstState( *state_name );
    bool is_final = checkAndClearFinalState( *state_name );

    automaton::AutomatonState* new_state;
    if( automaton->containState( *state_name ) ){
        new_state = automaton->getState( *state_name );
    }
    else{
        new_state = new automaton::AutomatonState( *state_name );
        automaton->addState( new_state );
    }

    if( is_first )
        automaton->setAsFirstState(new_state);

    if( is_final )
        automaton->setAsFinalState(new_state);
//        std::cout << *state_name << std::endl;

    state_name++;
    std::vector<std::string> alphabet = automaton->getAlphabet();
    alphabet.push_back( epsilon_ );
    for ( int by = 0; state_name != state_and_transitions.end() && by < alphabet.size(); state_name++, by++){
//            std::cout << *state_name << std::endl;
        /// Tokenize second time to remove all states from the set
        std::vector<std::string> possible_state_vector = tokenize(*state_name, state_separator_[0] );

        for( auto possible_state = possible_state_vector.begin(); possible_state != possible_state_vector.end(); possible_state++  ){
            automaton::AutomatonState* to_state;
            if( *possible_state == dead_state_ )
                continue;

            if( automaton->containState( *possible_state ) ){
                to_state = automaton->getState( *possible_state );
            }
            else{
                to_state = new automaton::AutomatonState( *possible_state );
            }
            automaton->addTransition( new_state, alphabet[by], to_state );
        }
    }
}

void FileWorker::createNewProduction(std::vector <std::string> production, grammar::Grammar* grammar ){
    auto production_it = production.begin();

    grammar::GrammarProduction* new_production;
    std::string not_terminal_str;
    not_terminal_str.push_back( (*production_it)[0] );

    std::cout << "NO TERMINAL " << not_terminal_str << std::endl;

    if( grammar->containNotTerminal( not_terminal_str ) ){
        new_production = grammar->getNotTerminal( not_terminal_str );
    }
    else{
        new_production = new grammar::GrammarProduction( not_terminal_str );
        grammar->addNotTerminal( new_production );
    }

    production_it++;

    for ( ;production_it != production.end(); production_it++){

        // TODO : create a function to split terminal/not_terminal for Grammar > Regular Grammar
        if( (*production_it).size() > 1 ){
            std::string terminal;
            terminal.push_back( (*production_it)[0] );
            std::string not_terminal;
            not_terminal.push_back( (*production_it)[1] );
            std::cout << "Derivation " << terminal << " " << not_terminal << std::endl;

            grammar::GrammarProduction* derivation_to;

            if( grammar->containNotTerminal( not_terminal ) ){
                derivation_to = grammar->getNotTerminal( not_terminal );
            }
            else{
                derivation_to = new grammar::GrammarProduction( not_terminal );
            }
            grammar->addDerivation( new_production, terminal, derivation_to );
        }else{
            std::string terminal;
            terminal.push_back( (*production_it)[0] );
            grammar->addTerminalTo( new_production, terminal );
            std::cout << "Derivation Terminal " << terminal << std::endl;
        }
    }
}

automaton::Automaton* FileWorker::getAutomaton(){
    automaton::Automaton* automaton = new automaton::Automaton( alphabet_ );
    openAutomataFile();
    std::string line;
    while(std::getline(*inputFileAutomata, line)){
        std::vector< std::string > tokens = tokenize(line, transition_separator_[0] );
        createNewState(tokens, automaton);
    }
    closeAutomataFile();
    return automaton;
}
//
//automaton::Automaton* FileWorker::getNextAutomaton( ){
//    automaton::Automaton* automaton = new automaton::Automaton( alphabet_ );
//    std::string line;
//    while(std::getline(inputFileAutomata, line) || line.find( final_marker_ ) != std::string::npos ){
//        std::vector< std::string > tokens = tokenize(line, transition_separator_[0] );
//        createNewState(tokens, automaton);
//    }
//    return automaton;
//}

//grammar::Grammar* FileWorker::getNextGrammar( std::string* line );


/// First Symbol add to the Grammar will be set as initial
grammar::Grammar* FileWorker::getGrammar(){
    grammar::Grammar* result_grammar = new grammar::Grammar( alphabet_ );
    std::string line;
    openGrammarFile();
    while(std::getline(*inputFileGrammar, line)){
        std::vector< std::string > tokens = tokenize(line, derivation_separator_[0] );
        createNewProduction(tokens, result_grammar);
    }
    closeGrammarFile();
    return result_grammar;
}

std::map< std::string, automaton::Automaton* > FileWorker::getAutomata(){
    std::map< std::string, automaton::Automaton* > result_map;
    openAutomataFile();
    int automaton_count = 0;
    bool new_automaton_add = true;
    while( new_automaton_add ) {
        std::cout << "New Automaton" << std::endl;

        new_automaton_add = false;
        std::string line;
        automaton::Automaton* new_automaton = new automaton::Automaton( alphabet_ );
        std::string automaton_name = "a" + std::to_string( automaton_count );

        if( inputFileAutomata->is_open() )
            std::cout << "OPEN" << std::endl;
        while( std::getline( *inputFileAutomata, line ) ){
            std::cout << "line: " << line << std::endl;
            if( line.find( final_marker_ ) != std::string::npos )
                break;
            if(line.find(name_marker_) != std::string::npos){
                std::size_t pos = line.find(name_marker_);
                automaton_name = line.substr(pos + name_marker_.size());
                automaton_name.erase(0, automaton_name.find_first_not_of(" \n\r\t"));
                std::cout << "Automaton Name: " << automaton_name << std::endl;
                continue;
            }
            if( line.find( alphabet_marker_ ) != std::string::npos ){
                std::size_t pos = line.find(alphabet_marker_);
                std::string alphabet_str = line.substr(pos + alphabet_marker_.size());
                alphabet_ = tokenize(alphabet_str, alphabet_separator_[0]);
                new_automaton->setAlphabet(alphabet_);
                continue;
            }
            std::vector< std::string > tokens = tokenize(line, transition_separator_[0] );
            if( tokens.size() == 0 )
                continue;
            createNewState(tokens, new_automaton);
            new_automaton_add = true;
        }
        if( new_automaton_add ){
            new_automaton->setName( automaton_name );
            result_map.insert( std::map< std::string, automaton::Automaton* >::value_type( automaton_name, new_automaton ) );
            ++automaton_count;
        }
    }
    closeAutomataFile();
    return result_map;
}


void FileWorker::openAutomataFile(){
    inputFileAutomata->open("/home/joaquim/Projects/Automaton/automata.in");
}

void FileWorker::openGrammarFile(){
    inputFileGrammar->open("grammars.in");
}

void FileWorker::closeAutomataFile(){
    inputFileAutomata->close();
}

void FileWorker::closeGrammarFile(){
    inputFileGrammar->close();
}
