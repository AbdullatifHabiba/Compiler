//
// Created by abdu on 11/25/23.
//

#include "DFA_State.h"

void DFA_State::addNFAState(NFA_State *nfaState) {

}
bool DFA_State::isFinalState() {
    return this->isFinal ;
}

void DFA_State::setFinalState(bool isFinal) {
    this->isFinal = isFinal;
}

DFA_State::DFA_State(set<NFA_State *> nfaStates) {

}

map<char, vector<DFA_State *>> DFA_State::getTransitions() {
    return map<char, vector<DFA_State *>>();
}

set<NFA_State *> DFA_State::get_content() {
    return set<NFA_State *>();
}

DFA_State *DFA_State::get_next(char rule) {
    return nullptr;
}

void DFA_State::set_next(char ch, DFA_State *state) {

}


DFA_State::~DFA_State() = default;
