//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_NFA_H
#define COMPILERS_NFA_H


#include <vector>
#include <string>
#include "NFA_State.h"

using namespace std;
class NFA {


public:
    NFA* buildNFA(vector<string> vector1);
    void printNFA();
    NFA();
    ~NFA();
    // define EPSILON
    const char EPSILON = '@';
    const string UNION = "|"; // Union symbol
    const string ZERO_OR_MORE ="*"; // Zero or more symbol
    const string ONE_OR_MORE = "+"; // One or more symbol
    vector<NFA_State*> states;
    NFA_State *start_state;
    NFA_State *accept_state;

    void extend(char c);
    void join(NFA *pNfa);
    void OneOrMore();
    void ZeroOrMore();
    void concatenate(NFA*);
    void OR(NFA *A);

private:
    int id = 0;
    bool isOperand(char rule);

};


#endif //COMPILERS_NFA_H
