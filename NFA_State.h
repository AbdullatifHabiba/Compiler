//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_NFA_STATE_H
#define COMPILERS_NFA_STATE_H
#include <map>
#include <vector>
#include <string>

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
    void set_id(int a);
    int get_id() const;
    void set_priority(int p);
    int get_priority();
    void set_token(string t);
    string get_token();


private:
    bool isFinal;
    int priority;
    string token;
    int id;
    static int increase_id;
    map<char, vector<NFA_State*>> transitions;
    vector<NFA_State*> epsilonTransitions;
};


#endif //COMPILERS_NFA_STATE_H
