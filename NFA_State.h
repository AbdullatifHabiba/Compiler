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
    NFA_State( bool isFinal);
    ~NFA_State();
    void addTransition(char rule, NFA_State *next_state);
    void addEpsilonTransition(NFA_State *next_state);
    bool isFinalState() ;
    void setFinalState(bool isFinal);
    map<char, vector<NFA_State*>> getTransitions();
    vector<NFA_State*> getEpsilonClosure();
    void set_id(int a);
    int get_id() const;


private:
    bool isFinal;
    int id;
    static int increase_id;
    map<char, vector<NFA_State*>> transitions;
    vector<NFA_State*> epsilonTransitions;



};


#endif //COMPILERS_NFA_STATE_H


