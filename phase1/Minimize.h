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
    set<DFA_State*> minimize_dfa_states (const set<DFA_State*>& DFA);

    static void printMinGraph(const set<DFA_State *> &Mfa);
    [[nodiscard]] DFA_State *get_start_state() const;

private:
     DFA_State *start_state{};



    static set<DFA_State *> bfsAndGetGroups(const set<DFA_State *> &DFA, set<DFA_State *> &marked, set<char> &alpha,
                                     vector<set<DFA_State *>> *grouping);

    void create_grouping(int bit, vector<set<DFA_State *>> *grouping, set<char> &alpha);

    set<DFA_State *> buildMinimizedDFA(const vector<set<DFA_State *>> *grouping, const set<char> &alpha);
};

#endif //COMPILERS_MINIMIZE_H










