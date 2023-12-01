//
// Created by abdu on 11/25/23.
//

#include "DFA_State.h"

void DFA_State::set_content(set<NFA_State *> Content) {
    this->content = Content;
}

set<NFA_State *> DFA_State::get_content() {
    return this->content;
}

map<char, DFA_State*> DFA_State::getTransitions() {
    return transitions;
}


DFA_State::DFA_State() {
    this->content = content;
    bool flag = false;
    for (set<NFA_State*>::iterator i = this->content.begin(); i != this->content.end(); i++)
    {
        NFA_State *temp = *i;
        if(temp->isFinalState())
        {
            flag = true;
        }
    }
    this->isFinal = flag;
    this->id=increased_id++;
}

void DFA_State::setFinalState(bool isFinal) {
    this->isFinal = isFinal;
}

bool DFA_State::isFinalState() {
    return isFinal;
}

DFA_State* DFA_State::get_next(char ch) {
    auto  t = this->transitions.find(ch);
    if( t== transitions.end())
    {
        DFA_State* d = new DFA_State();
        return d;
    }
    return this->transitions[ch];
}

void DFA_State::addTransition(char rule, DFA_State *next_state) {
    transitions[rule] = next_state;
}

DFA_State::~DFA_State() = default;
int DFA_State::increased_id = 1;

void DFA_State::set_id(int a) {
    this->id=a;
}

int DFA_State::get_id() const {
    return this->id;
}


DFA_State::DFA_State(bool is_accepted) {
    this -> id = increased_id++;
}





