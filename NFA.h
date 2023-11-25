//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_NFA_H
#define COMPILERS_NFA_H


#include <vector>
#include "NFA_State.h"

using namespace std;
class NFA {


public:
    void buildNFA(std::vector<char *> vector1);
    void printNFA();
    NFA();
    ~NFA();
    // define EPSILON
    static const char EPSILON = '@';
private:
    vector<NFA_State*> states;
    NFA_State *start_state;
    NFA_State *accept_state;

};


#endif //COMPILERS_NFA_H
