//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_DFA_H
#define COMPILERS_DFA_H


#include "DFA_State.h"

class DFA {
public:
    DFA();
    ~DFA();
    /*convert NFA to DFA return as a vector of states*/
    set<DFA_State*> convert_NFA_to_DFA(NFA_State* start);
    void printDFA(set<DFA_State *> DFA);
private:

    void e_closure(NFA_State *s);

    set<NFA_State*> e_closure(set<NFA_State*> T);

    set<NFA_State*> move(set<NFA_State*> T, char rule);

    set<char> get_alpha(NFA_State* S);

};


#endif //COMPILERS_DFA_H
