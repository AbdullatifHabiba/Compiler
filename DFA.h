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
    set<NFA_State *> e_closure(const set<NFA_State *>& T);
    set<NFA_State *> move(const set<NFA_State *>& T, char input);
    static set<char> get_alpha(NFA_State *s);
public:
    DFA();
    ~DFA();
    set<DFA_State *> Converter(NFA_State *start);
    static void printDFA(const set<DFA_State *>& Dfa);
    static void printDFA_data(const set<DFA_State *>& Dfa);
};

#endif
