//
// Created by abdu on 11/25/23.
//

#include <stack>
#include "NFA.h"
#include "NFA_State.h"
#include <iostream>
#include <set>
#include <cassert>
#include <algorithm>

using namespace std;
void NFA::printNFA() const {
    cout << "NFA" << endl;
    // print from start state
    cout << "Start State: " << start_state->get_id() << endl;
    cout << "Accept State: " << accept_state ->get_id()<< endl;
    cout << "Transitions size : " << start_state->getTransitions().size()<< endl;

    cout << "Transitions: " << endl;

        for (auto& transition : start_state->getTransitions()) {
            cout << "\t" << transition.first << ": ";
            for (auto& next_state : transition.second) {
                cout << next_state << " ";
            }
            cout << endl;
        }



}
int counter=0;
void NFA::printNFA(NFA_State* state, set<NFA_State*>& visited) {
    // Check if the state has already been visited
    if (visited.find(state) != visited.end()) {
        return;
    }
    if(state->isFinalState()){
        counter++;
        cout << "state id: "<< state->get_id()<< "  token: " << state->get_token()<< " is final?: "<<state->isFinalState() << endl<< counter<<endl;

    }
    // Mark the state as visited
    visited.insert(state);
//    cout << "state id: "<< state->get_id() << "   is it final?  " << state->isFinalState() << endl<< counter<<endl;

    // Print the state and its transitions
    /*for (auto& transition : state->getTransitions()) {
        cout << "State " << state->get_id() << " --" << transition.first << "--> ";
        for (auto& next_state : transition.second) {
            cout << "State " << next_state->get_id() <<" , ";
        }
        cout << endl;
    }*/

    // Recursively print all reachable states
    for (auto& transition : state->getTransitions()) {
        for (auto& next_state : transition.second) {
            printNFA(next_state, visited);
        }
    }
}

NFA* NFA::handleConcatenation(stack <NFA*>& s) {
    assert(s.size() >= 2 and "error");
    NFA *A = s.top();    s.pop();
    NFA *B = s.top();    s.pop();
    B ->concatenate(A);
    return B;
}

NFA* NFA::handleZeroOrMore(stack <NFA*>& s) {
    NFA *A = s.top();    s.pop();
    A ->ZeroOrMore();
    return A;
}

NFA* NFA::handleOneOrMore(stack <NFA*>& s) {
    NFA *A = s.top();    s.pop();
    A->OneOrMore();
    return A;
}

NFA* NFA::handleUnion(stack <NFA*>& s) {
    assert(s.size() >= 2 and "error");
    NFA *A = s.top();    s.pop();
    NFA *B = s.top();    s.pop();
    B -> OR(A);
    return B;
}

NFA* NFA::handleEpsilon() {
    NFA *str = new NFA();
    str -> start_state = new NFA_State(false);
    str -> accept_state = new NFA_State(false);

    str -> start_state -> addTransition('@', str -> accept_state);
    return str;
}

NFA* NFA::handleRange(vector<string>& expression, int& i) {
    char a = expression[i++][0];
    char b = expression[i++][0];

    assert(expression[i] == "-" and "error invalid postfix");

    NFA *range = new NFA();
    range -> start_state = new NFA_State(false);
    range -> accept_state = new NFA_State(false);
    for(int j = a;j <= b;++j)
        range -> start_state -> addTransition(j , range -> accept_state);

    range -> accept_state -> setFinalState(true);
    return range;
}

NFA* NFA::handleCharacter(vector<string>& expression, int& i) {
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
    return nfa;
}



NFA* NFA::buildNFA(vector<string> expression) {
    stack < NFA* > s;
//  cout<< expression.size()<<endl;
//    print_expression(expression);
    for(int i = 0;i < (int)expression.size();++i)
    {
        if(expression[i] == " ")
        {
            s.push(handleConcatenation(s));
        }
        else if(expression[i] ==ZERO_OR_MORE)
        {
            s.push(handleZeroOrMore(s));
        }
        else if(expression[i] == ONE_OR_MORE)
        {
            s.push(handleOneOrMore(s));
        }
        else if(expression[i] == UNION)
        {
            s.push(handleUnion(s));
        }
        else if(expression[i] == "\\L")
        {
            s.push(handleEpsilon());
        }
        else if((i + 2) < (int)expression.size() and expression[i].size() * expression[i + 1].size() * expression[i + 2].size() == 1 and
                expression[i + 2] == "-" and
                ((isalpha(expression[i][0]) and isalpha(expression[i + 1][0])) or
                 (isdigit(expression[i][0]) and isdigit(expression[i + 1][0]))))
        {
            s.push(handleRange(expression, i));
        }
        else
        {
            s.push(handleCharacter(expression, i));
        }
    }

    NFA *result = s.top();    s.pop();
//    set<NFA_State*> vis;
//    result->printNFA(result->start_state,vis);
//    cout<<"================================"<<endl;
    return result;
}



NFA::~NFA() = default;

NFA::NFA() = default;

void NFA::OneOrMore() {
    auto* newStart = new NFA_State(false);
    auto* newEnd = new NFA_State(false);
    this -> accept_state -> setFinalState(false);
    this -> accept_state -> addTransition(EPSILON, newEnd);
    newEnd -> set_priority(this -> accept_state -> get_priority());
    newEnd -> set_token(this -> accept_state -> get_token());
    newStart -> addTransition(EPSILON, this -> start_state);
    this -> accept_state -> addTransition(EPSILON, this->start_state);
    this -> start_state = newStart;

    this -> accept_state = newEnd;
    this -> accept_state -> setFinalState(true);
}


void NFA::ZeroOrMore() {
    OneOrMore();
    this -> start_state -> addTransition(EPSILON, this -> accept_state);
}

void NFA::extend(char c) {
    this -> accept_state ->setFinalState(false);
    auto* new_acc = new NFA_State(false);
    this -> accept_state -> addTransition(c, new_acc);
    new_acc -> setFinalState(true);
    new_acc -> set_priority(this -> accept_state -> get_priority());
    new_acc -> set_token(this -> accept_state -> get_token());
    this -> accept_state = new_acc;
    this -> states.push_back(new_acc);
}

void NFA::join(NFA *pNfa) {
    auto* newStart = new NFA_State(false);
    newStart ->addTransition(EPSILON, this -> start_state);
    newStart -> addTransition(EPSILON, pNfa-> start_state);
    this -> start_state = newStart;
//    this -> accept_state->addTransition(EPSILON, this->accept_state);
//    this -> accept_state->addTransition(EPSILON, pNfa->accept_state);

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
    this -> accept_state -> set_priority(A -> accept_state -> get_priority());
    this -> accept_state -> set_token(A -> accept_state -> get_token());
}

void NFA::concatenate(NFA *A) {
    this -> accept_state -> addTransition(EPSILON, A -> start_state);
    this -> accept_state -> setFinalState(false);
    this -> accept_state = A -> accept_state;

}



