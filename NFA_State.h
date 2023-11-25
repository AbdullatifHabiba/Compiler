//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_NFA_STATE_H
#define COMPILERS_NFA_STATE_H
#include <map>
#include <vector>
using namespace std;

class NFA_State {
public:
    NFA_State();
    ~NFA_State();
    void addTransition(char rule, NFA_State *next_state);
    void addEpsilonTransition(NFA_State *next_state);
    bool isFinalState();
    map<char, vector<NFA_State*>> getTransitions();
    map<char, vector<NFA_State*>> getEpsilonTransitions();
    vector<NFA_State*> getEpsilonClosure();
private:
    bool isFinal;
    map<char, vector<NFA_State*>> transitions;
    vector<NFA_State*> epsilonTransitions;



};


#endif //COMPILERS_NFA_STATE_H


