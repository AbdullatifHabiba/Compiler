//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_DFA_H
#define COMPILERS_DFA_H


#include "DFA_State.h"
class DFA {
private:
    set<NFA_State*> returned;
    void e_closure(NFA_State *s);
    set<NFA_State *> e_closure(set<NFA_State *> T);
    set<NFA_State *> move(set<NFA_State *> T, char input);
    set<char> get_alpha(NFA_State *s);
public:
    DFA();
    ~DFA();
    set<DFA_State *> Converter(NFA_State *start);
    void printDFA(set<DFA_State *> Dfa);
    void printDFA_data(set<DFA_State *> Dfa);
};

#endif
