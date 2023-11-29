//
// Created by abdu on 11/25/23.
//

#include "DFA.h"
#include <queue>

DFA::DFA() {

}

DFA::~DFA() {

}
set<NFA_State*> Mapped;
// get each nfa state epsilon closure
void DFA::e_closure(NFA_State *s)
{
    set<NFA_State*> v ;
    for (NFA_State *x : s->getTransitions()['@']) {
        v.insert(x);
    }
    Mapped.insert(s);
    if(v.size() == 0)
    {
        return;
    }
    for (set<NFA_State*>::iterator i = v.begin(); i != v.end(); i++)
    {
        NFA_State *state  = *i;
        e_closure(state);
    }
}
set<NFA_State*> DFA::e_closure(set<NFA_State*> T)
{
    set<NFA_State*> returned_set;
    for (set<NFA_State*>::iterator i = T.begin(); i != T.end(); i++)
    {
        Mapped.clear();
        NFA_State *state = *i;
        e_closure(state);
        set<NFA_State*> s = Mapped;
        returned_set.insert(s.begin(), s.end());
    }
    return returned_set;
}

set<NFA_State*> DFA::move(set<NFA_State*> T, char input)
{
    set<NFA_State*> returned_set;
    for (set<NFA_State*>::iterator i = T.begin(); i != T.end(); i++)
    {
        NFA_State *state = *i;
        set<NFA_State*> s1 ;
        for (NFA_State *x : state->getTransitions()['@']) {
            s1.insert(x);
        }
        set<NFA_State*> s2 = e_closure(s1);
        returned_set.insert(s2.begin(), s2.end());
    }
    return returned_set;
}

set<char> DFA::get_alpha(NFA_State *S) {
    return set<char>();
}

set<DFA_State *> DFA::convert_NFA_to_DFA(NFA_State *start) {
    return set<DFA_State *>();
}


