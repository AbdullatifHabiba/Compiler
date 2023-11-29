//
// Created by abdu on 11/25/23.
//

#ifndef COMPILERS_NFA_H
#define COMPILERS_NFA_H


#include <vector>
#include <string>
#include "NFA_State.h"
#include <stack>
#include <set>

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

    void printNFA(NFA_State *state, std::set<NFA_State *> &visited);

private:
    int id = 0;

    NFA *handleCharacter(vector<string> &expression, int &i);

    static NFA *handleRange(vector<string> &expression, int &i);

    static NFA *handleEpsilon();

    static NFA *handleUnion(stack<NFA *> &s);

    static NFA *handleOneOrMore(stack<NFA *> &s);
    static NFA *handleZeroOrMore(stack<NFA *> &s);

    static NFA *handleConcatenation(stack<NFA *> &s);


};


#endif //COMPILERS_NFA_H
