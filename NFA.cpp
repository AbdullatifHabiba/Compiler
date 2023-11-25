//
// Created by abdu on 11/25/23.
//

#include <stack>
#include "NFA.h"
#include "NFA_State.h"
#include <iostream>
#include <regex>
#include <set>
#include <cassert>

using namespace std;
void NFA::printNFA() {
    cout << "NFA" << endl;
    // print from start state
    cout << "Start State: " << start_state << endl;
    cout << "Accept State: " << accept_state << endl;
    cout << "Transitions: " << endl;
    for (auto& state : states) {
        cout << state << endl;
        for (auto& transition : state->getTransitions()) {
            cout << "\t" << transition.first << ": ";
            for (auto& next_state : transition.second) {
                cout << next_state << " ";
            }
            cout << endl;
        }
    }


}
NFA* NFA::buildNFA(vector<string> expression) {
    stack < NFA* > s;

    for(int i = 0;i < (int)expression.size();++i)
    {
        if(expression[i] == " ")
        {
            assert(s.size() >= 2 and "error");
            NFA *A = s.top();    s.pop();
            NFA *B = s.top();    s.pop();
            B ->concatenate(A);
            s.push(B);
        }
        else if(expression[i] ==ZERO_OR_MORE)
        {
            NFA *A = s.top();    s.pop();
            A ->ZeroOrMore();
            s.push(A);
        }
        else if(expression[i] == ONE_OR_MORE)
        {
            NFA *A = s.top();    s.pop();
            A->OneOrMore();
            s.push(A);
        }
        else if(expression[i] == UNION)
        {
            assert(s.size() >= 2 and "error");
            NFA *A = s.top();    s.pop();
            NFA *B = s.top();    s.pop();
            B -> OR(A);
            s.push(B);
        }
        else if(expression[i] == "\\L")
        {
            NFA *str = new NFA();
            str -> start_state = new NFA_State(false);
            str -> accept_state = new NFA_State(false);

            str -> start_state -> addTransition('\0' , str -> accept_state);
            s.push(str);
        }
        else if((i + 2) < (int)expression.size() and expression[i].size() * expression[i + 1].size() * expression[i + 2].size() == 1 and
                expression[i + 2] == "-" and
                ((isalpha(expression[i][0]) and isalpha(expression[i + 1][0])) or
                 (isdigit(expression[i][0]) and isdigit(expression[i + 1][0]))))
        {
            char a = expression[i++][0];
            char b = expression[i++][0];

            assert(expression[i] == "-" and "error invalid postfix");

            NFA *range = new NFA();
            range -> start_state = new NFA_State(false);
            range -> accept_state = new NFA_State(false);
            for(int j = a;j <= b;++j)
                range -> start_state -> addTransition(j , range -> accept_state);

            range -> accept_state -> setFinalState(true);
            s.push(range);
        }
        else
        {
            NFA *nfa = new NFA();
            nfa -> start_state = new NFA_State(false);
            nfa -> accept_state = new NFA_State(false);

            int z = 0;
            if(expression[i][z] == '\\')      ++z;

            nfa -> start_state -> addTransition(expression[i][z++] , nfa -> accept_state);

            while(z < (int)expression[i].size())
            {
                if(expression[i][z] == '\\')
                    ++z;

                nfa -> extend(expression[i][z++]);
            }
            s.push(nfa);
        }
    }

    NFA *result = s.top();    s.pop();

    return result;
}

bool NFA:: isOperand(char rule) {
    return rule != '|' && rule != '*' && rule != '+' && rule != '?' && rule != '.';

}


NFA::~NFA() = default;

NFA::NFA() = default;







void NFA::OneOrMore() {
    NFA_State* newStart = new NFA_State(false);
    NFA_State* newEnd = new NFA_State(false);

    this -> accept_state -> setFinalState(false);
    this -> accept_state -> addTransition(EPSILON, newEnd);

    newStart -> addTransition(EPSILON, this -> start_state);
    this -> accept_state -> addTransition(EPSILON, newEnd);
    this -> start_state = newStart;

    this -> accept_state = newEnd;
    this -> accept_state -> setFinalState(true);
}


void NFA::ZeroOrMore() {
    // Zero or One: nfa?
    OneOrMore();
    this -> start_state -> addTransition(EPSILON, this -> accept_state);
}

void NFA::extend(char c) {
    this -> accept_state ->setFinalState(false);
    auto* new_acc = new NFA_State(false);
    this -> accept_state -> addTransition(c, new_acc);
    new_acc -> setFinalState(true);
    new_acc -> id= this -> id++;
    this -> accept_state = new_acc;
    this -> states.push_back(new_acc);
}

void NFA::join(NFA *pNfa) {
    auto* newStart = new NFA_State(false);
    newStart ->addTransition(EPSILON, this -> start_state);
    newStart -> addTransition(EPSILON, pNfa-> start_state);
    this -> start_state = newStart;
    this -> accept_state = nullptr;
}


void NFA::OR(NFA* A)
{
    auto* newStart = new NFA_State(false);
    auto* newEnd = new NFA_State(false);

    newStart -> addTransition(EPSILON, this -> start_state);
    newStart -> addTransition(EPSILON, A -> start_state);

    this -> accept_state -> addTransition(EPSILON, newEnd);
    A -> accept_state -> addTransition(EPSILON, newEnd);


    this -> accept_state -> setFinalState(false);
    A -> accept_state -> setFinalState(false);



    this -> start_state = newStart;
    this -> accept_state = newEnd;

    this -> accept_state -> setFinalState(true);
}

void NFA::concatenate(NFA *A) {
    this -> start_state -> addTransition(EPSILON, A -> start_state);
    this -> accept_state -> setFinalState(false);
    this -> accept_state = A -> accept_state;

}



