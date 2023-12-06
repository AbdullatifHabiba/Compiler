//
// Created by u s e r on 03/12/2023.
//

#ifndef COMPILERS_MINIMIZE_H
#define COMPILERS_MINIMIZE_H

#include <bits/stdc++.h>
#include "DFA_State.h"
using namespace std;

class Minimize
{
public:
    Minimize();
    virtual ~Minimize();
    set<DFA_State*> DFA_min (const set<DFA_State*>& DFA);

    static void printTransitionTable(const set<DFA_State *> &Dfa);
    DFA_State *get_start_state() const;

private:
     DFA_State *start_state;

};

#endif //COMPILERS_MINIMIZE_H










