#ifndef NFA_TO_DFA_H
#define NFA_TO_DFA_H

#include "DFA_State.h"
#include "NFA_State.h"
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;


class DFA
{
public:
    DFA();
    virtual ~DFA();
    set<DFA_State*> Converter(NFA_State*);
    static void printDFA(const set<DFA_State *>& Dfa);
    static void printDFA_data(const set<DFA_State *>& Dfa);

    void printTransitionTable(const set<DFA_State *> &Dfa);

private:

    void e_closure(NFA_State *s);
    set<NFA_State*> e_closure(const set<NFA_State*>& T);
    set<NFA_State*> reduce(const set<NFA_State*>& T, char input);
    static set<char> get_all_inputs(NFA_State *s);


};

#endif