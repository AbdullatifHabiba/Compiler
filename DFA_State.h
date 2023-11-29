//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_DFA_STATE_H
#define COMPILERS_DFA_STATE_H


#include <set>
#include "NFA_State.h"

class DFA_State {
private:
    std::set<NFA_State*> nfaStates; // Set of NFA states in this DFA state
    bool isFinal;

public:
    DFA_State();
    ~DFA_State();
    set<NFA_State*> get_content();
    map<char, DFA_State*> getTransitions();
    bool isFinalState() ;
    void set_next(char ch, DFA_State *state);
    void setFinalState(bool isFinal);
    void addNFAState(NFA_State* nfaState);//add nfa states which correspond to the dfa state
    int id{};
};

#endif //COMPILERS_DFA_STATE_H
