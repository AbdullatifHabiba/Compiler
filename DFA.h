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
    void printDFA(set<DFA_State *> Dfa);
    void printDFA_data(set<DFA_State *> Dfa);

private:

    void e_closure(NFA_State *s);
    set<NFA_State*> e_closure(set<NFA_State*> T);
    set<NFA_State*> move(set<NFA_State*> T, char input);
    set<char> get_alpha(NFA_State*);

};

#endif