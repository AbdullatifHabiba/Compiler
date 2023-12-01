//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_DFA_STATE_H
#define COMPILERS_DFA_STATE_H


#include <set>
#include "NFA_State.h"

class DFA_State {
private:
    std::set<NFA_State*> content; // Set of NFA states in this DFA state
    map<char, DFA_State*> transitions;
    int id;
    static int increased_id;

public:
    DFA_State();
    DFA_State(bool is_accepted);
    ~DFA_State();
    bool isFinal;
    set<NFA_State*> get_content();
    void set_content(set<NFA_State*>);
    map<char, DFA_State*> getTransitions();
    void addTransition(char rule, DFA_State *next_state);
    bool isFinalState() ;
    DFA_State* get_next(char ch);
    void setFinalState(bool isFinal);
    void set_id(int a);
    int get_id() const;

};

#endif //COMPILERS_DFA_STATE_H
